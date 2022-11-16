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
	for (auto PointActor : PointActors)
	{
		if (IsValid(PointActor)) PointActor->Destroy();
	}
}

void AMissleSimulatorGameModeBase::SimulateFromParams(FVector StartCoordinates, float Angle, float Height,
                                                      float Velocity)
{
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	const float XCoord=StartCoordinates.X+200.f;
	 Missile = GetWorld()->SpawnActor<ABallisticMissle>(FVector(XCoord,StartCoordinates.Y, Height),
	 	FRotator(Angle, 0.f, 0.f), ActorSpawnParameters);

	//Исправить вектор и локацию спавна ракеты
	FVector CurrentVelocity;
	CurrentVelocity = Velocity*UKismetMathLibrary::GetDirectionUnitVector(Missile->GetActorLocation(), 
	Missile->GetActorLocation());

	UE_LOG(LogTemp, Error, TEXT("%f, %f, %f - missle velocity"), CurrentVelocity.X, CurrentVelocity.Y, CurrentVelocity.Z);
	
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

	//const auto PC = GetWorld()->GetFirstPlayerController<AMSPlayerController>();
	
}
