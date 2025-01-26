#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Kismet/KismetSystemLibrary.h"

#include "CommonActivatableWidget.h"
#include "CommonUserWidget.h"
#include "CommonTextBlock.h"

#include "CommonButtonBase.h"

#include "Components/Widget.h"
#include "Components/VerticalBox.h"
#include "DialogStruct.h"
#include "ButtonDialogueWidget.h"

#include "DialogueWidget.generated.h"

/**
 *
 */
UCLASS()
class CATTEST_API UDialogueWidget : public UCommonActivatableWidget
{
    GENERATED_BODY()

public:
    virtual void NativeConstruct() override;

    // Funkcja do ustawiania opcji dialogowych
    void PopulateDialogueOptions(TArray<FDialogStruct*>, int32 StartDialogueIndex);
    void SetNPCText(const FText& Text);

    void SetOptionVisibility(int32 OptionCount);

protected:
    // Referencja do VerticalBox, w kt�rym b�d� przechowywane przyciski
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UVerticalBox> DialogueOptionsBox;  // Tylko jedna deklaracja

    // Klasa przycisku, z kt�rej generowane b�d� opcje
    UPROPERTY(EditAnywhere, Category = "UI")
    TSubclassOf<UButtonDialogueWidget> ButtonWidgetRef;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* NPCTextBlock;

    // Przyciski dla odpowiedzi
    UPROPERTY(meta = (BindWidget))
    UButton* OptionButton1;

    UPROPERTY(meta = (BindWidget))
    UButton* OptionButton2;

    UPROPERTY(meta = (BindWidget))
    UButton* OptionButton3;

    UPROPERTY(meta = (BindWidget))
    UButton* OptionButton4;

    UPROPERTY(meta = (BindWidget))
    UButton* OptionButton5;

    UPROPERTY(meta = (BindWidget))
    UButton* OptionButton6;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* OptionButtonText1;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* OptionButtonText2;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* OptionButtonText3;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* OptionButtonText4;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* OptionButtonText5;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* OptionButtonText6;



   
    
private:
    // Funkcja obs�uguj�ca klikni�cie przycisku
    UFUNCTION()
    void CreateDialogueOptionButton(const FText& OptionText, int32 NextID);
    UFUNCTION()
    void OnDialogueOptionClicked();

    TArray<FDialogStruct*> DialogueOption;  // Tablica z opcjami dialogowymi
    int32 CurrentDialogueIndex;  // Indeks bie��cego dialogu
    int32 ClickedOption2;  // Indeks bie��cego dialogu
};