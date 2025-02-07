
#pragma once

#include "CommonTextBlock.h"
#include "CommonUserWidget.h"
#include "CoreMinimal.h"
#include "SelectOption.h"

#include "Logging/LogMacros.h"

#include "SelectionBase.generated.h"


UCLASS()
class CATTEST_API USelectionBase : public UCommonUserWidget
{
public:
	GENERATED_BODY()

	USelectionBase();
	virtual void NativeConstruct() override;

	void Clear();
	void AddOption(const FSelectOption& InOption);
	void SetCurrentSelection(int InIndex);

	UFUNCTION(BlueprintCallable)
	void SelectPrevious();
	UFUNCTION(BlueprintCallable)
	void SelectNext();

	DECLARE_DELEGATE_OneParam(FOnSelectionChange, int)
	FOnSelectionChange OnSelectionChange;

protected:
	UFUNCTION(BlueprintCallable)
	UWidget* OnNavigation(EUINavigation InNavigation); //custom navigation rules

	void UpdateCurrentSelection(); //update

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TArray<FSelectOption> Options; 

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	TObjectPtr<UCommonTextBlock> Label;

	int currentSelection;

};
