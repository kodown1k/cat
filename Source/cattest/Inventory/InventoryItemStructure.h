// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryItemStructure.generated.h"

/** Struktura obiektu w inventory */
USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Name"))
	FText Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Stackable", MakeStructureDefaultValue="False"))
	bool Stackable;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Quantity", MakeStructureDefaultValue="0"))
	int32 Quantity = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Thumbnail", MakeStructureDefaultValue="None"))
	TObjectPtr<UTexture2D> Thumbnail;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="Mesh", MakeStructureDefaultValue="None"))
	TObjectPtr<UStaticMesh> Mesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(DisplayName="SpawnSound", MakeStructureDefaultValue="None"))
	USoundBase* SpawnSound;
};

/**
 * 
 */
class CATTEST_API InventoryItemStructure
{
public:
	InventoryItemStructure();
	~InventoryItemStructure();
};
