// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryPanel.h"

void UInventoryPanel::NativeOnInitialized()
{
	// Super::NativeOnInitialized();
	HeaderText->SetText(FText::FromString("Inventory Panel"));
}
