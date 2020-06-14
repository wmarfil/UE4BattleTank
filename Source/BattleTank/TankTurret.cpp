// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::MutateAzimuth(float RelativeSpeed)
{
    // Move the turret the right amount this frame
    // Given a max elevation speed, and the frame time
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
    auto AzimuthChange = RelativeSpeed * MaxDegreesPerSecondes * GetWorld()->GetDeltaSeconds();
    auto AzimuthRaw = GetRelativeRotation().Yaw + AzimuthChange;
    SetRelativeRotation(FRotator(0, AzimuthRaw, 0));
}