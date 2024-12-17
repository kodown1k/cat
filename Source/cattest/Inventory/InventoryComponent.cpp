#include "InventoryComponent.h"
#include "EnhancedInputComponent.h"
#include "InventoryPanel.h"
#include "InventorySlot.h"
#include "PickUpItem.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"


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

	InitializeInventory();
	SetupPlayerInputComponent();

	// if (MyActorInstance)
	// {
	// 	MyActorInstance->OnMyEvent.AddDynamic(this, &UInventoryComponent::RemoveItem);
	// }
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UInventoryComponent::InitializeInventory()
{
	Items.SetNum(6);

	if (IsValid(InventoryWidgetClass))
	{
		InventoryWidget = Cast<UInventoryPanel>(CreateWidget(GetWorld()->GetFirstPlayerController(), InventoryWidgetClass));
		if (InventoryWidget)
		{
			RefreshInventory();

			InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
			InventoryWidget->AddToViewport();
		}
	}
}


void UInventoryComponent::ToggleVisibilityInventory()
{
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		if (!InventoryWidget)
		{
			return;
		}

		if (InventoryWidget->IsVisible())
		{
			InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
			PlayerController->bShowMouseCursor = false;
			FInputModeGameOnly InputMode;
			PlayerController->SetInputMode(InputMode);
		}
		else
		{
			InventoryWidget->SetVisibility(ESlateVisibility::Visible);
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
	for (const FInventoryItem& item : Items)
	{
		if (auto Slot = Cast<UInventorySlot>(CreateWidget(InventoryWidget, InventoryWidgetSlotClass)))
		{
			Slot->SItem = item;
			Slot->index = index;
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
			if (mDebug)
			{
				FText name = PickUpItem->ItemStructure.Name;
				log(name.ToString());
			}

			AddItem(PickUpItem->ItemStructure);
			RefreshInventory();
			PickUpItem->Destroy();
			return;
		}
	}
}


TArray<FHitResult> UInventoryComponent::SphereTrace()
{
	TArray<FHitResult> HitResults;
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (!PlayerCharacter)
	{
		return HitResults;
	}

	FVector Start = PlayerCharacter->GetActorLocation() + FVector(100, 0, 0);
	FVector End = Start - FVector(0, 0, 65);

	float SphereRadius = 130.0f; // Promień sfery
	FCollisionQueryParams CollisionParams;
	CollisionParams.bTraceComplex = true;
	CollisionParams.AddIgnoredActor(PlayerCharacter); // Ignoruj siebie

	// Wykonaj tracing
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


/**
 * Dodaje item do inventory. Wyszukuje po nazwie (zwiększa ilość), jesli nie znajdzie po nazwie to doda do pierwsezgo miejsca  z ilością=0.
 * Jeśli nie znajdzie miejsca nic nie robi.
 */
void UInventoryComponent::AddItem(FInventoryItem Item)
{
	for (int32 i = 0; i < Items.Num(); ++i)
	{
		if (Items[i].Name.EqualTo(Item.Name) && Item.Stackable) // Czy mamy w inventory item z taka nazwa i jest stackable, wowczas zwiekszamy ilosc.
		{
			Items[i].Quantity += Item.Quantity;
			return;
		}
	}
	for (int32 i = 0; i < Items.Num(); ++i)
	{
		if (Items[i].Quantity == 0) // Dodajemy do pierwszego pustego miejsca
		{
			Items[i] = Item;
			return;
		}
	}

	// Jesli nie ma stworzonych nawet pustych slotow dodajemy w pierwsze miejsce.
	Items.Insert(Item, 0);
}

void UInventoryComponent::RemoveItem()
{
	// if (Items.IsValidIndex(index))
	// {
	// 	FInventoryItemStructure Item = Items[index];
	// 	UE_LOG(LogTemp, Display, TEXT("Removing Item: %s"), *Item.Name.ToString());
	// 	--Item.Quantity;
	// 	if (Item.Quantity == 0)
	// 	{
	// 		Items.RemoveAt(index);
	// 	}
	// 	RefreshInventory();
	// }
	// else
	// {
	UE_LOG(LogTemp, Display, TEXT("Mamy problem"));
	// }
}


void UInventoryComponent::mDrawSphere(FVector MidPoint, float SphereRadius) const
{
	if (mDebug)
	{
		DrawDebugSphere(GetWorld(), MidPoint, SphereRadius, 12, FColor::MakeRandomColor(), false, 10.0f);
	}
}


void UInventoryComponent::log(FString msg) const
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::MakeRandomColor(), msg);
}
