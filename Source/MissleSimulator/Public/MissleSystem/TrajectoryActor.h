// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrajectoryActor.generated.h"

UCLASS()
class MISSLESIMULATOR_API ATrajectoryActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ATrajectoryActor();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite);
	UStaticMeshComponent* CubeMesh;
	
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:	

private:
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
