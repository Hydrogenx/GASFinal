// Copyright Epic Games, Inc. All Rights Reserved.

#include "GASFinalGameMode.h"
#include "GASFinalCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGASFinalGameMode::AGASFinalGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
