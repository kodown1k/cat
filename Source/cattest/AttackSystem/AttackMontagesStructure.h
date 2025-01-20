
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackMontagesStructure.generated.h"


USTRUCT(BlueprintType)
struct FAttackMontagesStructure
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimMontage* AttackMontages;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	USoundBase* AttackSound;
};
