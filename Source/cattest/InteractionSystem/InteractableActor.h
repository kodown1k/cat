#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionInterface.h"  // Zawiera nasz interfejs
#include "Components/WidgetComponent.h"  // Do widget�w
#include "InteractableActor.generated.h"

UCLASS()
class CATTEST_API AInteractableActor : public AActor, public IInteractionInterface
{
    GENERATED_BODY()

public:
    // Konstruktor
    AInteractableActor();

protected:
    // Funkcja, kt�ra jest wywo�ywana po rozpocz�ciu gry
    virtual void BeginPlay() override;

public:
    // Zmienna przechowuj�ca widget interakcji
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
    UWidgetComponent* InteractionWidget;

    // Funkcja interakcji, kt�r� mo�emy wywo�a� (np. klikni�cie F)
    virtual void Interact_Implementation() override;

    // Funkcja pobieraj�ca tekst interakcji
    virtual FText GetInteractionText_Implementation() const override;

    // Zmienna, kt�ra zawiera tekst interakcji
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
    FText InteractionText;
};