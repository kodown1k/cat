#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DialogueSystem.h"
#include "DialogueInterface.h"
#include "Engine/DataTable.h"
#include "Components/WidgetComponent.h"
#include "NameableInterface.h"
#include "InteractionInterface.h"  // Tw�j interfejs interakcji
#include "NPCWidget.h"
#include "InteractableActor.h"  // Interfejs interakcji
#include "BaseNPC.generated.h"

UCLASS(Blueprintable)
class CATTEST_API ABaseNPC : public ACharacter, public IInteractionInterface, public IDialogueInterface
{
	GENERATED_BODY()

public:
	// Konstruktor
	ABaseNPC();

	// Funkcja rozpoczynaj�ca dialog (implementacja interfejsu IDialogueInterface)
	virtual void StartDialogue() override;


	//DIALOG 
	//------------------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC")
	int32 NPC_ID;

	FGameplayTagContainer PlayerTags;

	// Historia wybranych dialog�w
	TArray<int32> SelectedDialogueIDs;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UDialogueWidget> DialogueWidgetClass;

	// Widget do wy�wietlania nazwy NPC
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	class UWidgetComponent* NameWidgetComponent;

	bool bIsDialogueActive = false;


	//gowno do usuniecia 
	//------------------------------------------------------
	// Funkcja do ustawiania nazwy NPC
	void SetNPCName(const FString& Name);

	// INTERAKCJA
	//-------------------------------------------------------
public:
	// Zmienna przechowuj�ca tekst interakcji
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	FText InteractionText;

	// Funkcja do ustawiania tekstu interakcji
	void SetInteractionText(const FText& NewText);

	// Implementacja funkcji interakcji
	virtual void Interact_Implementation() override;

	// Implementacja funkcji pobierania tekstu interakcji
	virtual FText GetInteractionText_Implementation() const override;

	// Widget do interakcji
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* InteractionWidget;

	// Funkcja do wy�wietlania/ukrywania widgetu interakcji
	void ShowInteractionWidget(bool bShow);

	// GAME TAG DO WZNOWIENIA RAYCASTOW
	//-------------------------------------------------------

	

protected:
	// Przechowuje tagi aktora
	UPROPERTY(EditAnywhere)
	FGameplayTagContainer ActorTags;

protected:
	// System dialogowy
	UPROPERTY()
	UDialogueSystem* DialogueSystem;

	// Tabela danych dialogowych dla tego NPC
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	UDataTable* DialogueDataTable;

	virtual void BeginPlay() override;

public:
	// Funkcja wywo�ywana w ka�dym ticku
	virtual void Tick(float DeltaTime) override;

	// Funkcja do mapowania akcji na wej�ciu (np. naci�ni�cie klawisza)
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
