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
 * Interfejs do obs�ugi interakcji
 */
class CATTEST_API IInteractionInterface
{
    GENERATED_BODY()

public:
    // Funkcja interakcji (np. naci�ni�cie klawisza)
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
    void Interact();

    // Funkcja pobieraj�ca tekst interakcji
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
    FText GetInteractionText() const;
};
