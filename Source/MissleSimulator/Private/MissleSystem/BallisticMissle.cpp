// Fill out your copyright notice in the Description page of Project Settings.


#include "MissleSimulator/Public/MissleSystem/BallisticMissle.h"

#include "Kismet/KismetMathLibrary.h"

ABallisticMissle::ABallisticMissle()
{
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>("SphereCol");
	RootComponent = Sphere;
	
	RocketMesh = CreateDefaultSubobject<USkeletalMeshComponent>("RoocketMesh");
	RocketMesh->SetupAttachment(Sphere);

	/*RocketMovement = CreateDefaultSubobject<UProjectileMovementComponent>("RocketMovement");
	RocketMovement->SetUpdatedComponent(RocketMesh);*/
}

void ABallisticMissle::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABallisticMissle::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Sphere->OnComponentHit.AddDynamic(this, &ABallisticMissle::OnGroundHit);
}

void ABallisticMissle::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Sphere->OnComponentHit.RemoveDynamic(this, &ABallisticMissle::OnGroundHit);

	Super::EndPlay(EndPlayReason);
}

void ABallisticMissle::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FRotator NewRotation;
	auto Vel = Sphere->GetPhysicsLinearVelocity();
	UKismetMathLibrary::Vector_Normalize(Vel);
	/*NewRotation.Pitch = FMath::ClampAngle( ,0.f,90.f);*/
	SetActorRotation(Vel.Rotation());
}

void ABallisticMissle::OnGroundHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	//play explosion effect
	Destroy();
}

