#include "DialogueWidget.h"
#include "Kismet/GameplayStatics.h"
#include "ButtonDialogueWidget.h"

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
    UE_LOG(LogTemp, Warning, TEXT("ccurrentindex %d"), StartDialogueIndex);
    DialogueOption = inDialogueOption;
    // Sprawdzamy, czy mamy dane w tablicy
    if (DialogueOption.Num() == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("DialogueOption array is empty!"));
        return;
    }

    FDialogStruct* CurrentIndexOption = DialogueOption[StartDialogueIndex];

    // Sprawdzamy, czy CurrentIndexOption jest wa�ny
    if (!CurrentIndexOption)
    {
        UE_LOG(LogTemp, Error, TEXT("CurrentIndexOption is null!"));
        return;
    }

    // Je�li NPC m�wi, wy�wietlamy jego tekst
    if (CurrentIndexOption->bIsNPC && CurrentIndexOption->bShow)  // Je�li NPC m�wi i tekst ma by� wy�wietlony
    {
        if (NPCTextBlock)
        {
            UE_LOG(LogTemp, Warning, TEXT("Znalaz�em tekst! NPCTextBlock: %p"), NPCTextBlock);
            NPCTextBlock->SetText(CurrentIndexOption->Text);
        }

        if (CurrentIndexOption->Text.IsEmpty())
        {
            UE_LOG(LogTemp, Warning, TEXT("NPC Text is empty!"));
            return;
        }
    }

    // Sprawdzamy, czy s� opcje do wy�wietlenia
    UE_LOG(LogTemp, Warning, TEXT("Option counter %d"), CurrentIndexOption->Options);
    if (CurrentIndexOption->Options > 0) // Tylko gdy opcje maj� by� widoczne
    {
        // Zabezpieczenie przed przekroczeniem liczby opcji
        int32 OptionCount = CurrentIndexOption->Options;
        SetOptionVisibility(OptionCount);
        
        UE_LOG(LogTemp, Warning, TEXT("Option counter %d"), OptionCount);

        // Zabezpieczenie przed pr�b� ustawienia tekstu na wi�cej ni� 6 przyciskach
        for (int32 i = 0; i < OptionCount; i++)
        {
            

            FText OptionText = CurrentIndexOption->Text; // U�ywamy tekstu z bie��cej opcji

            // Zabezpieczenie przed dost�pem do nieistniej�cego przycisku
            switch (i)
            {
            case 0:
                if (OptionButton1 && i==0)
                {
                    OptionButtonText1->SetText(DialogueOption[StartDialogueIndex+1]->Text);
                    
                    OptionButton1->OnClicked.RemoveAll(this);
                    OptionButton1->OnClicked.AddDynamic(this, &UDialogueWidget::OnDialogueOptionClicked1);
                    ClickedOption1 = DialogueOption[StartDialogueIndex + 1]->NextID;
                }



                break;
            case 1:
                if (OptionButton2 && i == 1)
                {
                    OptionButtonText2->SetText(DialogueOption[StartDialogueIndex + 2]->Text);
                    ClickedOption2 = DialogueOption[StartDialogueIndex + 2]->NextID;
                    OptionButton2->OnClicked.RemoveAll(this);
                    OptionButton2->OnClicked.AddDynamic(this, &UDialogueWidget::OnDialogueOptionClicked2);
                    
                    
                }
                break;
            case 2:
                if (OptionButton3 && i == 2)
                {
                    OptionButtonText3->SetText(DialogueOption[StartDialogueIndex + 3]->Text);

                    OptionButton3->OnClicked.RemoveAll(this);
                    OptionButton3->OnClicked.AddDynamic(this, &UDialogueWidget::OnDialogueOptionClicked3);
                    ClickedOption3 = DialogueOption[StartDialogueIndex + 3]->NextID;
                    
                }
                break;
            case 3:
                if (OptionButton4 && i == 3)
                {
                    OptionButtonText4->SetText(DialogueOption[StartDialogueIndex + 4]->Text);
                    OptionButton4->OnClicked.RemoveAll(this);
                    OptionButton4->OnClicked.AddDynamic(this, &UDialogueWidget::OnDialogueOptionClicked4);
                    ClickedOption4 = DialogueOption[StartDialogueIndex + 4]->NextID;
                }
                break;
            case 4:
                if (OptionButton5 && i == 4)
                {
                    OptionButtonText5->SetText(DialogueOption[StartDialogueIndex + 5]->Text);
                    OptionButton5->OnClicked.RemoveAll(this);
                    OptionButton5->OnClicked.AddDynamic(this, &UDialogueWidget::OnDialogueOptionClicked5);
                    ClickedOption5 = DialogueOption[StartDialogueIndex + 5]->NextID;
                }
                break;
            case 5:
                if (OptionButton6 && i == 5)
                {
                    OptionButtonText6->SetText(DialogueOption[StartDialogueIndex + 6]->Text);
                    OptionButton6->OnClicked.RemoveAll(this);
                    OptionButton6->OnClicked.AddDynamic(this, &UDialogueWidget::OnDialogueOptionClicked6);
                    ClickedOption6 = DialogueOption[StartDialogueIndex + 6]->NextID;
                }
                break;
            }

            // Zwi�kszamy wska�nik po przypisaniu tekstu do przycisku
            
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No visible dialogue options."));
    }
}


