#include "FireBallProjectile.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

#include "StatComponent.h"


#include "DrawDebugHelpers.h" // Debugowanie, jeœli chcesz zobaczyæ, jak dzia³a kod

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

    // Ustawiamy domyœln¹ wartoœæ obra¿eñ
    Damage = 50.f;
}

void AFireBallProjectile::BeginPlay()
{
    Super::BeginPlay();

    FVector SpawnLocation = GetActorLocation();
    FHitResult HitResult;
    FCollisionQueryParams CollisionParams;

    // Tworzymy kszta³t sweepa - w tym przypadku kula
    FCollisionShape CollisionShape;
    CollisionShape.SetSphere(15.0f); // Promieñ kuli w zale¿noœci od wielkoœci Twojego pocisku

    // Sweep sprawdzaj¹cy kolizjê
    bool bHit = GetWorld()->SweepSingleByChannel(HitResult, SpawnLocation, SpawnLocation, FQuat::Identity, ECC_Visibility, CollisionShape, CollisionParams);

    if (bHit)
    {
        // Jeœli pocisk uderza w coœ od razu, to przesuwamy go na trochê wy¿sze miejsce
        SetActorLocation(HitResult.ImpactPoint + FVector(0.f, 0.f, 20.f)); // Przesuniêcie w górê
    }

    // Ignorowanie kolizji z casterem
   
}

void AFireBallProjectile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Event wywo³any podczas kolizji
void AFireBallProjectile::OnHit(
    UPrimitiveComponent* HitComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    FVector NormalImpulse,
    const FHitResult& Hit)
{
    // SprawdŸ czy system Niagara dla wybuchu jest przypisany
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

    // Zadaj obra¿enia aktorowi, jeœli ma komponent obra¿eñ
    if (OtherActor && OtherActor != this)
    {
        UStatComponent* StatComponent = OtherActor->FindComponentByClass<UStatComponent>();
        if (StatComponent)
        {
            StatComponent->GetDamaged(Damage);
        }
    }

    // Opcjonalnie: Dodaj dŸwiêk wybuchu
    if (ExplosionSound)
    {
        UGameplayStatics::PlaySoundAtLocation(GetWorld(), ExplosionSound, Hit.ImpactPoint);
    }

    // Zniszcz pocisk po uderzeniu
    Destroy();
}