#include "PickUpItem.h"
#include "Components/SphereComponent.h"

APickUpItem::APickUpItem()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	RootComponent = StaticMeshComponent;
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereCollision->SetupAttachment(StaticMeshComponent);
	SetupCollisions();
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFinder(TEXT("/Script/Engine.Material'/Game/Material/M_Outline.M_Outline'"));

	if (MaterialFinder.Succeeded())
	{
		OverlayMaterial = MaterialFinder.Object;
		DynamicMaterial = UMaterialInstanceDynamic::Create(OverlayMaterial, this);
		DynamicMaterial->SetScalarParameterValue(TEXT("LineThickness"), 0.0f);
		StaticMeshComponent->SetOverlayMaterial(DynamicMaterial);
	}
}


void APickUpItem::BeginPlay()
{
	Super::BeginPlay();
}

void APickUpItem::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (StaticMeshComponent && ItemStructure.Mesh)
	{
		StaticMeshComponent->SetStaticMesh(ItemStructure.Mesh);
		StaticMeshComponent->SetSimulatePhysics(true);
	}
}


void APickUpItem::SetupCollisions()
{
	SphereCollision->InitSphereRadius(100.0f);
	SphereCollision->BodyInstance.SetCollisionProfileName("Item");
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &APickUpItem::OnOverlapBegin);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &APickUpItem::OnOverlapEnd);
}

void APickUpItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (CurrentLineThickness != TargetLineThickness)
	{
		CurrentLineThickness = FMath::FInterpTo(CurrentLineThickness, TargetLineThickness, DeltaTime, LerpSpeed);
		if (DynamicMaterial)
		{
			DynamicMaterial->SetScalarParameterValue(TEXT("LineThickness"), CurrentLineThickness);
		}
	}
}

void APickUpItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                 const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this))
	{
		TargetLineThickness = MaxTargetThickness;
		LerpSpeed = TargetLineThickness - CurrentLineThickness;
		bIsOverlapping = true;
	}
}

void APickUpItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	TargetLineThickness = 0.0f;
	LerpSpeed = 2.0f;
	bIsOverlapping = false;
}


void APickUpItem::log(FString msg) const
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::MakeRandomColor(), msg);
}
