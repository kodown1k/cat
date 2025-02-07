#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestStruct1.h"
#include "QuestManager.generated.h"

UCLASS()
class CATTEST_API AQuestManager : public AActor
{
	GENERATED_BODY()

public:
	AQuestManager();

protected:
	virtual void BeginPlay() override;

public:

	// Dodawanie nowego questa
	UFUNCTION(BlueprintCallable, Category = "Quests")
	void GiveQuest(const FQuestStruct1& NewQuest);

	// Aktualizacja postêpu questa
	UFUNCTION(BlueprintCallable, Category = "Quests")
	void UpdateQuestProgress(const FString& QuestName, int32 Amount);

	

	// Pobieranie aktywnych questów
	UFUNCTION(BlueprintCallable, Category = "Quests")
	TArray<FQuestStruct1> GetActiveQuests() const;

	// Lista aktualnych questów
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quests")
	TArray<FQuestStruct1> QuestList;
};
