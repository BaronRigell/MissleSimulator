// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "BallisticMissle.generated.h"

UCLASS()
class MISSLESIMULATOR_API ABallisticMissle : public AActor
{
	GENERATED_BODY()
	
public:	
	ABallisticMissle();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USkeletalMeshComponent* RocketMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UProjectileMovementComponent* RocketMovement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USphereComponent* Sphere;
	
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	virtual void Tick(float DeltaSeconds) override;
public:	
	USkeletalMeshComponent* GetMesh() const { return RocketMesh;}
	USphereComponent* GetSphere() const {return Sphere;}
private:
	UFUNCTION()
	void OnGroundHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
