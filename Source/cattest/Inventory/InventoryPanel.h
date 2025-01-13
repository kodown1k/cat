// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "InventoryPanel.generated.h"

/**
 * 
 */
UCLASS()
class CATTEST_API UInventoryPanel : public UUserWidget
{
	GENERATED_BODY()

	UFUNCTION()
	virtual void NativeOnInitialized() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	UHorizontalBox* OnionsBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	UTextBlock* HeaderText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	UImage* BackgroundImage;
};
