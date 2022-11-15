// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MISSLESIMULATOR_API AMSPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
public:
	void LockMovement();
	void ToggleInput(bool bInputNew);
};
