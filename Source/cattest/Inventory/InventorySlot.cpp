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

	APawn* PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerCharacter) return;
	
	FVector ForwardVector = PlayerCharacter->GetActorForwardVector();
	FVector SpawnLocation = PlayerCharacter->GetActorLocation() + ForwardVector * 100.0f; // 100 cm to 1 metr
	FRotator ActorRotation = PlayerCharacter->GetActorRotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	APickUpItem* PickUpItem = GetWorld()->SpawnActor<APickUpItem>(APickUpItem::StaticClass(), SpawnLocation, ActorRotation, SpawnParams);
	
	PickUpItem->StaticMeshComponent->SetStaticMesh(SItem.Mesh);
	PickUpItem->StaticMeshComponent->SetSimulatePhysics(true);
	if (PickUpItem)
	{
		UE_LOG(LogTemp, Display, TEXT("spawned"));
		PickUpItem->ItemStructure = SItem;
	}

	if (SItem.SpawnSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), SItem.SpawnSound, SpawnLocation);
	}

	m_inventoryComponent->RemoveItem(index);
}
