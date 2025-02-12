#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "GameplayTags.h"  // Konieczne dla tagów
#include "DialogStruct.generated.h"  // To makro wygeneruje kod specyficzny dla Unreal Engine

// Struktura do u¿ywania w DataTable
USTRUCT(BlueprintType)
struct FDialogStruct : public FTableRowBase
{
    GENERATED_BODY()  // To makro generuje kod niezbêdny dla Unreal Engine


        // ID dialogu
   // ID wiersza dialogowego
        UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ID;

    // Czy to NPC mówi (true) czy gracz (false)
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsNPC;

    // Tekst do wyœwietlenia
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Text;

    // Opcje dialogowe (0 - przejœcie do nastêpnego wiersza, -1 - zakoñczenie rozmowy, >0 - dostêpne opcje)
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Options;

    // Flaga czy pokazujemy tekst lub opcje
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bShow;

    // ID wiersza, do którego przejdzie NPC po wybraniu opcji
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 NextID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool ActivateQuest;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ActivateQuestID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool isQuestRelated;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 questID;
    
    

    


};