// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestJournal.h"

void UQuestJournal::NativeConstruct()
{
    Super::NativeConstruct();

    // Pobranie referencji do QuestManagera
     

    // Je�li mamy QuestManagera, aktualizujemy dziennik
    
}

void UQuestJournal::PopulateQuestList(TArray<FQuestStruct1> ActiveQuests)
{
    // Pobieramy istniej�ce wpisy
    TArray<UWidget*> ExistingChildren = QuestList->GetAllChildren();
    TMap<FString, UW_QuestEntry*> QuestMap;

    // Wype�niamy map� istniej�cych wpis�w
    for (UWidget* Child : ExistingChildren)
    {
        UW_QuestEntry* QuestEntry = Cast<UW_QuestEntry>(Child);
        if (QuestEntry)
        {
            QuestMap.Add(QuestEntry->QuestName->GetText().ToString(), QuestEntry);
        }
    }

    // Lista aktywnych quest�w do �atwego sprawdzania
    TSet<FString> ActiveQuestNames;
    for (const FQuestStruct1& Quest : ActiveQuests)
    {
        if (Quest.bIsActive)
        {
            ActiveQuestNames.Add(Quest.QuestName);
        }
    }

    // Usuwamy questy, kt�re by�y aktywne, ale teraz ich nie ma w ActiveQuests lub sta�y si� nieaktywne
    for (auto& Entry : QuestMap)
    {
        if (!ActiveQuestNames.Contains(Entry.Key))
        {
            Entry.Value->RemoveFromParent(); // Usuwamy z UI
            UE_LOG(LogTemp, Warning, TEXT("Usuni�to quest: %s"), *Entry.Key);
        }
    }

    // Przetwarzamy nowe questy
    for (const FQuestStruct1& Quest : ActiveQuests)
    {
        if (!Quest.bIsActive)
        {
            UE_LOG(LogTemp, Warning, TEXT("Pomini�to nieaktywny quest: %s"), *Quest.QuestName);
            continue;
        }

        if (QuestMap.Contains(Quest.QuestName))
        {
            // Aktualizujemy istniej�cy quest
            UW_QuestEntry* ExistingEntry = QuestMap[Quest.QuestName];
            ExistingEntry->CurrentProgress = Quest.CurrentProgress;
            ExistingEntry->RequiredAmount = Quest.RequiredAmount;

            ExistingEntry->QuestName->SetText(FText::FromString(Quest.QuestName));
            ExistingEntry->DescriptionText->SetText(FText::FromString(Quest.Description));

            UE_LOG(LogTemp, Warning, TEXT("Zaktualizowano quest: %s"), *Quest.QuestName);
        }
        else
        {
            // Tworzymy nowy wpis
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
                UE_LOG(LogTemp, Warning, TEXT("B��d przy tworzeniu widgetu dla questa: %s"), *Quest.QuestName);
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

            // Je�li to QuestEntry, wypisz jego dane
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
