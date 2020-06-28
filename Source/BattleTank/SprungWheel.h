// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class UPhysicsConstraintComponent;
class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	ASprungWheel();
	virtual void Tick(float DeltaTime) override;

	void AddDrivingForce(float ForceMagnitude);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Setup")
	USphereComponent* AxleMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Setup")
	USphereComponent* WheelMesh = nullptr;

	// TODO: Rename to clarify its our spring.
	UPROPERTY(EditAnywhere, Category = "Setup")
	UPhysicsConstraintComponent* SpringConstraint = nullptr;

	UPROPERTY(EditAnywhere, Category = "Setup")
	UPhysicsConstraintComponent* AxleWheelConstraint = nullptr;

	// NEVER EVER FORGET the UFUNCTIOn when creating a function for multicast delegate to call. + private as well !!
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void ApplyForce();

	float TotalForceMagnitudeThisFrame = 0.f;

	//SprungWheel_BP

};
