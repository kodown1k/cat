// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_BaseEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BaseEnemy.h"

#include "Kismet/GameplayStatics.h"

AAIController_BaseEnemy::AAIController_BaseEnemy()
{
	// Utworzenie obiektu percepcji z domyœlnymi wartoœciami
	SetupAIPerception();
}

void AAIController_BaseEnemy::BeginPlay()
{

	CharacterObj = Cast<ABaseEnemy>(GetPawn());
	if (!CharacterObj)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Character Found"));
		return;
	}

	if (AIBehaviorTree)
	{
		UE_LOG(LogTemp, Warning, TEXT("RunBehaviorTree"));
		RunBehaviorTree(AIBehaviorTree);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No BehaviorTree"));
	}

	// Ustawienie wartoœci domyœlnych dla zmiennych w Blackboard oraz zakresu widzenia
	SetupBlackboard();
	SetupSightRadius();

	// Ustawienie nas³uchu na aktualizacjê percepcji
	UAIPerceptionComponent* AIPerc = GetAIPerceptionComponent();
	if (AIPerc != nullptr) {
		AIPerc->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &AAIController_BaseEnemy::OnTargetPerceptionUpdatedDelegate);

	}
}

void AAIController_BaseEnemy::SetupBlackboard()
{
	UBlackboardComponent* AIBlackboard = GetBlackboardComponent();

	if (AIBlackboard == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Blackboard not found"));
		return;
	}

	// Do uzupe³nienia gdy przygotowany bêdzie obiekt Blackboard

	/*AIBlackboard->SetValueAsObject(TEXT("Player"), UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	AIBlackboard->SetValueAsBool(TEXT("IsPatrolling"), CharacterObj->IsPatrolling);
	if (EnemyCharacter->IsPatrolling)
	{
		AIBlackboard->SetValueAsBool(TEXT("PatrolPointIndex"), 0);
		AIBlackboard->SetValueAsObject(TEXT("Path"), EnemyCharacter->PatrolPath);
		AIBlackboard->SetValueAsFloat(TEXT("DefaultWaitTime"), EnemyCharacter->DefaultWaitTime);
		AIBlackboard->SetValueAsFloat(TEXT("RandomDeviation"), EnemyCharacter->RandomDeviation);
	}*/
}

void AAIController_BaseEnemy::SetupAIPerception()
{
	// Utworzenie domyœlnego obiektu percepcji
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component"));
	// Utworzenie domyœlnego obiektu zmys³u wzroku
	AISenseConfigSight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SenseSight"));

	// Ustawnie jakie postacie zmys³ wzroku ma wykrywaæ
	AISenseConfigSight->DetectionByAffiliation.bDetectFriendlies = false;
	AISenseConfigSight->DetectionByAffiliation.bDetectEnemies = true;
	AISenseConfigSight->DetectionByAffiliation.bDetectNeutrals = true;

	// Ustawinie zakresu wzroku
	AISenseConfigSight->SightRadius = 100.0f;
	AISenseConfigSight->LoseSightRadius = 150.0f;

	// Ustawienie jako g³ówny zmys³ i konfiguracja wzroku
	AIPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	AIPerceptionComponent->ConfigureSense(*AISenseConfigSight);


	SetGenericTeamId(FGenericTeamId(2));
}

void AAIController_BaseEnemy::SetupSightRadius()
{
	UAIPerceptionComponent* AIPerception = GetAIPerceptionComponent();
	if (AIPerception != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI perception found"));
		FAISenseID SenseId = UAISense::GetSenseID(UAISense_Sight::StaticClass());
		UAISenseConfig* SenseConfig = AIPerception->GetSenseConfig(SenseId);
		if (SenseConfig != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Sight config found"));
			UAISenseConfig_Sight* ConfigSight = Cast<UAISenseConfig_Sight>(SenseConfig);
			ConfigSight->SightRadius = CharacterObj->SightRadius;
			ConfigSight->LoseSightRadius = CharacterObj->LoseSightRadius;
			UE_LOG(LogTemp, Warning, TEXT("Sight Radius %f"), ConfigSight->SightRadius);
			AIPerception->RequestStimuliListenerUpdate();
		}
	}
}

void AAIController_BaseEnemy::OnTargetPerceptionUpdatedDelegate(AActor* Actor, FAIStimulus Stimulus)
{
	UE_LOG(LogTemp, Warning, TEXT("Perception Update"));

	// Do uzupe³nienia gdy utworzony bêdzie obiekt Blackboard

	//APlayerCharacter* Target = Cast<APlayerCharacter>(Actor);
	//if (Target == nullptr)
	//{
	//	//UE_LOG(LogTemp, Warning, TEXT("Target nullptr"));
	//	return;
	//}

	//UBlackboardComponent* AIBlackboard = GetBlackboardComponent();
	//if (Stimulus.WasSuccessfullySensed())
	//{
	//	//UE_LOG(LogTemp, Warning, TEXT("Target in sight"));
	//	AIBlackboard->SetValueAsVector(TEXT("PlayerLocation"), Actor->GetActorLocation());
	//	AIBlackboard->SetValueAsObject(TEXT("Player"), Target);
	//	AIBlackboard->SetValueAsBool(TEXT("IsMoveToPlayerPossible"), true);
	//}
	//else {
	//	//UE_LOG(LogTemp, Warning, TEXT("Target out of sight"));
	//	AIBlackboard->ClearValue(TEXT("PlayerLocation"));
	//	AIBlackboard->ClearValue(TEXT("Player"));
	//	AIBlackboard->SetValueAsBool(TEXT("IsMoveToPlayerPossible"), false);
	//}
}