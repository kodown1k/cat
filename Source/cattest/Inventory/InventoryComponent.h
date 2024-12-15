// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "InventoryPanel.h"
#include "Components/ActorComponent.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "InventoryComponent.generated.h"


class UHorizontalBox;

/** Struktura obiektu w inventory */
USTRUCT(BlueprintType)
struct FInventoryItemStructure
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Name"))
	FText Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Stackable", MakeStructureDefaultValue="False"))
	bool Stackable;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Quantity", MakeStructureDefaultValue="0"))
	int32 Quantity = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Thumbnail", MakeStructureDefaultValue="None"))
	TObjectPtr<UTexture2D> Thumbnail;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Mesh", MakeStructureDefaultValue="None"))
	TObjectPtr<UStaticMesh> Mesh;
};


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
	class UInputAction* InventoryAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* PickUpAction;

public:
	UInventoryComponent();

	void SetupPlayerInputComponent(UEnhancedInputComponent* EnhancedInputComponent);

protected:
	virtual void BeginPlay() override;

	// Dodaje puste sloty w inventory
	void InitializeInventory();
	void ToggleVisibilityInventory();
	void PickupItem();
	void AddItem(FInventoryItemStructure Item);
	// Uzupełnia i dodaje sloty w inventory (OnionsBox) na podstawie Items. 
	void RefreshInventory();

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void log(FString msg) const;

private:
	// Obiekty w inventory
	TArray<FInventoryItemStructure> Items;
	// wykrywania kolizje w formie sferycznego promienia
	TArray<FHitResult> SphereTrace();

	UInventoryPanel* InventoryWidget;

	bool mDebug = true;
	void mDrawSphere(FVector MidPoint, float SphereRadius) const;
};
