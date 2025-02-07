// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "W_QuestEntry.h"
#include "QuestManager.h"
#include "Components/VerticalBox.h"

#include "QuestJournal.generated.h"


/**
 * 
 */
UCLASS()
class CATTEST_API UQuestJournal : public UCommonUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> QuestList;
	
	UFUNCTION(BlueprintCallable, Category = "Quest Log")
	void PopulateQuestList(TArray<FQuestStruct1> ActiveQuests);

	void DebugQuestListContents();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UW_QuestEntry> QuestEntryWidgetClass;

};
