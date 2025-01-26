#include "DialogueSystem.h"
#include "DialogueWidget.h"
#include "ButtonDialogueWidget.h"

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
    if (UWorld* World = GetWorld())  // Sprawdzamy, czy œwiat jest dostêpny
    {
        if (DialogueWidgetClass)  // Sprawdzamy, czy klasa widgetu zosta³a przypisana
        {
            // Jeœli widget ju¿ istnieje i jest widoczny, nie tworzymy nowego
            if (DialogueWidget && DialogueWidget->IsInViewport())
            {
                // Mo¿esz dodaæ dodatkow¹ logikê, aby zaktualizowaæ widget lub po prostu wyjœæ
                UE_LOG(LogTemp, Warning, TEXT("Widget is already visible."));
                return;
            }

            // Tworzymy widget tylko wtedy, gdy nie jest jeszcze widoczny
            DialogueWidget = CreateWidget<UDialogueWidget>(World, DialogueWidgetClass);

            if (DialogueWidget)  // Jeœli widget zosta³ poprawnie utworzony
            {
                // Przekazywanie dialogu do widgetu
                if (DialogOptions.IsValidIndex(CurrentDialogueIndex))
                {
                    DialogueWidget->PopulateDialogueOptions(DialogOptions,CurrentDialogueIndex);
                    UE_LOG(LogTemp, Log, TEXT("Widget populated with dialogue options."));
                }
                else
                {
                    UE_LOG(LogTemp, Warning, TEXT("Invalid dialogue index: %d. Cannot populate dialogue options."), CurrentDialogueIndex);
                }

                // Ustawienie widocznoœci widgetu na ekranie
                DialogueWidget->SetVisibility(ESlateVisibility::Visible);
                DialogueWidget->AddToViewport();
                DisablePlayerMovement();
                UE_LOG(LogTemp, Log, TEXT("Widget added to viewport."));
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Nie uda³o siê stworzyæ widgetu!"));
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Brak przypisanej klasy widgetu!"));
        }
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
        InputMode.SetWidgetToFocus(DialogueWidget->TakeWidget());
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