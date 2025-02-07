// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PatrolType.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BT_FindPatrolPositionsByTags.generated.h"

/**
 * Behavior Tree Task to patrol actors with specific tags.
 */
UCLASS()
class CATTEST_API UBT_FindPatrolPositionsByTags : public UBTTaskNode
{
	GENERATED_BODY()
public:

	explicit UBT_FindPatrolPositionsByTags(const FObjectInitializer& ObjectInitializer);
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	UFUNCTION(BlueprintCallable, Category="Patrol")
	AActor* PatrolInCircle(AActor* Owner);

	UFUNCTION(BlueprintCallable, Category="Patrol")
	AActor* PatrolBackAndForth(AActor* Owner);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Patrol", meta=(AllowPrivateAccess="true"))
	float SearchRadius = 15000.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Patrol", meta=(AllowPrivateAccess="true"))
	TArray<FName> ActorTagsToPatrol = {};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Patrol", meta=(AllowPrivateAccess="true"))
	EPatrolType PatrolType = EPatrolType::Circle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Patrol", meta=(AllowPrivateAccess="true"))
	FBlackboardKeySelector PatrolLocationBlackboardKey;

	TArray<AActor*> SortTaggedActorsByDistance(AActor* Owner) const;
	
	int32 CurrentActorIndex = 0;
};
