#include "InventoryComponent.h"
#include "EnhancedInputComponent.h"
#include "InventoryPanel.h"
#include "PickUpItem.h"
#include "Blueprint/UserWidget.h"
#include "cattest/Game/MyGameInstance.h"
#include "Kismet/GameplayStatics.h"


UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::SetupPlayerInputComponent()
{
	if (UEnhancedInputComponent* EnhancedInputComponent = GetOwner()->GetComponentByClass<UEnhancedInputComponent>())
	{
		EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Triggered, this, &UInventoryComponent::ToggleVisibilityInventory);
		EnhancedInputComponent->BindAction(PickUpAction, ETriggerEvent::Triggered, this, &UInventoryComponent::PickupItem);
	}
}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();


	SetupPlayerInputComponent();
}

void UInventoryComponent::InitializeInventory()
{
	GetItems().SetNum(9);

	if (IsValid(InventoryWidgetClass))
	{
		InventoryWidget = Cast<UInventoryPanel>(CreateWidget(GetWorld()->GetFirstPlayerController(), InventoryWidgetClass));
		if (InventoryWidget)
		{
			RefreshInventory();
		}
	}
}


void UInventoryComponent::ToggleVisibilityInventory()
{
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		isVisible = !isVisible;
		if (isVisible)
		{
			InventoryWidget->RemoveFromParent();
			InventoryWidget = nullptr;
			PlayerController->bShowMouseCursor = false;
			FInputModeGameOnly InputMode;
			PlayerController->SetInputMode(InputMode);
		}
		else
		{
			InitializeInventory();
			if (!InventoryWidget)
			{
				return;
			}
			InventoryWidget->AddToViewport();
			PlayerController->bShowMouseCursor = true;
			FInputModeGameAndUI InputMode;
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
			PlayerController->SetInputMode(InputMode);
		}
	}
}


void UInventoryComponent::RefreshInventory()
{
	if (!InventoryWidget)
	{
		return;
	}

	InventoryWidget->OnionsBox->ClearChildren();
	int index = 0;
	for (const FInventoryItem& item : GetItems())
	{
		if (auto Slot = Cast<UInventorySlot>(CreateWidget(InventoryWidget, InventoryWidgetSlotClass)))
		{
			Slot->SItem = item;
			Slot->index = index;
			Slot->SetInventoryComponent(this);
			InventoryWidget->OnionsBox->AddChildToHorizontalBox(Slot);
			++index;
		}
	}
}


void UInventoryComponent::PickupItem()
{
	for (const FHitResult& Hit : SphereTrace())
	{
		if (auto PickUpItem = Cast<APickUpItem>(Hit.GetActor()))
		{
			if (GetDebugMode())
			{
				FText name = PickUpItem->ItemStructure.Name;
				log(name.ToString());
			}

			AddItem(PickUpItem->ItemStructure);

			PickUpItem->Destroy();
			if (PickUpItem->ItemStructure.SpawnSound)
			{
				FVector Start;
				FRotator CameraRotation;
				GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Start, CameraRotation);
				UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickUpItem->ItemStructure.SpawnSound, Start);
			}
			return;
		}
	}
}


TArray<FHitResult> UInventoryComponent::SphereTrace()
{
	TArray<FHitResult> HitResults;

	FVector Start = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FRotator ActorRotation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorRotation();

	FVector ForwardVector = ActorRotation.Vector();
	FVector End = Start + ForwardVector * (GrabRange / 2);
	Start -= FVector(0, 0, GrabRange / 2);

	float SphereRadius = GrabRange / 2;
	FCollisionQueryParams CollisionParams;
	CollisionParams.bTraceComplex = true;

	GetWorld()->SweepMultiByChannel(
		HitResults,
		Start,
		End,
		FQuat::Identity,
		ECC_Camera,
		FCollisionShape::MakeSphere(SphereRadius),
		CollisionParams
	);

	mDrawSphere((Start + End) / 2.0f, SphereRadius);

	return HitResults;
}

