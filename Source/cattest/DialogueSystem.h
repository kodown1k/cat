#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DialogueWidget.h"
#include "DialogStruct.h"
#include "UObject/ConstructorHelpers.h"
#include "DialogueSystem.generated.h"

class UDialogueWidget;

UCLASS()
class CATTEST_API UDialogueSystem : public UObject
{
    GENERATED_BODY()

public:
    UDialogueSystem();

    // Funkcja do wczytania dialogów z DataTable
    void LoadDialogueData(UDataTable* DialogueDataTable, int32 NPC_ID, TSubclassOf<UDialogueWidget> NewWidgetClass);

    // Funkcja do wyœwietlenia dialogu
    void ShowDialogueWidget();

    // Funkcja do ustawienia klasy widgetu
    void SetDialogueWidgetClass(TSubclassOf<UDialogueWidget> NewWidgetClass);

    void EnablePlayerMovement();
    void DisablePlayerMovement();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    TSubclassOf<UDialogueWidget> DialogueWidgetClass;

    UDialogueWidget* DialogueWidget;

private:
    TArray<FDialogStruct*> DialogOptions;
    int32 CurrentDialogueIndex;

    

};

