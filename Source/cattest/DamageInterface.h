// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DamageInterface.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI)
class UDamageInterface : public UInterface
{
	GENERATED_BODY()
};

class CATTEST_API IDamageInterface {
    GENERATED_BODY()

public:
    // Funkcja do zadawania obra¿eñ
    virtual void GetDamaged(int DamageAmount) = 0;
};
