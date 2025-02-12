#include "DialogueWidget.h"
#include "Kismet/GameplayStatics.h"
#include "ButtonDialogueWidget.h"
#include "StoryComponent.h"

void UDialogueWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // Ustawienie pierwszego przycisku jako focus
    if (OptionButton1)
    {
        OptionButton1->SetKeyboardFocus();
    }
}

void UDialogueWidget::PopulateDialogueOptions(TArray<FDialogStruct*> inDialogueOption, int32 StartDialogueIndex)
{
    questIDToActivate = 0;

    UE_LOG(LogTemp, Warning, TEXT("ccurrentindex %d"), StartDialogueIndex);
    DialogueOption = inDialogueOption;
    // Sprawdzamy, czy mamy dane w tablicy
    if (DialogueOption.Num() == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("DialogueOption array is empty!"));
        return;
    }

    FDialogStruct* CurrentIndexOption = DialogueOption[StartDialogueIndex];

    // Sprawdzamy, czy CurrentIndexOption jest wa¿ny
    if (!CurrentIndexOption)
    {
        UE_LOG(LogTemp, Error, TEXT("CurrentIndexOption is null!"));
        return;
    }

    // Jeœli NPC mówi, wyœwietlamy jego tekst
    if (CurrentIndexOption->bIsNPC && CurrentIndexOption->bShow)  // Jeœli NPC mówi i tekst ma byæ wyœwietlony
    {
        if (NPCTextBlock)
        {
            UE_LOG(LogTemp, Warning, TEXT("Znalaz³em tekst! NPCTextBlock: %p"), NPCTextBlock);
            NPCTextBlock->SetText(CurrentIndexOption->Text);
        }

        if (CurrentIndexOption->Text.IsEmpty())
        {
            UE_LOG(LogTemp, Warning, TEXT("NPC Text is empty!"));
            return;
        }
    }

    // Sprawdzamy, czy s¹ opcje do wyœwietlenia
    UE_LOG(LogTemp, Warning, TEXT("Option counter %d"), CurrentIndexOption->Options);
    if (CurrentIndexOption->Options > 0) // Tylko gdy opcje maj¹ byæ widoczne
    {
        // Zabezpieczenie przed przekroczeniem liczby opcji
        int32 OptionCount = CurrentIndexOption->Options;
        SetOptionVisibility(OptionCount);
        
        UE_LOG(LogTemp, Warning, TEXT("Option counter %d"), OptionCount);

        // Zabezpieczenie przed prób¹ ustawienia tekstu na wiêcej ni¿ 6 przyciskach
        for (int32 i = 0; i < OptionCount; i++)
        {
            UE_LOG(LogTemp, Warning, TEXT("quest related %d : %s"),
                i + 1, DialogueOption[StartDialogueIndex + i+1]->isQuestRelated ? TEXT("True") : TEXT("False"));

            if (DialogueOption[StartDialogueIndex + i + 1]->isQuestRelated) {
                if (!PlayerCharacter) {
                    PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
                    UE_LOG(LogTemp, Warning, TEXT("not Found Player Character:"));
                }
                if (PlayerCharacter)
                {
                    UE_LOG(LogTemp, Warning, TEXT("Found Player Character:"));
                    UStoryComponent* StoryComponent = PlayerCharacter->FindComponentByClass<UStoryComponent>();
                    if (!StoryComponent->IsQuestActive(DialogueOption[StartDialogueIndex + i + 1]->questID)) {
                    
                        UE_LOG(LogTemp, Warning, TEXT("quest is not active skipping dialog option: "), DialogueOption[StartDialogueIndex + i + 1]->questID);
                        switch (i)
                        {
                        case 0: if (OptionButton1) OptionButton1->SetVisibility(ESlateVisibility::Collapsed); break;
                        case 1: if (OptionButton2) OptionButton2->SetVisibility(ESlateVisibility::Collapsed); break;
                        case 2: if (OptionButton3) OptionButton3->SetVisibility(ESlateVisibility::Collapsed); break;
                        case 3: if (OptionButton4) OptionButton4->SetVisibility(ESlateVisibility::Collapsed); break;
                        case 4: if (OptionButton5) OptionButton5->SetVisibility(ESlateVisibility::Collapsed); break;
                        case 5: if (OptionButton6) OptionButton6->SetVisibility(ESlateVisibility::Collapsed); break;
                        }
                        continue;
                    }
                }

            }

            FText OptionText = CurrentIndexOption->Text; // U¿ywamy tekstu z bie¿¹cej opcji

            // Zabezpieczenie przed dostêpem do nieistniej¹cego przycisku
            
            switch (i)
            {
            case 0:
                if (OptionButton1 && i==0)
                {
                    OptionButtonText1->SetText(DialogueOption[StartDialogueIndex+1]->Text);
                    
                    OptionButton1->OnClicked.RemoveAll(this);
                    OptionButton1->OnClicked.AddDynamic(this, &UDialogueWidget::OnDialogueOptionClicked1);
                    ClickedOption1 = DialogueOption[StartDialogueIndex + 1]->NextID;
                    if (DialogueOption[StartDialogueIndex + 1]->ActivateQuest) {
                        questIDToActivate = DialogueOption[StartDialogueIndex + 1]->ActivateQuestID;
                    }
                }



                break;
            case 1:
                if (OptionButton2 && i == 1)
                {
                    OptionButtonText2->SetText(DialogueOption[StartDialogueIndex + 2]->Text);
                    ClickedOption2 = DialogueOption[StartDialogueIndex + 2]->NextID;
                    OptionButton2->OnClicked.RemoveAll(this);
                    OptionButton2->OnClicked.AddDynamic(this, &UDialogueWidget::OnDialogueOptionClicked2);
                    if (DialogueOption[StartDialogueIndex + 2]->ActivateQuest) {
                        questIDToActivate = DialogueOption[StartDialogueIndex + 2]->ActivateQuestID;
                    }
                    
                }
                break;
            case 2:
                if (OptionButton3 && i == 2)
                {
                    OptionButtonText3->SetText(DialogueOption[StartDialogueIndex + 3]->Text);

                    OptionButton3->OnClicked.RemoveAll(this);
                    OptionButton3->OnClicked.AddDynamic(this, &UDialogueWidget::OnDialogueOptionClicked3);
                    ClickedOption3 = DialogueOption[StartDialogueIndex + 3]->NextID;
                    if (DialogueOption[StartDialogueIndex + 3]->ActivateQuest) {
                        questIDToActivate = DialogueOption[StartDialogueIndex + 3]->ActivateQuestID;
                    }
                }
                break;
            case 3:
                if (OptionButton4 && i == 3)
                {
                    OptionButtonText4->SetText(DialogueOption[StartDialogueIndex + 4]->Text);
                    OptionButton4->OnClicked.RemoveAll(this);
                    OptionButton4->OnClicked.AddDynamic(this, &UDialogueWidget::OnDialogueOptionClicked4);
                    ClickedOption4 = DialogueOption[StartDialogueIndex + 4]->NextID;
                    if (DialogueOption[StartDialogueIndex + 4]->ActivateQuest) {
                        questIDToActivate = DialogueOption[StartDialogueIndex + 4]->ActivateQuestID;
                    }
                }
                break;
            case 4:
                if (OptionButton5 && i == 4)
                {
                    OptionButtonText5->SetText(DialogueOption[StartDialogueIndex + 5]->Text);
                    OptionButton5->OnClicked.RemoveAll(this);
                    OptionButton5->OnClicked.AddDynamic(this, &UDialogueWidget::OnDialogueOptionClicked5);
                    ClickedOption5 = DialogueOption[StartDialogueIndex + 5]->NextID;
                    if (DialogueOption[StartDialogueIndex + 5]->ActivateQuest) {
                        questIDToActivate = DialogueOption[StartDialogueIndex + 5]->ActivateQuestID;
                    }
                }
                break;
            case 5:
                if (OptionButton6 && i == 5)
                {
                    OptionButtonText6->SetText(DialogueOption[StartDialogueIndex + 6]->Text);
                    OptionButton6->OnClicked.RemoveAll(this);
                    OptionButton6->OnClicked.AddDynamic(this, &UDialogueWidget::OnDialogueOptionClicked6);
                    ClickedOption6 = DialogueOption[StartDialogueIndex + 6]->NextID;
                    if (DialogueOption[StartDialogueIndex + 1]->ActivateQuest) {
                        questIDToActivate = DialogueOption[StartDialogueIndex + 6]->ActivateQuestID;
                    }
                }
                break;
            }

            // Zwiêkszamy wskaŸnik po przypisaniu tekstu do przycisku
            
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No visible dialogue options."));
    }
}


