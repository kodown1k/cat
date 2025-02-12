#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "GameplayTags.h"  // Konieczne dla tag�w
#include "DialogStruct.generated.h"  // To makro wygeneruje kod specyficzny dla Unreal Engine

// Struktura do u�ywania w DataTable
USTRUCT(BlueprintType)
struct FDialogStruct : public FTableRowBase
{
    GENERATED_BODY()  // To makro generuje kod niezb�dny dla Unreal Engine


        // ID dialogu
   // ID wiersza dialogowego
        UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ID;

    // Czy to NPC m�wi (true) czy gracz (false)
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsNPC;

    // Tekst do wy�wietlenia
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Text;

    // Opcje dialogowe (0 - przej�cie do nast�pnego wiersza, -1 - zako�czenie rozmowy, >0 - dost�pne opcje)
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Options;

    // Flaga czy pokazujemy tekst lub opcje
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bShow;

    // ID wiersza, do kt�rego przejdzie NPC po wybraniu opcji
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