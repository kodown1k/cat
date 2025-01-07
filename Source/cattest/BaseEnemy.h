// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseEnemy.generated.h"

UCLASS()
class CATTEST_API ABaseEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseEnemy();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	// Do usuniêcia
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Funkcja zwracaj¹ca bool czy postaæ nie¿yje
	UFUNCTION(BlueprintCallable)
	bool IsDead();

	// Zakres wzroku postaci
	UPROPERTY(EditDefaultsOnly, meta = (Category = "AI|Combat"))
	float SightRadius = 2000;
	// Odleg³oœæ poza któr¹ postaæ traci kontakt wzrokowy z wczeœniej zauwa¿onym aktorem
	UPROPERTY(EditDefaultsOnly, meta = (Category = "AI|Combat"))
	float LoseSightRadius = 2500;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Metoda wywo³ywany gdy postaæ ginie
	virtual void Death();
	// Metoda wywo³ywana gdy postaæ otrzymuje obra¿enia
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	// Maksymalna iloœæ punktów ¿ycia, ustawiane w Blueprincie
	UPROPERTY(BlueprintReadWrite, meta = (Category = "Enemy"))
	float MaxHealth = 100;
private:

	// Aktualna iloœæ ¿ycia
	float Health;
	// Flaga czy postaæ ¿yje
	bool bIsDead;

};
