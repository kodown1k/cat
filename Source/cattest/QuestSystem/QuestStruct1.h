// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "QuestStruct1.generated.h"

/**
 * 
 */

 // Definicja typu questa
UENUM(BlueprintType)
enum class EQuestType : uint8
{
    Collect UMETA(DisplayName = "Collect Items"),
    Kill UMETA(DisplayName = "Kill Enemies"),
    Talk UMETA(DisplayName = "Talk to NPC"),
    Move UMETA(DisplayName = "Move to Location"),
    Solve UMETA(DisplayName = "SolveTheProblem")
};

USTRUCT(BlueprintType)
struct CATTEST_API FQuestStruct1
{
    GENERATED_BODY()
public:
	FQuestStruct1();
	~FQuestStruct1();


public:
    // Nazwa questa
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    FString QuestName;

    // Opis questa
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    FString Description;

    // Liczba wymaganych przedmiotów / zabitych wrogów
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    int32 RequiredAmount;

    // Aktualny postêp questa
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    int32 CurrentProgress;

    // Czy quest jest ukoñczony?
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    bool bIsCompleted;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    bool bIsActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    EQuestType QuestType;   // Domyœlnie quest zbierania
   
};
