// Fill out your copyright notice in the Description page of Project Settings.


#include "USpellBase.h"

void USpellBase::CastSpell_Implementation(AActor* Caster)
{
    if (GEngine)
    {
        FString CasterName = Caster ? Caster->GetName() : TEXT("Unknown");
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Casting spell: %s by %s"), *SpellName, *CasterName));
    }
}