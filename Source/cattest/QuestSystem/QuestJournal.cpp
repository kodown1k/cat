// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestJournal.h"

void UQuestJournal::NativeConstruct()
{
    Super::NativeConstruct();

    // Pobranie referencji do QuestManagera
     

    // Jeœli mamy QuestManagera, aktualizujemy dziennik
    
}

void UQuestJournal::PopulateQuestList(TArray<FQuestStruct1> ActiveQuests)
{
    // Pobieramy istniej¹ce wpisy
    TArray<UWidget*> ExistingChildren = QuestList->GetAllChildren();

    // Mapa do œledzenia istniej¹cych questów
    TMap<FString, UW_QuestEntry*> QuestMap;

    // Wype³niamy mapê istniej¹cych wpisów
    for (UWidget* Child : ExistingChildren)
    {
        UW_QuestEntry* QuestEntry = Cast<UW_QuestEntry>(Child);
        if (QuestEntry)
        {
            QuestMap.Add(QuestEntry->QuestName->GetText().ToString(), QuestEntry);
        }
    }

    // Przetwarzamy nowe questy
    for (const FQuestStruct1& Quest : ActiveQuests)
    {
        if (QuestMap.Contains(Quest.QuestName))
        {
            // ? Jeœli quest ju¿ istnieje, aktualizujemy go
            UW_QuestEntry* ExistingEntry = QuestMap[Quest.QuestName];
            ExistingEntry->CurrentProgress = Quest.CurrentProgress;
            ExistingEntry->RequiredAmount = Quest.RequiredAmount;

            // Aktualizujemy teksty
            ExistingEntry->QuestName->SetText(FText::FromString(Quest.QuestName));
            ExistingEntry->DescriptionText->SetText(FText::FromString(Quest.Description));

            UE_LOG(LogTemp, Warning, TEXT("Zaktualizowano quest: %s"), *Quest.QuestName);
        }
        else
        {
            // ? Jeœli quest nie istnieje, tworzymy nowy widget
            UW_QuestEntry* NewEntry = CreateWidget<UW_QuestEntry>(GetWorld(), QuestEntryWidgetClass);

            if (NewEntry)
            {
                NewEntry->QuestName->SetText(FText::FromString(Quest.QuestName));
                NewEntry->DescriptionText->SetText(FText::FromString(Quest.Description));
                NewEntry->RequiredAmount = Quest.RequiredAmount;
                NewEntry->CurrentProgress = Quest.CurrentProgress;

                QuestList->AddChild(NewEntry);

                UE_LOG(LogTemp, Warning, TEXT("Dodano nowy quest: %s"), *Quest.QuestName);
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("B³¹d przy tworzeniu widgetu dla questa: %s"), *Quest.QuestName);
            }
        }
    }
}


void UQuestJournal::DebugQuestListContents()
{
    if (!QuestList)
    {
        UE_LOG(LogTemp, Error, TEXT("QuestList jest nullptr!"));
        return;
    }

    int32 ChildCount = QuestList->GetChildrenCount();
    UE_LOG(LogTemp, Warning, TEXT("Liczba dzieci w QuestList: %d"), ChildCount);

    for (int32 i = 0; i < ChildCount; i++)
    {
        UWidget* ChildWidget = QuestList->GetChildAt(i);
        if (ChildWidget)
        {
            UE_LOG(LogTemp, Warning, TEXT("Element %d: %s"), i, *ChildWidget->GetName());

            // Jeœli to QuestEntry, wypisz jego dane
            UW_QuestEntry* QuestEntry = Cast<UW_QuestEntry>(ChildWidget);
            if (QuestEntry)
            {
                UE_LOG(LogTemp, Warning, TEXT("QuestEntry - Nazwa: %s"),
                    *QuestEntry->QuestName->GetText().ToString()
                    );
            }
        }
    }
}
