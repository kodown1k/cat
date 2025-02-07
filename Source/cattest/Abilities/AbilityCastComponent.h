// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputModule.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "USpellBase.h"
#include "../cattestCharacter.h"

#include "AbilityCastComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CATTEST_API UAbilityCastComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAbilityCastComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	float LastCastTime; // Czas ostatniego rzucenia czaru

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	float CooldownTime; // Czas odnowienia w sekundach


	


	void CastCurrentSpell();
	void SetCurrentSpell(TSubclassOf<USpellBase> NewSpell);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	TSubclassOf<USpellBase> CurrentSpell;
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* CastAbilityAction;

	

	

};
