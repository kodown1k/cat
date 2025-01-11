#include "PickUpItem.h"


APickUpItem::APickUpItem()
{
	PrimaryActorTick.bCanEverTick = true;

	// Tworzenie komponentu mesh
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent = StaticMeshComponent;
}


void APickUpItem::BeginPlay()
{
	Super::BeginPlay();
}

void APickUpItem::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// Przypisanie mesh z struktury do komponentu Static Mesh
	// UStaticMeshComponent* MeshComp = GetComponentByClass<UStaticMeshComponent>();

	if (StaticMeshComponent && ItemStructure.Mesh)
	{
		StaticMeshComponent->SetStaticMesh(ItemStructure.Mesh);
		StaticMeshComponent->SetSimulatePhysics(true);
	}
}


void APickUpItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
