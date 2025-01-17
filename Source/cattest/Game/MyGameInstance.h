// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CATTEST_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMyGameInstance();

	UFUNCTION(exec)
	void SetDebug(bool Debug);

	UFUNCTION(exec)
	void GetDebug();

	UFUNCTION(exec)
	void SetDebugDrawLifeTime(float Time);
	
	UPROPERTY(BlueprintReadWrite, Category = "Debug")
	bool bDebug;
	UPROPERTY(BlueprintReadWrite, Category = "Debug")
	float fDebugDrawLifeTime = 5.0f;
};
