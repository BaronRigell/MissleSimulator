// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BallisticMissle.generated.h"

UCLASS()
class MISSLESIMULATOR_API ABallisticMissle : public AActor
{
	GENERATED_BODY()
	
public:	
	ABallisticMissle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

};
