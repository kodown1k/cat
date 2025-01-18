// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "FireBallProjectile.generated.h"

UCLASS()
class CATTEST_API AFireBallProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFireBallProjectile();

protected:
    // Komponent kolizji;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USphereComponent* CollisionComponent;

    // Komponent ruchu
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UProjectileMovementComponent* ProjectileMovement;

    // Obra¿enia pocisku
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
    float Damage;

    // Wywo³ane przy kolizji
    UFUNCTION()
    void OnHit(
        UPrimitiveComponent* HitComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        FVector NormalImpulse,
        const FHitResult& Hit);

    virtual void BeginPlay() override;

public:    
    // Wywo³ane co klatkê
    virtual void Tick(float DeltaTime) override;

};
