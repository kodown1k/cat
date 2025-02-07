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
    // Logika po klikni�ciu przycisku
    UE_LOG(LogTemp, Log, TEXT("Button clicked, Level to go: %d"), LevelToGo);
    // Mo�esz wywo�a� jak�� metod� zwi�zan� z przej�ciem do nast�pnego poziomu
}

void UButtonDialogueWidget::NativeConstruct()
{
    Super::NativeConstruct();

    // Rejestracja funkcji obs�ugi klikni�cia przycisku
    if (Btn)
    {
        Btn->OnClicked.AddDynamic(this, &UButtonDialogueWidget::OnBtnClick);
    }
}
