#include "FireBallProjectile.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

#include "StatComponent.h"


#include "DrawDebugHelpers.h" // Debugowanie, je�li chcesz zobaczy�, jak dzia�a kod

// Sets default values
AFireBallProjectile::AFireBallProjectile()
{
    PrimaryActorTick.bCanEverTick = true;

    // Tworzymy komponent kolizji
    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    CollisionComponent->InitSphereRadius(15.0f);
    CollisionComponent->SetCollisionProfileName(TEXT("BlockAll"));
    CollisionComponent->OnComponentHit.AddDynamic(this, &AFireBallProjectile::OnHit);
    RootComponent = CollisionComponent;

    // Tworzymy komponent ruchu
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
    ProjectileMovement->UpdatedComponent = CollisionComponent;
    ProjectileMovement->InitialSpeed = 1500.f;
    ProjectileMovement->MaxSpeed = 1500.f;
    ProjectileMovement->ProjectileGravityScale = 0.1f;
    ProjectileMovement->bRotationFollowsVelocity = false;
    ProjectileMovement->bShouldBounce = false;

    // Ustawiamy domy�ln� warto�� obra�e�
    Damage = 50.f;
}

void AFireBallProjectile::BeginPlay()
{
    Super::BeginPlay();

    FVector SpawnLocation = GetActorLocation();
    FHitResult HitResult;
    FCollisionQueryParams CollisionParams;

    // Tworzymy kszta�t sweepa - w tym przypadku kula
    FCollisionShape CollisionShape;
    CollisionShape.SetSphere(15.0f); // Promie� kuli w zale�no�ci od wielko�ci Twojego pocisku

    // Sweep sprawdzaj�cy kolizj�
    bool bHit = GetWorld()->SweepSingleByChannel(HitResult, SpawnLocation, SpawnLocation, FQuat::Identity, ECC_Visibility, CollisionShape, CollisionParams);

    if (bHit)
    {
        // Je�li pocisk uderza w co� od razu, to przesuwamy go na troch� wy�sze miejsce
        SetActorLocation(HitResult.ImpactPoint + FVector(0.f, 0.f, 20.f)); // Przesuni�cie w g�r�
    }

    // Ignorowanie kolizji z casterem
   
}

void AFireBallProjectile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Event wywo�any podczas kolizji
void AFireBallProjectile::OnHit(
    UPrimitiveComponent* HitComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    FVector NormalImpulse,
    const FHitResult& Hit)
{
    // Sprawd� czy system Niagara dla wybuchu jest przypisany
    if (ExplosionEffect)
    {
        // Spawnuje system Niagara w miejscu kolizji
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(
            GetWorld(),
            ExplosionEffect,
            Hit.ImpactPoint,
            FRotator::ZeroRotator
        );
    }
    DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 100, 100, FColor::Red, false, 2.0f);

    // Zadaj obra�enia aktorowi, je�li ma komponent obra�e�
    if (OtherActor && OtherActor != this)
    {
        UStatComponent* StatComponent = OtherActor->FindComponentByClass<UStatComponent>();
        if (StatComponent)
        {
            StatComponent->GetDamaged(Damage);
        }
    }

    // Opcjonalnie: Dodaj d�wi�k wybuchu
    if (ExplosionSound)
    {
        UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, Hit.ImpactPoint);
    }

    // Zniszcz pocisk po uderzeniu
    Destroy();
}