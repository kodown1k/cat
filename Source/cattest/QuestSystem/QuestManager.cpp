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
    Super::BeginPlay(); // Upewnij si�, �e wywo�ujesz funkcj� bazow� na pocz�tku

    // Je�eli QuestDataTable jest przypisany, za�aduj questy
    if (QuestDataTable)
    {
        UE_LOG(LogTemp, Error, TEXT("QuestDataTable is  assigned!"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("QuestDataTable is not assigned!"));
    }
}

// Funkcja dodaj�ca questa do listy
void AQuestManager::GiveQuest(const FQuestStruct1& NewQuest)
{
    QuestList.Add(NewQuest); // Dodajemy obiekt, nie wska�nik
    UE_LOG(LogTemp, Warning, TEXT("Dodano nowy quest: %s"), *NewQuest.QuestName);
}

// Funkcja aktualizuj�ca post�p questa
void AQuestManager::UpdateQuestProgress(const FString& QuestName, int32 Amount)
{
    for (FQuestStruct1& Quest : QuestList) // Iteracja po referencjach
    {
        if (Quest.QuestName == QuestName)
        {
            Quest.CurrentProgress += Amount;
            UE_LOG(LogTemp, Warning, TEXT("Quest %s: Progress = %d"), *Quest.QuestName, Quest.CurrentProgress);

            // Sprawdzenie, czy quest zosta� uko�czony
            if (Quest.CurrentProgress >= Quest.RequiredAmount)
            {
                UE_LOG(LogTemp, Warning, TEXT("Quest %s uko�czony!"), *Quest.QuestName);
                // Tutaj mo�na doda� np. usuni�cie questa lub nagrody
            }
            return;
        }
    }
    UE_LOG(LogTemp, Warning, TEXT("Quest %s nie znaleziony!"), *QuestName);
}

// Pobieranie aktywnych quest�w
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
                ActiveQuests.Add(*Row); // Dodajemy kopi� quest�w tylko, je�li s� aktywne
            }
        }

        // Aktualizujemy list� aktywnych quest�w
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
        UE_LOG(LogTemp, Warning, TEXT("QuestDataTable zosta�o przypisane!"));
        UpdateQuestList();
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("QuestDataTable jest NULL!"));
    }
}

void AQuestManager::UpdateQuestList()
{
    // Za�aduj dane z QuestDataTable i zaktualizuj QuestList
    TArray<FQuestStruct1> LoadedQuestsOptions;
    if (QuestDataTable)
    {
        TArray<FName> RowNames = QuestDataTable->GetRowNames();

        for (const FName& RowName : RowNames)
        {
            FQuestStruct1* Row = QuestDataTable->FindRow<FQuestStruct1>(RowName, TEXT(""));
            if (Row)
            {
                LoadedQuestsOptions.Add(*Row); // Dodajemy kopi� obiektu do tablicy
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
