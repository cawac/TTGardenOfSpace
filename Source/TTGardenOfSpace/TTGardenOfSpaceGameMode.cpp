// Copyright Epic Games, Inc. All Rights Reserved.

#include "TTGardenOfSpaceGameMode.h"
#include "UObject/ConstructorHelpers.h"

ATTGardenOfSpaceGameMode::ATTGardenOfSpaceGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Character/BP_Character"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	
}
