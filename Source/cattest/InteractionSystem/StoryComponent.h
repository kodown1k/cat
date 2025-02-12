// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseNPC.h"
#include "EnhancedInputComponent.h"
#include "DialogueInterface.h"
#include "Kismet/GameplayStatics.h"
#include "../Questsystem/QuestManager.h"
#include "../QuestSystem/QuestJournal.h"

#include "StoryComponent.generated.h"





UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CATTEST_API UStoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	//DELEGAT DLA WYLACZANIA RAYCASTA W MOMENCIE ZAKONCZENIA DIALOGU
	

	

	void ResumeRaycast();
	// Sets default values for this component's properties
	UStoryComponent();

	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	void Interact();

	void InteractWithNPC();
	void InteractWithWorld();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> MainMenuWidgetRef;

	AActor* HitActor; // Aktor na ktorego aktualnie wskazuje ray trace
	ABaseNPC* NewHitActor;


	bool canPerformRaycast;


	//SEKCJA QUESTOW
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MenuAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quest")
	TObjectPtr<AQuestManager> QuestManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	UDataTable* QuestManagerDatatable;

	// Referencja do widgetu QuestLog (jeœli chcesz go pokazaæ)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UQuestJournal> QuestLogWidgetClass;

	// Widget QuestLog, który ma byæ wyœwietlony
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	TObjectPtr<UQuestJournal> QuestLogWidget;

	// Inicjalizacja komponentu
	void OpenMenuWidget();

	void ShowQuestLog();
	UFUNCTION()
	void UpdateDataTable(int32 QuestID, bool NewStatus);
	UFUNCTION()
	void UpdateDataTableCompleteQuest(int32 QuestID, bool NewStatus);
	UFUNCTION()
	bool IsQuestActive(int32 QuestID);
	UFUNCTION()
	bool IsQuestCompleted(int32 QuestID);

	
	
	//

protected:
	virtual void BeginPlay() override;

	
	FTimerHandle TimerHandle;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	 
		
};
