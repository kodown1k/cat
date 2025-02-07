#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractionInterface.generated.h"

UINTERFACE(MinimalAPI)
class UInteractionInterface : public UInterface
{
    GENERATED_BODY()
};

/**
 * Interfejs do obs³ugi interakcji
 */
class CATTEST_API IInteractionInterface
{
    GENERATED_BODY()

public:
    // Funkcja interakcji (np. naciœniêcie klawisza)
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
    void Interact();

    // Funkcja pobieraj¹ca tekst interakcji
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
    FText GetInteractionText() const;
};
