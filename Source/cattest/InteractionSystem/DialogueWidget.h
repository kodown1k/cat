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


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueClosed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDialogueQuest, bool, activateQuest, int32, questID);
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

    
    FOnDialogueClosed OnDialogueClosed; // Delegat, wywo³ywany przy zamkniêciu dialogu
    FOnDialogueQuest OnDialogueQuest; // Delegat, wywo³ywany przy zamkniêciu dialogu
    UFUNCTION()
    void CloseDialogue(); // Funkcja zamykaj¹ca dialog
    UFUNCTION()
    void ActivateQuest(bool activate, int32 questID);

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly) //referencja do gracza
        ACharacter* PlayerCharacter;
    
protected:
    // Referencja do VerticalBox, w którym bêd¹ przechowywane przyciski
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UVerticalBox> DialogueOptionsBox;  // Tylko jedna deklaracja

    // Klasa przycisku, z której generowane bêd¹ opcje
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
    // Funkcja obs³uguj¹ca klikniêcie przycisku
    UFUNCTION()
    void CreateDialogueOptionButton(const FText& OptionText, int32 NextID);
    UFUNCTION()
    void OnDialogueOptionClicked(int32 clickedOptionId);
    UFUNCTION()
    void OnDialogueOptionClicked1();
    UFUNCTION()
    void OnDialogueOptionClicked2();
    UFUNCTION()
    void OnDialogueOptionClicked3();
    UFUNCTION()
    void OnDialogueOptionClicked4();
    UFUNCTION()
    void OnDialogueOptionClicked5();
    UFUNCTION()
    void OnDialogueOptionClicked6();

    TArray<FDialogStruct*> DialogueOption;  // Tablica z opcjami dialogowymi
    int32 questIDToActivate;
    int32 CurrentDialogueIndex;  // Indeks bie¿¹cego dialogu
    int32 ClickedOption6;  // Indeks bie¿¹cego dialogu
    int32 ClickedOption1;  // Indeks bie¿¹cego dialogu
    int32 ClickedOption2;  // Indeks bie¿¹cego dialogu
    int32 ClickedOption3;  // Indeks bie¿¹cego dialogu
    int32 ClickedOption4;  // Indeks bie¿¹cego dialogu
    int32 ClickedOption5;  // Indeks bie¿¹cego dialogu
    int32 ClickedOption;
    
};