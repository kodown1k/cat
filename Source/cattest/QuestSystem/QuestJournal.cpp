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
    QuestList->ClearChildren();
    // Dla ka¿dego aktywnego questa tworzymy nowy widget i dodajemy do listy
    for (const FQuestStruct1& Quest : ActiveQuests)
    {
        
        // Tworzymy widget dla ka¿dego questa
        // Tworzymy widget dla ka¿dego questa
        UW_QuestEntry* NewEntry = CreateWidget<UW_QuestEntry>(GetWorld(), QuestEntryWidgetClass);


        // Logowanie, czy widget zosta³ utworzony
        if (NewEntry)
        {
            UE_LOG(LogTemp, Warning, TEXT("Nowy widget quest entry stworzony: %s"), *Quest.QuestName);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("B³¹d przy tworzeniu widgetu dla questa: %s"), *Quest.QuestName);
        }


        // Ustawiamy dane w odpowiednich widgetach
        if (NewEntry)
        {
            // Przypisujemy teksty do odpowiednich widgetów
            if (NewEntry->QuestName)
            {
                NewEntry->QuestName->SetText(FText::FromString(Quest.QuestName));
            }

            if (NewEntry->DescriptionText)
            {
                NewEntry->DescriptionText->SetText(FText::FromString(Quest.Description));
            }

            // Ustawiamy inne dane (jeœli potrzeba)
            NewEntry->RequiredAmount = Quest.RequiredAmount;
            NewEntry->CurrentProgress = Quest.CurrentProgress;

            // Dodajemy widget do listy (jeœli u¿ywasz np. VerticalBox)
            QuestList->AddChild(NewEntry);
            UE_LOG(LogTemp, Warning, TEXT("Dodano quest do listy: %s"), *Quest.QuestName)
                DebugQuestListContents();
               
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