void UDialogueWidget::SetOptionVisibility(int32 OptionCount)
{
    // Ukryj opcje, kt�re nie s� potrzebne
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
            PlayerController->SetInputMode(FInputModeGameOnly()); // Przywr�cenie trybu gry
            PlayerController->bShowMouseCursor = false; // Ukrycie kursora myszy
        }
        CloseDialogue();
        return; // Wyj�cie z funkcj
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
    if (ClickedOption1 == -1) {

        SetVisibility(ESlateVisibility::Hidden); // Ustawienie widgetu jako niewidocznego, opcjonalne

        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if (PlayerController)
        {
            PlayerController->SetInputMode(FInputModeGameOnly()); // Przywr�cenie trybu gry
            PlayerController->bShowMouseCursor = false; // Ukrycie kursora myszy
        }
        CloseDialogue();
        return; // Wyj�cie z funkcj
    }

    if (DialogueOption.IsValidIndex(ClickedOption1))
    {

        // Zaktualizowanie widgetu z nowymi opcjami
        PopulateDialogueOptions(DialogueOption, ClickedOption1);
    }
}

void UDialogueWidget::OnDialogueOptionClicked2()
{

    UE_LOG(LogTemp, Warning, TEXT("Clicked option index %d."), ClickedOption2);
    if (ClickedOption2 == -1) {

        SetVisibility(ESlateVisibility::Hidden); // Ustawienie widgetu jako niewidocznego, opcjonalne

        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if (PlayerController)
        {
            PlayerController->SetInputMode(FInputModeGameOnly()); // Przywr�cenie trybu gry
            PlayerController->bShowMouseCursor = false; // Ukrycie kursora myszy
        }
        CloseDialogue();
        return; // Wyj�cie z funkcj
    }

    if (DialogueOption.IsValidIndex(ClickedOption2))
    {

        // Zaktualizowanie widgetu z nowymi opcjami
        PopulateDialogueOptions(DialogueOption, ClickedOption2);
    }
}

void UDialogueWidget::OnDialogueOptionClicked3()
{

    UE_LOG(LogTemp, Warning, TEXT("Clicked option index %d."), ClickedOption3);
    if (ClickedOption3 == -1) {

        SetVisibility(ESlateVisibility::Hidden); // Ustawienie widgetu jako niewidocznego, opcjonalne

        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if (PlayerController)
        {
            PlayerController->SetInputMode(FInputModeGameOnly()); // Przywr�cenie trybu gry
            PlayerController->bShowMouseCursor = false; // Ukrycie kursora myszy
        }
        CloseDialogue();
        return; // Wyj�cie z funkcj
    }

    if (DialogueOption.IsValidIndex(ClickedOption3))
    {

        // Zaktualizowanie widgetu z nowymi opcjami
        PopulateDialogueOptions(DialogueOption, ClickedOption3);
    }
}

void UDialogueWidget::OnDialogueOptionClicked4()
{

    UE_LOG(LogTemp, Warning, TEXT("Clicked option index %d."), ClickedOption4);
    if (ClickedOption4 == -1) {

        SetVisibility(ESlateVisibility::Hidden); // Ustawienie widgetu jako niewidocznego, opcjonalne

        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if (PlayerController)
        {
            PlayerController->SetInputMode(FInputModeGameOnly()); // Przywr�cenie trybu gry
            PlayerController->bShowMouseCursor = false; // Ukrycie kursora myszy
        }
        CloseDialogue();
        return; // Wyj�cie z funkcj
    }

    if (DialogueOption.IsValidIndex(ClickedOption4))
    {

        // Zaktualizowanie widgetu z nowymi opcjami
        PopulateDialogueOptions(DialogueOption, ClickedOption4);
    }
}

void UDialogueWidget::OnDialogueOptionClicked5()
{

    UE_LOG(LogTemp, Warning, TEXT("Clicked option index %d."), ClickedOption5);
    if (ClickedOption5 == -1) {

        SetVisibility(ESlateVisibility::Hidden); // Ustawienie widgetu jako niewidocznego, opcjonalne

        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if (PlayerController)
        {
            PlayerController->SetInputMode(FInputModeGameOnly()); // Przywr�cenie trybu gry
            PlayerController->bShowMouseCursor = false; // Ukrycie kursora myszy
        }
        CloseDialogue();
        return; // Wyj�cie z funkcj
    }

    if (DialogueOption.IsValidIndex(ClickedOption5))
    {

        // Zaktualizowanie widgetu z nowymi opcjami
        PopulateDialogueOptions(DialogueOption, ClickedOption5);
    }
}

void UDialogueWidget::OnDialogueOptionClicked6()
{

    UE_LOG(LogTemp, Warning, TEXT("Clicked option index %d."), ClickedOption6);
    if (ClickedOption6 == -1) {

        SetVisibility(ESlateVisibility::Hidden); // Ustawienie widgetu jako niewidocznego, opcjonalne

        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if (PlayerController)
        {
            PlayerController->SetInputMode(FInputModeGameOnly()); // Przywr�cenie trybu gry
            PlayerController->bShowMouseCursor = false; // Ukrycie kursora myszy
        }
        CloseDialogue();
        return; // Wyj�cie z funkcj
    }

    if (DialogueOption.IsValidIndex(ClickedOption6))
    {

        // Zaktualizowanie widgetu z nowymi opcjami
        PopulateDialogueOptions(DialogueOption, ClickedOption6);
    }
}