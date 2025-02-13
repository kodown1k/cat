#include "QuestManager.h"
#include "Kismet/GameplayStatics.h"

// Konstruktor
AQuestManager::AQuestManager()
{
    PrimaryActorTick.bCanEverTick = false; // Nie potrzebujemy ticka
}

// Uruchomienie gry
void AQuestManager::BeginPlay()
{
    Super::BeginPlay(); // Upewnij siê, ¿e wywo³ujesz funkcjê bazow¹ na pocz¹tku

    // Je¿eli QuestDataTable jest przypisany, za³aduj questy
    if (QuestDataTable)
    {
        UE_LOG(LogTemp, Error, TEXT("QuestDataTable is  assigned!"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("QuestDataTable is not assigned!"));
    }
}

// Funkcja dodaj¹ca questa do listy
void AQuestManager::GiveQuest(const FQuestStruct1& NewQuest)
{
    QuestList.Add(NewQuest); // Dodajemy obiekt, nie wskaŸnik
    UE_LOG(LogTemp, Warning, TEXT("Dodano nowy quest: %s"), *NewQuest.QuestName);
}

// Funkcja aktualizuj¹ca postêp questa
void AQuestManager::UpdateQuestProgress(const FString& QuestName, int32 Amount)
{
    for (FQuestStruct1& Quest : QuestList) // Iteracja po referencjach
    {
        if (Quest.QuestName == QuestName)
        {
            Quest.CurrentProgress += Amount;
            UE_LOG(LogTemp, Warning, TEXT("Quest %s: Progress = %d"), *Quest.QuestName, Quest.CurrentProgress);

            // Sprawdzenie, czy quest zosta³ ukoñczony
            if (Quest.CurrentProgress >= Quest.RequiredAmount)
            {
                UE_LOG(LogTemp, Warning, TEXT("Quest %s ukoñczony!"), *Quest.QuestName);
                // Tutaj mo¿na dodaæ np. usuniêcie questa lub nagrody
            }
            return;
        }
    }
    UE_LOG(LogTemp, Warning, TEXT("Quest %s nie znaleziony!"), *QuestName);
}

// Pobieranie aktywnych questów
TArray<FQuestStruct1> AQuestManager::GetActiveQuests()
{
    
    TArray<FQuestStruct1> ActiveQuests; // Tablica na aktywne questy

    if (QuestDataTable)
    {
        TArray<FName> RowNames = QuestDataTable->GetRowNames();

        for (const FName& RowName : RowNames)
        {
            // Znajdujemy wiersz w DataTable
            FQuestStruct1* Row = QuestDataTable->FindRow<FQuestStruct1>(RowName, TEXT(""));

            if (Row && Row->bIsActive) // Sprawdzamy czy wiersz istnieje i czy quest jest aktywny
            {
                ActiveQuests.Add(*Row); // Dodajemy kopiê questów tylko, jeœli s¹ aktywne
            }
        }

        // Aktualizujemy listê aktywnych questów
        QuestList = ActiveQuests;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("QuestDataTable is not assigned!"));
    }
    PrintAllQuests();
    return ActiveQuests; // Zwracamy tylko aktywne questy
}

void AQuestManager::SetQuestDataTable(UDataTable* NewDataTable)
{
    if (NewDataTable)
    {
        QuestDataTable = NewDataTable;
        UE_LOG(LogTemp, Warning, TEXT("QuestDataTable zosta³o przypisane!"));
        UpdateQuestList();
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("QuestDataTable jest NULL!"));
    }
}

void AQuestManager::UpdateQuestList()
{
    // Za³aduj dane z QuestDataTable i zaktualizuj QuestList
    TArray<FQuestStruct1> LoadedQuestsOptions;
    if (QuestDataTable)
    {
        TArray<FName> RowNames = QuestDataTable->GetRowNames();

        for (const FName& RowName : RowNames)
        {
            FQuestStruct1* Row = QuestDataTable->FindRow<FQuestStruct1>(RowName, TEXT(""));
            if (Row)
            {
                LoadedQuestsOptions.Add(*Row); // Dodajemy kopiê obiektu do tablicy
            }
        }
    }
    QuestList = LoadedQuestsOptions;
}

void AQuestManager::PrintAllQuests()
{
    if (!QuestDataTable)
    {
        UE_LOG(LogTemp, Error, TEXT("QuestDataTable is NULL!"));
        return;
    }

    TArray<FName> RowNames = QuestDataTable->GetRowNames();
    for (const FName& RowName : RowNames)
    {
        FQuestStruct1* QuestRow = QuestDataTable->FindRow<FQuestStruct1>(RowName, TEXT(""));

        if (QuestRow)
        {
           
            UE_LOG(LogTemp, Warning, TEXT("Quest Name: , bIsActive: %s"),
                 QuestRow->bIsActive ? TEXT("True") : TEXT("False"));

        }
    }
}
