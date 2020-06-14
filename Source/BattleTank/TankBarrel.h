// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * Note that once you should compile then create new component extended from this C++ class to not have unpredictable shit going on like
 * static mesh of the extended BP clearing itself, the BP resetting and stuff and random crash probably. 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegreesPerSecondes = 5.f;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxElevation = 40.f;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MinElevation = 0.f;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	bool bPreventSelfCollision = true;
};
