// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Apply forces to a tank to move it.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UTankTrack();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetThrottle(float Throttle);
	
	// Max force per track, In Newton  => 1g acceleration for 40tons tank. Note that we will have to multiply by 100 when using it since its N for cm instead of m.
	UPROPERTY(EditDefaultsOnly, Category = "Driving")
	float TrackMaxDrivingForce = 400000.f;

private:
	virtual void TickComponent(float DeltaTime,enum ELevelTick TickType,FActorComponentTickFunction * ThisTickFunction) override;

};
