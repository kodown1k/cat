// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "EnhancedInputComponent.h"
#include "InventoryPanel.h"
#include "InventorySlot.h"
#include "PickUpItem.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UInventoryComponent::SetupPlayerInputComponent(UEnhancedInputComponent* EnhancedInputComponent)
{
	EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Triggered, this,
	                                   &UInventoryComponent::ToggleVisibilityInventory);
	EnhancedInputComponent->BindAction(PickUpAction, ETriggerEvent::Triggered, this,
	                                   &UInventoryComponent::PickupItem);
}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	InitializeInventory();
}

void UInventoryComponent::InitializeInventory()
{
	Items.SetNum(6);

	if (IsValid(InventoryWidgetClass))
	{
		InventoryWidget = Cast<UInventoryPanel>(CreateWidget(GetWorld(), InventoryWidgetClass));
		if (InventoryWidget)
		{
			InventoryWidget->AddToViewport();
			RefreshInventory();
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
	for (const FInventoryItemStructure& item : Items)
	{
		log(FString::FromInt(item.Quantity));
		if (auto Slot = Cast<UInventorySlot>(CreateWidget(InventoryWidget, InventoryWidgetSlotClass)))
		{
			Slot->SItem = item;

			InventoryWidget->OnionsBox->AddChildToHorizontalBox(Slot);
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

		if (InventoryWidget->IsInViewport())
		{
			InventoryWidget->RemoveFromParent();
			PlayerController->bShowMouseCursor = false;

			FInputModeGameOnly InputMode;
			PlayerController->SetInputMode(InputMode);
		}
		else
		{
			FInputModeGameAndUI InputMode;
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
			// InputMode.SetWidgetToFocus(InventoryWidget->TakeWidget());
			PlayerController->SetInputMode(InputMode);

			PlayerController->bShowMouseCursor = true;
			InventoryWidget->AddToViewport();
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

	FVector Start = PlayerCharacter->GetActorLocation(); // Lokalizacja postaci
	FVector End = Start - FVector(0, 0, 65);
	// Przesunięcie w dół o 65 jednostek, to mozna uzaleznić od kierunku patrzenia.

	float SphereRadius = 130.0f; // Promień sfery
	FCollisionQueryParams CollisionParams;
	CollisionParams.bTraceComplex = true;
	CollisionParams.AddIgnoredActor(PlayerCharacter); // Ignoruj siebie

	// Wykonaj tracing
	bool bHit = GetWorld()->SweepMultiByChannel(
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

void UInventoryComponent::mDrawSphere(FVector MidPoint, float SphereRadius) const
{
	if (mDebug)
	{
		DrawDebugSphere(GetWorld(), MidPoint, SphereRadius, 12, FColor::MakeRandomColor(), false, 10.0f);
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
		}
	}
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


/**
 * Dodaje item do inventory. Wyszukuje po nazwie (zwiększa ilość), jesli nie znajdzie po nazwie to doda do pierwsezgo miejsca  z ilością=0.
 * Jeśli nie znajdzie miejsca nic nie robi.
 */
void UInventoryComponent::AddItem(FInventoryItemStructure Item)
{
	log("asdf");
	for (int32 i = 0; i < Items.Num(); ++i)
	{
		if (Items[i].Name.EqualTo(Item.Name))
		{
			Items[i].Quantity += Item.Quantity;
			return;
		}
	}
	for (int32 i = 0; i < Items.Num(); ++i)
	{
		if (Items[i].Quantity == 0)
		{
			Items[i] = Item;
			return;
		}
	}

	Items.Insert(Item, 0);
}

void UInventoryComponent::log(FString msg) const
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::MakeRandomColor(), msg);
}
