#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "InventoryItemStructure.h"
#include "InventorySlot.generated.h"


class UInventoryComponent;

/**
 * Slot na itemy w inventory 
 */
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

	void SetInventoryComponent(UInventoryComponent* InventoryComponent);

protected:
	virtual void NativePreConstruct() override;

private:
	UFUNCTION()
	void OnItemButtonClicked();
	UInventoryComponent* m_inventoryComponent;
};