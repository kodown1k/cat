// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectionBase.h"


USelectionBase::USelectionBase()
{
	currentSelection = 0;
	SetIsFocusable(true);
	SetVisibilityInternal(ESlateVisibility::Visible);
}

void USelectionBase::NativeConstruct()
{
	if (Options.Num() == 0) {
		UE_LOG(LogTemp, Warning, TEXT("USelectionBase: No options where provided"));
		return;
	}

	UpdateCurrentSelection();

	FCustomWidgetNavigationDelegate NavigationDelegate;
	NavigationDelegate.BindDynamic(this, &USelectionBase::OnNavigation);
	SetNavigationRuleCustom(EUINavigation::Left, NavigationDelegate);
	SetNavigationRuleCustom(EUINavigation::Right, NavigationDelegate);

}

void USelectionBase::Clear()
{
	Options.Reset(); //wyczysc tarray

}

void USelectionBase::AddOption(const FSelectOption& InOption)
{
	Options.Add(InOption);
	UpdateCurrentSelection();

}

void USelectionBase::SetCurrentSelection(int InIndex)
{
	check(InIndex >= 0 && InIndex < Options.Num());
	currentSelection = InIndex;
	UpdateCurrentSelection();

}



void USelectionBase::SelectPrevious()
{
	OnNavigation(EUINavigation::Left);
}

void USelectionBase::SelectNext()
{
	OnNavigation(EUINavigation::Right);
}

UWidget* USelectionBase::OnNavigation(EUINavigation InNavigation)
{
	check(InNavigation == EUINavigation::Left || InNavigation == EUINavigation::Right);

	const auto direction = InNavigation == EUINavigation::Left ? -1 : 1;

	currentSelection += direction;

	if (currentSelection < 0)
	{
		currentSelection = Options.Num() - 1;
	}
	else if (currentSelection >= Options.Num())
	{
		currentSelection = 0;
	}

	UpdateCurrentSelection();

	OnSelectionChange.ExecuteIfBound(currentSelection); //broadcoast to parent widget

	return this;
}

void USelectionBase::UpdateCurrentSelection()
{
	Label->SetText(Options[currentSelection].Label);
}






