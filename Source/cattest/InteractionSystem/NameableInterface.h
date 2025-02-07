#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "NameableInterface.generated.h"

UINTERFACE(MinimalAPI)
class UNameableInterface : public UInterface
{
    GENERATED_BODY()
};

class CATTEST_API INameableInterface
{
    GENERATED_BODY()

public:
    // Metoda do ustawiania nazwy
    virtual void SetName(const FString& Name) = 0;
    
};