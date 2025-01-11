// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventorySlot.h"
#include "GameFramework/Actor.h"
#include "PickUpItem.generated.h"


class USphereComponent;

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
	virtual void OnConstruction(const FTransform& Transform) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FInventoryItem ItemStructure;

	UPROPERTY()
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInterface* OverlayMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Materials")
	UMaterialInstanceDynamic* DynamicMaterial;

	UPROPERTY(VisibleDefaultsOnly, Category=Item)
	USphereComponent* SphereCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FCollisionProfileName CollisionProfile;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
	                    AActor* OtherActor,
	                    UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex,
	                    bool bFromSweep,
	                    const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void SetupCollisions();

	void log(FString msg) const;

private:
	float CurrentLineThickness = 0.0f;
	float TargetLineThickness = 0.0f;
	float MaxTargetThickness = 0.5;
	float LerpSpeed = 0.0;
	bool bIsOverlapping = false;
};
