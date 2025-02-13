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
    void BeginPlay();
    // Funkcja do wczytania dialogów z DataTable
    void LoadDialogueData(UDataTable* DialogueDataTable, int32 NPC_ID, TSubclassOf<UDialogueWidget> NewWidgetClass);

    // Funkcja do wyœwietlenia dialogu
    void ShowDialogueWidget();

    // Funkcja do ustawienia klasy widgetu
    void SetDialogueWidgetClass(TSubclassOf<UDialogueWidget> NewWidgetClass);

    UFUNCTION()
    void EnablePlayerMovement();
    void UpdateQuest();
    UFUNCTION()
    void DisablePlayerMovement();
    UFUNCTION()
    void HandleDialogueQuest(bool activateQuest, int32 questID); //DODAJE QUESTA
    UFUNCTION()
    void HandleDialogueQuestCompleted(bool activateQuest, int32 questID);//KONCZY QUESTA

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) //referencja do gracza
    ACharacter* PlayerCharacter;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    TSubclassOf<UDialogueWidget> DialogueWidgetClass;
    UPROPERTY()
    TObjectPtr<UDialogueWidget> DialogueWidget;

private:
    TArray<FDialogStruct*> DialogOptions;
    int32 CurrentDialogueIndex;

    

};


