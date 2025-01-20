#include "Fireball.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h" // Do obs³ugi rzutowania
#include "Components/SphereComponent.h"

UFireball::UFireball()
{
    SpellName = "Fireball";
    damage = 50.f;
    castingTime = 2.f;
    manacost = 20.f;
    projectile = true;
}

void UFireball::CastSpell_Implementation(AActor* Caster)
{
    

    if (!FireballProjectileClass || !Caster)
    {
        return;
    }

    // Pobranie kontrolera gracza
    APlayerController* LocalPlayerController = UGameplayStatics::GetPlayerController(Caster, 0);
    if (!LocalPlayerController)
    {
        return;
    }

    // Pobranie orientacji kamery
    FVector CameraLocation;
    FRotator CameraRotation;
    LocalPlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

    // Miejsce spawnowania pocisku (przed Casterem)
    FVector SpawnLocation = Caster->GetActorLocation() + CameraRotation.Vector() * 150.f;

    // Rotacja pocisku zgodna z kamer¹ gracza
    FRotator SpawnRotation = CameraRotation;

    // Tworzenie pocisku
    AFireBallProjectile* SpawnedProjectile = GetWorld()->SpawnActor<AFireBallProjectile>(
        FireballProjectileClass,
        SpawnLocation,
        SpawnRotation
    );

    if (SpawnedProjectile)
    {
        // Ustawienie w³aœciciela
        SpawnedProjectile->SetOwner(Caster);

        // Ignorowanie kolizji z w³aœcicielem
        if (USphereComponent* CollisionComponent = SpawnedProjectile->FindComponentByClass<USphereComponent>())
        {
            CollisionComponent->IgnoreActorWhenMoving(Caster, true);
        }

        UE_LOG(LogTemp, Warning, TEXT("Pocisk stworzony i ustawiono ignorowanie castera."));
    }
}
