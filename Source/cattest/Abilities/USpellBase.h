// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "USpellBase.generated.h"

/**
 * klasa bazowa dla reszty umiejetnosci
 */
UCLASS(Abstract, Blueprintable)
class CATTEST_API USpellBase : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	FString SpellName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	float manacost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	bool spellLearned;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	float castingTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	float damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	float speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spell")
	bool projectile;
	

	UFUNCTION(BlueprintNativeEvent, Category = "Spell")
	void CastSpell(AActor* Caster);



	
};
