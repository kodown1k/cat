#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DialogStruct.h"
#include "DialogueInterface.generated.h"

// Ustawienie interfejsu
UINTERFACE(MinimalAPI)
class UDialogueInterface : public UInterface
{
    GENERATED_BODY()
};

class CATTEST_API IDialogueInterface
{
    GENERATED_BODY()

public:
    // Funkcja do rozpoczêcia dialogu
    virtual void StartDialogue() = 0;

    
};