void UDialogueWidget::SetOptionVisibility(int32 OptionCount)
{
    // Ukryj opcje, które nie s¹ potrzebne
    OptionButton1->SetVisibility(OptionCount >= 1 ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    OptionButton2->SetVisibility(OptionCount >= 2 ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    OptionButton3->SetVisibility(OptionCount >= 3 ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    OptionButton4->SetVisibility(OptionCount >= 4 ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    OptionButton5->SetVisibility(OptionCount >= 5 ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    OptionButton6->SetVisibility(OptionCount >= 6 ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}


void UDialogueWidget::CloseDialogue()
{
    OnDialogueClosed.Broadcast();

    // Ukrywanie widgetu
    this->RemoveFromParent();

}

void UDialogueWidget::ActivateQuest(bool activate, int32 questID)
{
    OnDialogueQuest.Broadcast(activate, questID);

}

void UDialogueWidget::CreateDialogueOptionButton(const FText& OptionText, int32 NextID)
{
    
}

void UDialogueWidget::OnDialogueOptionClicked(int32 clickedOptionId)
{
    
    UE_LOG(LogTemp, Warning, TEXT("Clicked option index %d."), clickedOptionId);
    if (clickedOptionId == -1) {
        
        SetVisibility(ESlateVisibility::Hidden); // Ustawienie widgetu jako niewidocznego, opcjonalne
        
        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if (PlayerController)
        {
            PlayerController->SetInputMode(FInputModeGameOnly()); // Przywrócenie trybu gry
            PlayerController->bShowMouseCursor = false; // Ukrycie kursora myszy
        }
        CloseDialogue();
        return; // Wyjœcie z funkcj
    }

    if (DialogueOption.IsValidIndex(clickedOptionId))
    {
        
        // Zaktualizowanie widgetu z nowymi opcjami
        PopulateDialogueOptions(DialogueOption, clickedOptionId);
    }
}


void UDialogueWidget::OnDialogueOptionClicked1()
{

    UE_LOG(LogTemp, Warning, TEXT("Clicked option index %d."), ClickedOption1);
    if (questIDToActivate != 0) {
        ActivateQuest(true, questIDToActivate);
    }

    if (ClickedOption1 == -1) {

        SetVisibility(ESlateVisibility::Hidden); // Ustawienie widgetu jako niewidocznego, opcjonalne

        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if (PlayerController)
        {
            PlayerController->SetInputMode(FInputModeGameOnly()); // Przywrócenie trybu gry
            PlayerController->bShowMouseCursor = false; // Ukrycie kursora myszy
        }
        CloseDialogue();
        return; // Wyjœcie z funkcj
    }

    if (DialogueOption.IsValidIndex(ClickedOption1))
    {

        // Zaktualizowanie widgetu z nowymi opcjami
        PopulateDialogueOptions(DialogueOption, ClickedOption1);
    }
}

void UDialogueWidget::OnDialogueOptionClicked2()
{
    if (questIDToActivate != 0) {
        ActivateQuest(true, questIDToActivate);
    }
    UE_LOG(LogTemp, Warning, TEXT("Clicked option index %d."), ClickedOption2);
    if (ClickedOption2 == -1) {

        SetVisibility(ESlateVisibility::Hidden); // Ustawienie widgetu jako niewidocznego, opcjonalne

        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if (PlayerController)
        {
            PlayerController->SetInputMode(FInputModeGameOnly()); // Przywrócenie trybu gry
            PlayerController->bShowMouseCursor = false; // Ukrycie kursora myszy
        }
        CloseDialogue();
        return; // Wyjœcie z funkcj
    }

    if (DialogueOption.IsValidIndex(ClickedOption2))
    {

        // Zaktualizowanie widgetu z nowymi opcjami
        PopulateDialogueOptions(DialogueOption, ClickedOption2);
    }
}

void UDialogueWidget::OnDialogueOptionClicked3()
{

    if (questIDToActivate != 0) {
        OnDialogueQuest.Broadcast(true, questIDToActivate); // Activates quest with ID 101
    }
    UE_LOG(LogTemp, Warning, TEXT("Clicked option index %d."), ClickedOption3);
    if (ClickedOption3 == -1) {

        SetVisibility(ESlateVisibility::Hidden); // Ustawienie widgetu jako niewidocznego, opcjonalne

        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if (PlayerController)
        {
            PlayerController->SetInputMode(FInputModeGameOnly()); // Przywrócenie trybu gry
            PlayerController->bShowMouseCursor = false; // Ukrycie kursora myszy
        }
        CloseDialogue();
        return; // Wyjœcie z funkcj
    }

    if (DialogueOption.IsValidIndex(ClickedOption3))
    {

        // Zaktualizowanie widgetu z nowymi opcjami
        PopulateDialogueOptions(DialogueOption, ClickedOption3);
    }
}

void UDialogueWidget::OnDialogueOptionClicked4()
{
    if (questIDToActivate != 0) {
        ActivateQuest(true, questIDToActivate);
    }
    UE_LOG(LogTemp, Warning, TEXT("Clicked option index %d."), ClickedOption4);
    if (ClickedOption4 == -1) {

        SetVisibility(ESlateVisibility::Hidden); // Ustawienie widgetu jako niewidocznego, opcjonalne

        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if (PlayerController)
        {
            PlayerController->SetInputMode(FInputModeGameOnly()); // Przywrócenie trybu gry
            PlayerController->bShowMouseCursor = false; // Ukrycie kursora myszy
        }
        CloseDialogue();
        return; // Wyjœcie z funkcj
    }

    if (DialogueOption.IsValidIndex(ClickedOption4))
    {

        // Zaktualizowanie widgetu z nowymi opcjami
        PopulateDialogueOptions(DialogueOption, ClickedOption4);
    }
}

void UDialogueWidget::OnDialogueOptionClicked5()
{
    if (questIDToActivate != 0) {
        ActivateQuest(true, questIDToActivate);
    }
    UE_LOG(LogTemp, Warning, TEXT("Clicked option index %d."), ClickedOption5);
    if (ClickedOption5 == -1) {

        SetVisibility(ESlateVisibility::Hidden); // Ustawienie widgetu jako niewidocznego, opcjonalne

        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if (PlayerController)
        {
            PlayerController->SetInputMode(FInputModeGameOnly()); // Przywrócenie trybu gry
            PlayerController->bShowMouseCursor = false; // Ukrycie kursora myszy
        }
        CloseDialogue();
        return; // Wyjœcie z funkcj
    }

    if (DialogueOption.IsValidIndex(ClickedOption5))
    {

        // Zaktualizowanie widgetu z nowymi opcjami
        PopulateDialogueOptions(DialogueOption, ClickedOption5);
    }
}

void UDialogueWidget::OnDialogueOptionClicked6()
{
    if (questIDToActivate != 0) {
        ActivateQuest(true, questIDToActivate);
    }
    UE_LOG(LogTemp, Warning, TEXT("Clicked option index %d."), ClickedOption6);
    if (ClickedOption6 == -1) {

        SetVisibility(ESlateVisibility::Hidden); // Ustawienie widgetu jako niewidocznego, opcjonalne

        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if (PlayerController)
        {
            PlayerController->SetInputMode(FInputModeGameOnly()); // Przywrócenie trybu gry
            PlayerController->bShowMouseCursor = false; // Ukrycie kursora myszy
        }
        CloseDialogue();
        return; // Wyjœcie z funkcj
    }

    if (DialogueOption.IsValidIndex(ClickedOption6))
    {

        // Zaktualizowanie widgetu z nowymi opcjami
        PopulateDialogueOptions(DialogueOption, ClickedOption6);
    }
}