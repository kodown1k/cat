#include "FireBallProjectile.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

#include "../StatComponent.h"


#include "DrawDebugHelpers.h" // Debugowanie, je�li chcesz zobaczy�, jak dzia�a kod

// Sets default values
AFireBallProjectile::AFireBallProjectile()
{
    AreaDamageRadius = 100;
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

    // Inicjalizacja zdarzenia kolizji
   
}

void AFireBallProjectile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Mo�esz doda� tutaj kod do wykonywania dzia�a� co klatk� (np. ruch, efekty, itp.)
}

void AFireBallProjectile::OnHit(
    UPrimitiveComponent* HitComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    FVector NormalImpulse,
    const FHitResult& Hit)
{
    // Sprawd�, czy system Niagara dla wybuchu jest przypisany
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

    // Wy�wietlenie sfery obszaru eksplozji (debugowanie)
    DrawDebugSphere(GetWorld(), Hit.ImpactPoint, AreaDamageRadius, 100, FColor::Red, false, 2.0f);

    // Zdefiniowanie kszta�tu eksplozji (sfera)
    FCollisionShape CollisionShape;
    CollisionShape.SetSphere(AreaDamageRadius);  // Promie� eksplozji

    // Parametry zapytania kolizji
    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this); // Ignorowanie naszego pocisku

    // Wyniki zapytania o kolizje
    TArray<FHitResult> OverlapResults;

    // Wykonanie zapytania o kolizj� w obszarze wybuchu
    bool bHit = GetWorld()->SweepMultiByChannel(
        OverlapResults,                         // Tablica wynik�w overlapu
        Hit.ImpactPoint,                        // Punkt, w kt�rym nast�puje eksplozja
        Hit.ImpactPoint,                        // Punkt pocz�tkowy
        FQuat::Identity,                        // Brak rotacji
        ECC_GameTraceChannel1,                           // Kana� kolizji (np. kana� eksplozji)
        CollisionShape,                         // Kszta�t eksplozji
        QueryParams                             // Parametry zapytania
    );

    // Obs�uga wynik�w
    if (bHit)
    {
        // Iteracja po wynikach overlapu
        for (const FHitResult& OverlapResult : OverlapResults)
        {
            AActor* OverlappedActor = OverlapResult.GetActor();
            if (OverlappedActor && OverlappedActor != this)
            {
                // Sprawdzamy, czy aktor posiada komponent StatComponent
                UStatComponent* StatComponent = OverlappedActor->FindComponentByClass<UStatComponent>();
                if (StatComponent)
                {
                    StatComponent->GetDamaged(Damage);  // Zadaj obra�enia
                }
            }
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