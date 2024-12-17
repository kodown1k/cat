#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"


#include "InventorySlot.generated.h"

/** Struktura obiektu w inventory */
USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()
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

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="SpawnSound", MakeStructureDefaultValue="None"))
	USoundBase* SpawnSound;
};

/**
 * Slot na itemy w inventory 
 */
// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMyDelegate, int, Index);

UCLASS()
class CATTEST_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FInventoryItem SItem;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	UImage* itemimage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	UTextBlock* itemquantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	UButton* itembuttom;

	int index;

	// UPROPERTY(BlueprintAssignable)
	// FMyDelegate OnMyEvent;

protected:
	virtual void NativePreConstruct() override;

private:
	UFUNCTION()
	void OnItemButtonClicked();
};
