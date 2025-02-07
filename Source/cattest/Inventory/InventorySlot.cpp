#include "inventorySlot.h"
#include "InventoryComponent.h"
#include "PickUpItem.h"
#include "Kismet/GameplayStatics.h"

void UInventorySlot::SetInventoryComponent(UInventoryComponent* InventoryComponent)
{
	m_inventoryComponent = InventoryComponent;
}

void UInventorySlot::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (itembuttom)
	{
		itembuttom->OnClicked.AddDynamic(this, &UInventorySlot::OnItemButtonClicked);
	}

	if (SItem.Thumbnail)
	{
		itemimage->SetVisibility(ESlateVisibility::Visible);
		itemimage->SetBrushFromTexture(SItem.Thumbnail);
	}
	else
	{
		itemimage->SetVisibility(ESlateVisibility::Collapsed);
	}

	itemquantity->SetText(FText::FromString(FString::FromInt(SItem.Quantity)));
	itemquantity->SetVisibility(ESlateVisibility::Hidden);
	if (SItem.Quantity > 1)
	{
		itemquantity->SetVisibility(ESlateVisibility::Visible);
	}
}

void UInventorySlot::OnItemButtonClicked()
{
	if (SItem.Quantity <= 0)
	{
		return;
	}
	
	m_inventoryComponent->SpawnItem(index);
}
