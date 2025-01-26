#include "DialogueWidget.h"
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
            

            FText OptionText = CurrentIndexOption->Text; // U¿ywamy tekstu z bie¿¹cej opcji

            // Zabezpieczenie przed dostêpem do nieistniej¹cego przycisku
            switch (i)
            {
            case 0:
                if (OptionButton1 && i==0)
                {
                    OptionButtonText1->SetText(DialogueOption[StartDialogueIndex+1]->Text);
                    
                    OptionButton1->OnClicked.RemoveAll(this);
                    OptionButton1->OnClicked.AddDynamic(this, &UDialogueWidget::OnDialogueOptionClicked);
                    ClickedOption2 = DialogueOption[StartDialogueIndex + 1]->NextID;
                }



                break;
            case 1:
                if (OptionButton2 && i == 1)
                {
                    OptionButtonText2->SetText(DialogueOption[StartDialogueIndex + 2]->Text);
                    
                }
                break;
            case 2:
                if (OptionButton3 && i == 2)
                {
                    OptionButtonText3->SetText(DialogueOption[StartDialogueIndex + 3]->Text);
                    
                }
                break;
            case 3:
                if (OptionButton4 && i == 3)
                {
                    OptionButtonText4->SetText(DialogueOption[StartDialogueIndex + 4]->Text);
                    
                }
                break;
            case 4:
                if (OptionButton5 && i == 4)
                {
                    OptionButtonText5->SetText(DialogueOption[StartDialogueIndex + 5]->Text);
                    
                }
                break;
            case 5:
                if (OptionButton6 && i == 5)
                {
                    OptionButtonText6->SetText(DialogueOption[StartDialogueIndex + 6]->Text);
                    
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


void UDialogueWidget::CreateDialogueOptionButton(const FText& OptionText, int32 NextID)
{
    
}

void UDialogueWidget::OnDialogueOptionClicked()
{
    if (DialogueOption.IsValidIndex(ClickedOption2))
    {

        // Zaktualizowanie widgetu z nowymi opcjami
        PopulateDialogueOptions(DialogueOption, ClickedOption2);
    }
}
