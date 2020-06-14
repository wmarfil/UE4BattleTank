// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
    // Move the barrel the right amount this frame
    // Given a max elevation speed, and the frame time
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
    auto ElevationChange = RelativeSpeed * MaxDegreesPerSecondes * GetWorld()->GetDeltaSeconds();
    auto ElevationRaw =  GetRelativeRotation().Pitch + ElevationChange;
    SetRelativeRotation(FRotator(FMath::Clamp<float>(ElevationRaw, MinElevation, MaxElevation), 0, 0));
}