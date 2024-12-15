// Copyright Epic Games, Inc. All Rights Reserved.

#include "LabaZaliczenieGameMode.h"
#include "LabaZaliczenieCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALabaZaliczenieGameMode::ALabaZaliczenieGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
