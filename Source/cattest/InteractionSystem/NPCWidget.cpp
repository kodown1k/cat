#include "NPCWidget.h"
#include "Components/TextBlock.h"

void UNPCWidget::SetName(const FString& Name)
{
    if (NameTextBlock)
    {
        NameTextBlock->SetText(FText::FromString(Name));
        UE_LOG(LogTemp, Log, TEXT("Name set to: %s"), *Name);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("NameTextBlock is null!"));
    }
}

void UNPCWidget::NativeConstruct()
{
    Super::NativeConstruct();

    UE_LOG(LogTemp, Log, TEXT("NPCWidget: NativeConstruct() called"));

    // Sprawdü, czy NameTextBlock istnieje
    if (!NameTextBlock)
    {
        UE_LOG(LogTemp, Error, TEXT("NPCWidget: NameTextBlock is NULL in NativeConstruct!"));
        return;
    }

    UE_LOG(LogTemp, Log, TEXT("NPCWidget: NameTextBlock is valid in NativeConstruct!"));

    SetName(TEXT("NPC Name"));
}