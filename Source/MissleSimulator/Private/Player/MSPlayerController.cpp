// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MSPlayerController.h"

void AMSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	SetShowMouseCursor(true);
}
