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
	Super::BeginPlay();

	
}


// Funkcja dodaj¹ca questa do listy
void AQuestManager::GiveQuest(const FQuestStruct1& NewQuest)
{
	QuestList.Add(NewQuest);
	UE_LOG(LogTemp, Warning, TEXT("Dodano nowy quest: %s"), *NewQuest.QuestName);
}

// Funkcja aktualizuj¹ca postêp questa
void AQuestManager::UpdateQuestProgress(const FString& QuestName, int32 Amount)
{
	for (FQuestStruct1& Quest : QuestList)
	{
		if (Quest.QuestName == QuestName)
		{
			Quest.CurrentProgress += Amount;
			UE_LOG(LogTemp, Warning, TEXT("Quest %s: postêp %d/%d"), *Quest.QuestName, Quest.CurrentProgress, Quest.RequiredAmount);

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
TArray<FQuestStruct1> AQuestManager::GetActiveQuests() const
{
	return QuestList;
}
