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
}


void APickUpItem::BeginPlay()
{
	Super::BeginPlay();
	DefaultOverlayMaterial = StaticMeshComponent->GetOverlayMaterial();
	if (OutlineMaterial)
	{
		DynamicMaterial = UMaterialInstanceDynamic::Create(OutlineMaterial, this);
		DynamicMaterial->SetScalarParameterValue(FName("LineThickness"), 0.0f);
		StaticMeshComponent->SetOverlayMaterial(DynamicMaterial);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("OutlineMaterial is not set!"));
	}
}

void APickUpItem::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	StaticMeshComponent->SetOverlayMaterial(DefaultOverlayMaterial);
}


void APickUpItem::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (StaticMeshComponent && ItemStructure.Mesh)
	{
		StaticMeshComponent->SetStaticMesh(ItemStructure.Mesh);
		StaticMeshComponent->SetSimulatePhysics(true);
		StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		StaticMeshComponent->SetCollisionResponseToAllChannels(ECR_Block);
	}
}


void APickUpItem::SetupCollisions()
{
	SphereCollision->InitSphereRadius(SphereCollisionRadius);
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
