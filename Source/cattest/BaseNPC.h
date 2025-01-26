// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DialogueSystem.h"
#include "DialogueInterface.h"  // Jeœli u¿ywasz interfejsu
#include "Engine/DataTable.h"
#include "BaseNPC.generated.h"

UCLASS(Blueprintable)
class CATTEST_API ABaseNPC : public ACharacter, public IDialogueInterface
{
	GENERATED_BODY()

public:
	// Konstruktor
	ABaseNPC();

	// Funkcja rozpoczynaj¹ca dialog
	virtual void StartDialogue() override;

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
	int32 NPC_ID;

	FGameplayTagContainer PlayerTags;

	// Historia wybranych dialogów
	TArray<int32> SelectedDialogueIDs;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UDialogueWidget> DialogueWidgetClass;

protected:
	// Called when the game starts or when spawned
	UPROPERTY()
	UDialogueSystem* DialogueSystem;

	// Tabela danych dialogowych dla tego NPC
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	UDataTable* DialogueDataTable;

	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
