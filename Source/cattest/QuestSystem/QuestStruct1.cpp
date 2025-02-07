// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestStruct1.h"

FQuestStruct1::FQuestStruct1()
    :
    QuestName(TEXT("Default Quest")),
    Description(TEXT("Complete this task.")),
    RequiredAmount(1),
    CurrentProgress(0),
    bIsCompleted(false),
    QuestType(EQuestType::Move)
    
{
}

FQuestStruct1::~FQuestStruct1()
{
}
