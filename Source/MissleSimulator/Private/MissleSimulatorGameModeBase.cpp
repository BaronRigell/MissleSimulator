// Copyright Epic Games, Inc. All Rights Reserved.


#include "MissleSimulator/Public/MissleSimulatorGameModeBase.h"

#include "MSPlayerController.h"
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
		const auto Traj = GetWorld()->SpawnActor<ATrajectoryActor>(TrajectoryActorClass, Location,
			FRotator::ZeroRotator);
		PointActors.Add(Traj);
	}
}

void AMissleSimulatorGameModeBase::SetupLandingZone(FVector& LandingLocation)
{
	
}

void AMissleSimulatorGameModeBase::ClearSimulation()
{
	Missile->Destroy();
	for (const auto PointActor : PointActors)
	{
		if (IsValid(PointActor)) PointActor->Destroy();
	}
}

void AMissleSimulatorGameModeBase::SimulateFromParams(FVector StartCoordinates, float Angle, float Height,
                                                      float Velocity)
{
	Velocity*=100.f;
	Height*=100.f;
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	 

	//Исправить локацию спавна ракеты
	FVector CurrentVelocity(FMath::Cos(Angle)*Velocity, 0.f, FMath::Sin(Angle)*Velocity);

	UE_LOG(LogTemp, Error, TEXT("%f, %f, %f - missle velocity"), CurrentVelocity.X, CurrentVelocity.Y, CurrentVelocity.Z);
	
	Missile->GetMovement()->Velocity = CurrentVelocity;
	
	FHitResult HitResult;
	TArray<FVector> PointLocations;
	FVector LastTraceDest;
	
	UGameplayStatics::Blueprint_PredictProjectilePath_ByTraceChannel(GetWorld(), HitResult, PointLocations,
		LastTraceDest, Missile->GetActorLocation(), CurrentVelocity, true,
		10.f, ECollisionChannel::ECC_Visibility, true, TArray<AActor*>{Missile.Get()},
		EDrawDebugTrace::Persistent, 10.f, 10.f, 5.f);

	SetupTrajectory(PointLocations);
	SetupLandingZone(HitResult.Location);

	const auto PC = GetWorld()->GetFirstPlayerController<AMSPlayerController>();
	
}
