// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
    auto Name = GetName();
    UE_LOG(LogTemp, Warning, TEXT("Throttle set to %f for %s"), Throttle, *Name);

    // TODO: Clamp up throttle to not allow player to over drive. Multiplied by 100 since we got Newtons/100
    auto ForceApplied = GetForwardVector() * TrackMaxDrivingForce*100 * Throttle;
    auto ForceLocation = GetComponentLocation();
    auto RootComp =  Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    RootComp->AddForceAtLocation(ForceApplied, ForceLocation);
}