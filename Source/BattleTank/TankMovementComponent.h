// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

// NOTE: To compare this to the AimingCOmponent, since we started coding it the same way, we will now get the references of the tank component (tracks here) 
// directly by the a method Initialize.

class UTankTrack;

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankTrack* LeftTrack, UTankTrack* RightTrack);
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveFoward(float Throw);
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendTurnRight(float Throw);
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;


private:
	UTankTrack* TrackRight = nullptr;
	UTankTrack* TrackLeft = nullptr;
};
