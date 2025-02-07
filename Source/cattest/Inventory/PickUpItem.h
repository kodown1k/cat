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
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void OnConstruction(const FTransform& Transform) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	FInventoryItem ItemStructure;

	UPROPERTY()
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(NotBlueprintable)
	UMaterialInterface* DefaultOverlayMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Materials")
	UMaterialInterface* OutlineMaterial;
	
	UPROPERTY(NotBlueprintable)
	UMaterialInstanceDynamic* DynamicMaterial;

	UPROPERTY(VisibleDefaultsOnly, Category=Item)
	USphereComponent* SphereCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FCollisionProfileName CollisionProfile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float SphereCollisionRadius = 50.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowTrace")
	float CurrentLineThickness = 0.0f;

	UPROPERTY(BlueprintReadWrite, Category = "ShowTrace")
	float TargetLineThickness = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowTrace")
	float MaxTargetThickness = 0.5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowTrace")
	float LerpSpeed = 0.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShowTrace")
	bool bIsOverlapping = false;
	
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

	void SetupMaterials();
private:
	
};
