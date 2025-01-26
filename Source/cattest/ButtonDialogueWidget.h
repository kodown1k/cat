#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "ButtonDialogueWidget.generated.h"

/**
 * UButtonDialogueWidget - Widget reprezentuj�cy pojedynczy przycisk w dialogu.
 */
UCLASS()
class CATTEST_API UButtonDialogueWidget : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	// Referencja do przycisku
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* Btn;

	// Referencja do tekstu na przycisku
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* Text;

	// Numer poziomu, do kt�rego ma przej�� u�ytkownik po klikni�ciu
	int LevelToGo;

	// Funkcja do ustawiania danych dla tego przycisku
	void SetData(const FText& ButtonText, int32 Level);

	// Funkcja wywo�ywana przy klikni�ciu przycisku
	UFUNCTION()
	void OnBtnClick();

protected:
	// Zarejestrowanie funkcji dla przycisku w metodzie NativeConstruct
	virtual void NativeConstruct() override;
};