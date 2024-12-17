#include "InventorySlot.h"

#include "PickUpItem.h"
#include "Kismet/GameplayStatics.h"

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
	FVector Start;
	FRotator CameraRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Start, CameraRotation);

	UE_LOG(LogTemp, Display, TEXT("Clicked"));

	FActorSpawnParameters SpawnParams;

	APickUpItem* PickUpItem = GetWorld()->SpawnActor<APickUpItem>(APickUpItem::StaticClass(), Start + FVector(100, 0, 0), CameraRotation, SpawnParams);

	PickUpItem->StaticMeshComponent->SetStaticMesh(SItem.Mesh);
	PickUpItem->StaticMeshComponent->SetSimulatePhysics(true);
	if (PickUpItem)
	{
		UE_LOG(LogTemp, Display, TEXT("spawned"));
		PickUpItem->ItemStructure = SItem;
	}

	if (SItem.SpawnSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SItem.SpawnSound, Start);
	}

	// if (UInventoryComponent* InventoryComponent = GetWorld()->GetFirstPlayerController()->GetComponentByClass<UInventoryComponent>())
	// {
	// 	UE_LOG(LogTemp, Display, TEXT("Inventory Component Getted"));
	// 	// InventoryComponent->RemoveItem(index);
	// }
}
