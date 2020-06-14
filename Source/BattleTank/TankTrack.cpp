// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
    // TODO
    auto Name = GetName();
    UE_LOG(LogTemp, Warning, TEXT("Throttle set to %f for %s"), Throttle, *Name);
}