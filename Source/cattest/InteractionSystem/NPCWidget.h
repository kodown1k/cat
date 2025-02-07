// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "NameableInterface.h"
#include "Components/TextBlock.h"
#include "NPCWidget.generated.h"


/**
 * 
 */
UCLASS()
class CATTEST_API UNPCWidget : public UCommonUserWidget, public INameableInterface
{
	GENERATED_BODY()
public:
    // Implementacja metody z interfejsu
    UFUNCTION()
    virtual void SetName(const FString& Name) override;

    virtual void NativeConstruct() override;

    UPROPERTY(EditAnywhere, meta = (BindWidget))
    UTextBlock* NameTextBlock;

protected:
    // Referencja do TextBlock w blueprintcie
    
	
};
