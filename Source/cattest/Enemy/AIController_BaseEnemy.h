// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "AIController.h"
#include "AIController_BaseEnemy.generated.h"

class ABaseEnemy;
/**
 *
 */
UCLASS()
class CATTEST_API AAIController_BaseEnemy : public AAIController
{
	GENERATED_BODY()

public:
	AAIController_BaseEnemy();

	// Komponent percepcji AI
	UPROPERTY(VisibleAnywhere, meta = (Category = "AI"))
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent = nullptr;
	TObjectPtr<class UAISenseConfig_Sight> AISenseConfigSight = nullptr;

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	UBehaviorTree* AIBehaviorTree;

	ABaseEnemy* CharacterObj;

	/*
		Ustawienie wartoœci pocz¹tkowych zmiennych na Blackboard
	*/
	void SetupBlackboard();
	/*
		Ustawienie domyœlnych wartoœci percepcji
	*/
	void SetupAIPerception();


	/*
		Ustawnie zakresu wzroku zgodnie z danymi na obiekcie Character
	*/
	void SetupSightRadius();

	/*
		Funkcja wywo³ywana przy aktualizacji percepcji
	*/
	UFUNCTION()
	void OnTargetPerceptionUpdatedDelegate(AActor* Actor, FAIStimulus Stimulus);
};