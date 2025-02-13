#include "DialogueSystem.h"
#include "DialogueWidget.h"
#include "ButtonDialogueWidget.h"
#include <Kismet/GameplayStatics.h>
#include "StoryComponent.h"

UDialogueSystem::UDialogueSystem()
{
    // Inicjalizacja wartoœci domyœlnych
    CurrentDialogueIndex = 0;
}



void UDialogueSystem::LoadDialogueData(UDataTable* DialogueDataTable, int32 NPC_ID, TSubclassOf<UDialogueWidget> NewWidgetClass)
{
    SetDialogueWidgetClass(NewWidgetClass);

    if (!DialogueDataTable)
    {
        UE_LOG(LogTemp, Warning, TEXT("Dialogue DataTable is null!"));
        return;
    }

    // Za³aduj dane z DataTable
    TArray<FName> RowNames = DialogueDataTable->GetRowNames();
    TArray<FDialogStruct*> LoadedDialogOptions;

    for (const FName& RowName : RowNames)
    {
        FDialogStruct* Row = DialogueDataTable->FindRow<FDialogStruct>(RowName, TEXT(""));
        if (Row)
        {
            LoadedDialogOptions.Add(Row);
        }
    }

    // Ustawiamy za³adowane opcje
    DialogOptions = LoadedDialogOptions;

    // Uruchomienie dialogu
    ShowDialogueWidget();
}


void UDialogueSystem::ShowDialogueWidget()
{
    if (!DialogueWidget) // Tworzenie widgetu tylko raz
    {
        if (UWorld* World = GetWorld())
        {
            if (DialogueWidgetClass)
            {
                DialogueWidget = CreateWidget<UDialogueWidget>(World, DialogueWidgetClass);
                if (DialogueWidget)
                {
                    DialogueWidget->OnDialogueClosed.AddDynamic(this, &UDialogueSystem::EnablePlayerMovement);
                    DialogueWidget->OnDialogueQuest.AddDynamic(this, &UDialogueSystem::HandleDialogueQuest);
                    DialogueWidget->OnDialogueQuestCompleted.AddDynamic(this, &UDialogueSystem::HandleDialogueQuestCompleted);
                    
                    DialogueWidget->SetVisibility(ESlateVisibility::Hidden); // Ukryty na start

                    UE_LOG(LogTemp, Log, TEXT("Widget created and added to viewport."));
                }
            }
        }
    }

    if (DialogueWidget)
    {
        DisablePlayerMovement();
        DialogueWidget->AddToViewport();
        
        DialogueWidget->SetVisibility(ESlateVisibility::Visible);
        DialogueWidget->PopulateDialogueOptions(DialogOptions, CurrentDialogueIndex);
        
    }
}

void UDialogueSystem::SetDialogueWidgetClass(TSubclassOf<UDialogueWidget> NewWidgetClass)
{
    DialogueWidgetClass = NewWidgetClass;
}

void UDialogueSystem::DisablePlayerMovement()
{
    if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
    {
        // Ustawienie tylko trybu UI
        FInputModeUIOnly InputMode;
        if (DialogueWidget && DialogueWidget->IsValidLowLevel())
        {
            InputMode.SetWidgetToFocus(DialogueWidget->TakeWidget());
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("DialogueWidget is null or invalid!"));
        }

        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        PlayerController->SetInputMode(InputMode);

        // Poka¿ kursor myszy
        PlayerController->bShowMouseCursor = true;

        // Zablokuj ruch postaci (mo¿esz ukryæ to w metodzie gracza)
        if (APawn* ControlledPawn = PlayerController->GetPawn())
        {
            ControlledPawn->DisableInput(PlayerController);
        }
    }
}

void UDialogueSystem::HandleDialogueQuest(bool activateQuest, int32 questID)
{
    if (activateQuest)
    {
        UE_LOG(LogTemp, Warning, TEXT("Activating Quest: %d"), questID);
        if (!PlayerCharacter) {
            PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
        }
        if (PlayerCharacter)
        {
            UE_LOG(LogTemp, Warning, TEXT("Found Player Character:"));
            UStoryComponent* StoryComponent = PlayerCharacter->FindComponentByClass<UStoryComponent>();
            if (StoryComponent) {
                StoryComponent->UpdateDataTable(questID, true);
                UE_LOG(LogTemp, Warning, TEXT("Activating Quest: "), questID);
            }
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Deactivating Quest: %d"), questID);
    }
}

void UDialogueSystem::HandleDialogueQuestCompleted(bool completeQuest, int32 questID)
{
    if (completeQuest)
    {
        UE_LOG(LogTemp, Warning, TEXT("Completing Quest: %d"), questID);
        if (!PlayerCharacter) {
            PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
        }
        if (PlayerCharacter)
        {
            UE_LOG(LogTemp, Warning, TEXT("Found Player Character:"));
            UStoryComponent* StoryComponent = PlayerCharacter->FindComponentByClass<UStoryComponent>();
            if (StoryComponent) {
                StoryComponent->UpdateDataTable(questID, false);
                StoryComponent->UpdateDataTableCompleteQuest(questID, true);
                UE_LOG(LogTemp, Warning, TEXT("Activating Quest: "), questID);
            }
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Deactivating Quest: %d"), questID);
    }
}

void UDialogueSystem::EnablePlayerMovement()
{
    if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
    {
        // Przywrócenie normalnego trybu wejœcia
        FInputModeGameOnly InputMode;
        PlayerController->SetInputMode(InputMode);

        // Ukryj kursor
        PlayerController->bShowMouseCursor = false;

        // Odblokuj ruch postaci
        if (APawn* ControlledPawn = PlayerController->GetPawn())
        {
            ControlledPawn->EnableInput(PlayerController);
        }
    }
}

