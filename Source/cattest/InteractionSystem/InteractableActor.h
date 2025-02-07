#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionInterface.h"  // Zawiera nasz interfejs
#include "Components/WidgetComponent.h"  // Do widgetów
#include "InteractableActor.generated.h"

UCLASS()
class CATTEST_API AInteractableActor : public AActor, public IInteractionInterface
{
    GENERATED_BODY()

public:
    // Konstruktor
    AInteractableActor();

protected:
    // Funkcja, która jest wywo³ywana po rozpoczêciu gry
    virtual void BeginPlay() override;

public:
    // Zmienna przechowuj¹ca widget interakcji
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
    UWidgetComponent* InteractionWidget;

    // Funkcja interakcji, któr¹ mo¿emy wywo³aæ (np. klikniêcie F)
    virtual void Interact_Implementation() override;

    // Funkcja pobieraj¹ca tekst interakcji
    virtual FText GetInteractionText_Implementation() const override;

    // Zmienna, która zawiera tekst interakcji
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
    FText InteractionText;
};