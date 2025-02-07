// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonDialogueWidget.h"

void UButtonDialogueWidget::SetData(const FText& ButtonText, int32 Level)
{
    // Ustawianie tekstu na przycisku
    if (Text)
    {
        Text->SetText(ButtonText);
    }

    // Przechowywanie numeru poziomu
    LevelToGo = Level;
}

void UButtonDialogueWidget::OnBtnClick()
{
    // Logika po klikniêciu przycisku
    UE_LOG(LogTemp, Log, TEXT("Button clicked, Level to go: %d"), LevelToGo);
    // Mo¿esz wywo³aæ jak¹œ metodê zwi¹zan¹ z przejœciem do nastêpnego poziomu
}

void UButtonDialogueWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // Rejestracja funkcji obs³ugi klikniêcia przycisku
    if (Btn)
    {
        Btn->OnClicked.AddDynamic(this, &UButtonDialogueWidget::OnBtnClick);
    }
}
