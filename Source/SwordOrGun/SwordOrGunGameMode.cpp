// Copyright Epic Games, Inc. All Rights Reserved.

#include "SwordOrGunGameMode.h"
#include "SwordOrGunCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASwordOrGunGameMode::ASwordOrGunGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
