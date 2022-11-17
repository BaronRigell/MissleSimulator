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
	if (IsValid(Missile.Get())) Missile->Destroy();
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
	float XCoord=FMath::Abs(Velocity*UKismetMathLibrary::DegCos(Angle)*((Velocity*UKismetMathLibrary::DegSin(Angle)-FMath::Sqrt(
		FMath::Square(Velocity*UKismetMathLibrary::DegSin(Angle)))+2*Height*9.8f)/9.8f));
	XCoord+=StartCoordinates.X;
	 Missile = GetWorld()->SpawnActor<ABallisticMissle>(BallisticMissileClass, FVector(200.f,StartCoordinates.Y, Height),
	 	FRotator(Angle, 0.f, 0.f), ActorSpawnParameters);

	//Исправить локацию спавна ракеты
	FVector CurrentVelocity(UKismetMathLibrary::DegCos(Angle)*Velocity, 0.f, UKismetMathLibrary::DegSin(Angle)*Velocity);

	UE_LOG(LogTemp, Error, TEXT("%f, %f, %f - missle velocity"), CurrentVelocity.X, CurrentVelocity.Y, CurrentVelocity.Z);
	
	Missile->GetMovement()->Velocity = CurrentVelocity;
	
	FHitResult HitResult;
	TArray<FVector> PointLocations;
	FVector LastTraceDest;
	
	UGameplayStatics::Blueprint_PredictProjectilePath_ByTraceChannel(GetWorld(), HitResult, PointLocations,
		LastTraceDest, Missile->GetActorLocation(), CurrentVelocity, true,
		10.f, ECollisionChannel::ECC_Visibility, true, TArray<AActor*>{Missile.Get()},
		EDrawDebugTrace::ForOneFrame, 10.f, 10.f, 5.f);

	SetupTrajectory(PointLocations);
	SetupLandingZone(HitResult.Location);

	const auto PC = GetWorld()->GetFirstPlayerController<AMSPlayerController>();
	
}
