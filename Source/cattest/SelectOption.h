// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SelectOption.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct FSelectOption
{
	GENERATED_BODY()
	

	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Option")
	FText Label;
};
