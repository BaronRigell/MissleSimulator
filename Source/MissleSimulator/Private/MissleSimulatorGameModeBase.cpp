// Copyright Epic Games, Inc. All Rights Reserved.


#include "MissleSimulator/Public/MissleSimulatorGameModeBase.h"

#include "MSPlayerController.h"
#include "TrajectoryActor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AMissleSimulatorGameModeBase::AMissleSimulatorGameModeBase()
{
	PlayerControllerClass = AMSPlayerController::StaticClass();
}

void AMissleSimulatorGameModeBase::SetupTrajectory(TArray<FVector>& Locations)
{
	for (const FVector& Location : Locations)
	{
		GetWorld()->SpawnActor<ATrajectoryActor>(Location, FRotator::ZeroRotator);
	}
}

void AMissleSimulatorGameModeBase::SetupLandingZone(FVector& LandingLocation)
{
	
}

void AMissleSimulatorGameModeBase::SimulateFromParams(FVector StartCoordinates, float Angle, float Height,
                                                      float Velocity)
{
	 Missile = GetWorld()->SpawnActor<ABallisticMissle>(/* Need Params */);

	FVector CurrentVelocity;
	CurrentVelocity = Velocity*UKismetMathLibrary::GetDirectionUnitVector(Missile->GetActorLocation(), 
	Missile->GetActorLocation());
	
	Missile->GetMesh()->SetPhysicsLinearVelocity(CurrentVelocity);

	FHitResult HitResult;
	TArray<FVector> PointLocations;
	FVector LastTraceDest;
	
	UGameplayStatics::Blueprint_PredictProjectilePath_ByTraceChannel(GetWorld(), HitResult, PointLocations,
		LastTraceDest, Missile->GetActorLocation(), CurrentVelocity, true,
		10.f, ECollisionChannel::ECC_Visibility, true, TArray<AActor*>{Missile.Get()},
		EDrawDebugTrace::Persistent, 10.f, 15.f, 5.f);

	SetupTrajectory(PointLocations);
	SetupLandingZone(HitResult.Location);

	const auto PC = GetWorld()->GetFirstPlayerController<AMSPlayerController>();
	
}
