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

	FVector Start = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FRotator ActorRotation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorRotation();

	bool bNoCollisionFail = true;
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = bNoCollisionFail
		                                             ? ESpawnActorCollisionHandlingMethod::AlwaysSpawn
		                                             : ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	APickUpItem* PickUpItem = GetWorld()->SpawnActor<APickUpItem>(APickUpItem::StaticClass(), Start + FVector(200, 200, 200), ActorRotation, SpawnParams);

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

	m_inventoryComponent->RemoveItem(index);
}
