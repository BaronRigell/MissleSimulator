// Copyright Epic Games, Inc. All Rights Reserved.


#include "MissleSimulator/Public/MissleSimulatorGameModeBase.h"

#include "MSPlayerController.h"

AMissleSimulatorGameModeBase::AMissleSimulatorGameModeBase()
{
	PlayerControllerClass = AMSPlayerController::StaticClass();
}
