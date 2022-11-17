// Fill out your copyright notice in the Description page of Project Settings.


#include "MissleSystem/TrajectoryActor.h"

#include "BallisticMissle.h"

ATrajectoryActor::ATrajectoryActor()
{
	PrimaryActorTick.bCanEverTick = false;

	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>("MeshPoint");
	RootComponent = CubeMesh;
}

void ATrajectoryActor::BeginPlay()
{
	Super::BeginPlay();
}

void ATrajectoryActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	CubeMesh->OnComponentEndOverlap.AddDynamic(this, &ATrajectoryActor::OnEndOverlap);
}

void ATrajectoryActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CubeMesh->OnComponentEndOverlap.RemoveDynamic(this, &ATrajectoryActor::OnEndOverlap);
	
	Super::EndPlay(EndPlayReason);
}

void ATrajectoryActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s registered"), *(this->GetName()))
	if (Cast<ABallisticMissle>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is going to die"), *(this->GetName()))
		Destroy();
	}
}
