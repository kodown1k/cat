#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "QuestStruct1.h"
#include "CommonTextBlock.h"
#include "CommonUserWidget.h"
#include "W_QuestEntry.generated.h"


UCLASS()
class CATTEST_API UW_QuestEntry : public UCommonUserWidget
{
    GENERATED_BODY()

public:

    // Nazwa questa
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    TObjectPtr<UCommonTextBlock> QuestName;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    TObjectPtr<UCommonTextBlock> DescriptionText; // Dla opisu questa

    // Liczba wymaganych przedmiotów / zabitych wrogów
    UPROPERTY(BlueprintReadOnly)
    int32 RequiredAmount;

    // Aktualny postêp questa
    UPROPERTY(BlueprintReadOnly)
    int32 CurrentProgress;

    // Funkcje do pobrania danych w Blueprints
    
   

    UFUNCTION(BlueprintCallable)
    int32 GetRequiredAmount() const { return RequiredAmount; }

    UFUNCTION(BlueprintCallable)
    int32 GetCurrentProgress() const { return CurrentProgress; }
};
