// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	

	UE_LOG(LogTemp, Warning, TEXT("Hello========================"));
	Health = MaxHealth;
}

void ABaseEnemy::Death()
{
	UE_LOG(LogTemp, Warning, TEXT("Actor Dies"));
	bIsDead = true;
	DetachFromControllerPendingDestroy();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetSimulatePhysics(true);
	SetLifeSpan(5);
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float ABaseEnemy::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	UE_LOG(LogTemp, Warning, TEXT("Actor takes damage: %f"), DamageToApply);

	float tmpHealth = Health;
	float damageApplied = 0.0f;
	if (DamageToApply >= Health)
	{
		Health = 0;
		damageApplied = DamageToApply - tmpHealth;
		UE_LOG(LogTemp, Warning, TEXT("Character is killed"), DamageToApply);
		Death();
	}
	else
	{
		Health -= DamageToApply;
		damageApplied = DamageToApply;
		UE_LOG(LogTemp, Warning, TEXT("Actor life: %f"), Health);
	}
	return damageApplied;
}

bool ABaseEnemy::IsDead()
{
	return bIsDead;
}

