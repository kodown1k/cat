// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "USpellBase.h"
#include "FireBallProjectile.h"
#include "Fireball.generated.h"

/**
 * 
 */
UCLASS()
class CATTEST_API UFireball : public USpellBase
{
	GENERATED_BODY()
public:
    UFireball();

    // Implementacja rzucania czaru
    virtual void CastSpell_Implementation(AActor* Caster) override;
   
    
    
protected:
    // Klasa blueprinta pocisku
    UPROPERTY(EditDefaultsOnly, Category = "Fireball")
    TSubclassOf<AFireBallProjectile> FireballProjectileClass;

    
    
	
};
