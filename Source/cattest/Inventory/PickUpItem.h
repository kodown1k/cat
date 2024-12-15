// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "GameFramework/Actor.h"
#include "PickUpItem.generated.h"

UCLASS()
class CATTEST_API APickUpItem : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APickUpItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FInventoryItemStructure ItemStructure;
};
