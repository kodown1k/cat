// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_FindPatrolPositionsByTags.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

AActor* UBT_FindPatrolPositionsByTags::PatrolInCircle(AActor* Owner)
{
    TArray<AActor*> Actors = SortTaggedActorsByDistance(Owner);
    
    if (Actors.Num() == 0) return Owner;

    AActor* PatrolActor = Actors[CurrentActorIndex];
    CurrentActorIndex = (CurrentActorIndex + 1) % Actors.Num();

    return PatrolActor;
}


bool GBForwardDirection = true;

AActor* UBT_FindPatrolPositionsByTags::PatrolBackAndForth(AActor* Owner)
{
    TArray<AActor*> Actors = SortTaggedActorsByDistance(Owner);
    for (const FName& Tag : ActorTagsToPatrol)
    {
        TArray<AActor*> TaggedActors;
        UGameplayStatics::GetAllActorsWithTag(GetWorld(), Tag, TaggedActors);
        Actors.Append(TaggedActors);
    }

    Actors.Sort([Owner](const AActor& A, const AActor& B)
    {
        return FVector::DistSquared(Owner->GetActorLocation(), A.GetActorLocation()) < FVector::DistSquared(Owner->GetActorLocation(), B.GetActorLocation());
    });

    if (Actors.Num() == 0) return Owner;

    AActor* PatrolActor = Actors[CurrentActorIndex];
	
    if (GBForwardDirection)
    {
        CurrentActorIndex++;
        if (CurrentActorIndex >= Actors.Num())
        {
            CurrentActorIndex = Actors.Num() - 1;
            GBForwardDirection = false;
        }
    }
    else
    {
        CurrentActorIndex--;
        if (CurrentActorIndex < 0)
        {
            CurrentActorIndex = 0;
            GBForwardDirection = true;
        }
    }

    return PatrolActor;
}

TArray<AActor*> UBT_FindPatrolPositionsByTags::SortTaggedActorsByDistance(AActor* Owner) const
{
	TArray<AActor*> Actors;
	for (const FName& Tag : ActorTagsToPatrol)
	{
		TArray<AActor*> TaggedActors;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), Tag, TaggedActors);
		Actors.Append(TaggedActors);
	}

	Actors.Sort([Owner](const AActor& A, const AActor& B)
	{
		return FVector::DistSquared(Owner->GetActorLocation(), A.GetActorLocation()) < FVector::DistSquared(Owner->GetActorLocation(), B.GetActorLocation());
	});
	
	return Actors;
}


UBT_FindPatrolPositionsByTags::UBT_FindPatrolPositionsByTags(const FObjectInitializer& ObjectInitializer)
{
	NodeName = "Find actors to patrol by tags.";
}

EBTNodeResult::Type UBT_FindPatrolPositionsByTags::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	if (AActor* Owner = Cast<AActor>(OwnerComp.GetOwner()))
	{
		AActor* PatrolActor = Owner;
		switch (PatrolType)
		{
		case EPatrolType::Circle:
			PatrolActor = PatrolInCircle(Owner);
			break;
		
		case EPatrolType::BackAndForth:
			PatrolActor = PatrolBackAndForth(Owner);
			break;
		default:
			break;
		}
		OwnerComp.GetBlackboardComponent()->SetValueAsObject( PatrolLocationBlackboardKey.SelectedKeyName, PatrolActor);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
