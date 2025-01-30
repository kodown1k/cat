// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	bDebug = false;
}

/**
 * Czy debugowac?
 */
void UMyGameInstance::SetDebug(bool Debug)
{
	bDebug = Debug;
	UE_LOG(LogTemp, Log, TEXT("Debug mode set to: %s"), bDebug ? TEXT("true") : TEXT("false"));
}

void UMyGameInstance::GetDebug()
{
	if (GEngine)
	{
		const FString DebugMessage = FString::Printf(TEXT("Debug mode is: %s"), bDebug ? TEXT("true") : TEXT("false"));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, DebugMessage);
	}
}

void UMyGameInstance::SetDebugDrawLifeTime(float Time)
{
	fDebugDrawLifeTime = Time;
}
