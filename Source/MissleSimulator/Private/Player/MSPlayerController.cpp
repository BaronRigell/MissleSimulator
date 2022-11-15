// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MSPlayerController.h"

void AMSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ToggleInput(false);
}

void AMSPlayerController::LockMovement()
{
	
}

void AMSPlayerController::ToggleInput(bool bInputNew)
{
	if (!bInputNew) SetInputMode(FInputModeUIOnly());
	else SetInputMode(FInputModeGameOnly());
	SetShowMouseCursor(!bInputNew);
}
