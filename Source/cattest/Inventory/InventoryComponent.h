// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "InputAction.h"
#include "InventoryItemStructure.h"
#include "InventoryPanel.h"
class UInventorySlot;
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


class UHorizontalBox;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CATTEST_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "UI", meta = (BindWidget))
	TSubclassOf<UUserWidget> InventoryWidgetClass;

	UPROPERTY(EditAnywhere, Category = "UI", meta = (BindWidget))
	TSubclassOf<UUserWidget> InventoryWidgetSlotClass;

	/** ACTIONS */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InventoryAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PickUpAction;

public:
	UInventoryComponent();

	void SetupPlayerInputComponent();
	void RemoveItem(int index);

protected:
	virtual void BeginPlay() override;

	// Dodaje puste sloty w inventory
	void InitializeInventory();
	void ToggleVisibilityInventory();
	void PickupItem();
	void AddItem(FInventoryItem Item);

	// Uzupełnia i dodaje sloty w inventory (OnionsBox) na podstawie Items. 
	void RefreshInventory();

public:
	void log(FString msg) const;

private:
	UPROPERTY(EditAnywhere)
	float GrabRange = 200.0f;

	// Obiekty w inventory
	TArray<FInventoryItem> Items;

	// wykrywania kolizje w formie sferycznego promienia
	TArray<FHitResult> SphereTrace();
	TArray<FHitResult> LineTrace();

	UPROPERTY()
	UInventoryPanel* InventoryWidget;


	bool isVisible = true;
	bool mDebug = false;
	void mDrawSphere(FVector MidPoint, float SphereRadius) const;
};
