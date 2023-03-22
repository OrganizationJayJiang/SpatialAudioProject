// Copyright Epic Games, Inc. All Rights Reserved.

#include "SpatialAudioProjectGameMode.h"
#include "SpatialAudioProjectHUD.h"
#include "SpatialAudioProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASpatialAudioProjectGameMode::ASpatialAudioProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ASpatialAudioProjectHUD::StaticClass();
}