TArray<FHitResult> UInventoryComponent::LineTrace()
{
	TArray<FHitResult> HitResults;
	FVector Start;
	FRotator CameraRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Start, CameraRotation);
	FVector End = Start + CameraRotation.Vector() * GrabRange;

	GetWorld()->LineTraceMultiByChannel(HitResults, Start, End, ECC_Visibility);
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 5, 0, 4);
	return HitResults;
}


/**
 * Dodaje item do inventory. Wyszukuje po nazwie (zwiększa ilość), jesli nie znajdzie po nazwie to doda do pierwsezgo miejsca  z ilością=0.
 * Jeśli nie znajdzie miejsca nic nie robi.
 */
void UInventoryComponent::AddItem(FInventoryItem Item)
{
	for (int32 i = 0; i < GetItems().Num(); ++i)
	{
		FInventoryItem* _Item = GetItem(i);
		if (_Item->Name.EqualTo(Item.Name) && _Item->Stackable) // Czy mamy w inventory item z taka nazwa i jest stackable, wowczas zwiekszamy ilosc.
		{
			_Item->Quantity += Item.Quantity;
			return;
		}
	}
	for (int32 i = 0; i < GetItems().Num(); ++i)
	{
		FInventoryItem* _Item = GetItem(i);
		if (_Item->Quantity == 0) // Dodajemy do pierwszego pustego miejsca
		{
			*_Item = Item;
			return;
		}
	}

	// Jesli nie ma stworzonych nawet pustych slotow dodajemy w pierwsze miejsce.
	GetItems().Insert(Item, 0);
}

void UInventoryComponent::RemoveItem(int index)
{
	if (GetItems().IsValidIndex(index))
	{
		FInventoryItem* Item = GetItem(index);
		--Item->Quantity;
		if (Item->Quantity == 0)
		{
			GetItems().RemoveAt(index);
			GetItems().SetNum(9);
		}
		RefreshInventory();
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Mamy problem"));
	}
}

TArray<FInventoryItem>& UInventoryComponent::GetItems()
{
	if (UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		return MyGameInstance->Items;
	}
	return Items;
}

FInventoryItem* UInventoryComponent::GetItem(int index)
{
	if (UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		return &MyGameInstance->Items[index];
	}
	return nullptr;
}

void UInventoryComponent::SpawnItem(int index)
{
	APawn* PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerCharacter) return;
	
	FVector ForwardVector = PlayerCharacter->GetActorForwardVector();
	FVector SpawnLocation = PlayerCharacter->GetActorLocation() + ForwardVector * 100.0f; // 100 cm to 1 metr
	FRotator ActorRotation = PlayerCharacter->GetActorRotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	APickUpItem* PickUpItem = GetWorld()->SpawnActor<APickUpItem>(APickUpItem::StaticClass(), SpawnLocation, ActorRotation, SpawnParams);

	FInventoryItem Item =* GetItem(index);
	Item.Quantity = 1;
	PickUpItem->StaticMeshComponent->SetStaticMesh(Item.Mesh);
	PickUpItem->StaticMeshComponent->SetSimulatePhysics(true);
	if (PickUpItem)
	{
		UE_LOG(LogTemp, Display, TEXT("spawned"));
		PickUpItem->ItemStructure = Item;
	}

	if (Item.SpawnSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), Item.SpawnSound, SpawnLocation);
	}

	RemoveItem(index);
}


bool UInventoryComponent::GetDebugMode() const
{
	if (UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		return MyGameInstance->bDebug;
	}
	return false;
}

float UInventoryComponent::GetDebugDrawLifeTime() const
{
	if (UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		return MyGameInstance->fDebugDrawLifeTime;
	}
	return 2.0f;
}

void UInventoryComponent::mDrawSphere(FVector MidPoint, float SphereRadius) const
{
	if (GetDebugMode())
	{
		DrawDebugSphere(GetWorld(), MidPoint, SphereRadius, 12, FColor::MakeRandomColor(), false, GetDebugDrawLifeTime());
	}
}


void UInventoryComponent::log(FString msg) const
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::MakeRandomColor(), msg);
}
