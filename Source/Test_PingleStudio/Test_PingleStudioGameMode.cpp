// Copyright Epic Games, Inc. All Rights Reserved.

#include "Test_PingleStudioGameMode.h"
#include "Test_PingleStudioHUD.h"
#include "Test_PingleStudioCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATest_PingleStudioGameMode::ATest_PingleStudioGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATest_PingleStudioHUD::StaticClass();
}
