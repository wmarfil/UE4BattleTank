// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "Tank.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrack, UTankTrack* RightTrack)
{
    // UE_LOG(LogTemp, Warning, TEXT(" Initialize Tank Movement Component"));
    if(!LeftTrack || !RightTrack){ UE_LOG(LogTemp, Error, TEXT("Initialize: No tracks for movement component..."));return;}
    TrackLeft = LeftTrack;
    TrackRight = RightTrack;
}

void UTankMovementComponent::IntendMoveFoward(float Throw)
{
    // TODO: Prevent double input = double the speed (scale).
    // UE_LOG(LogTemp, Warning, TEXT(" Intend to Move forward!"));
    if(!TrackLeft || !TrackRight){ UE_LOG(LogTemp, Error, TEXT("Intend move forward: No tracks for movement component..."));return;}
    TrackLeft->SetThrottle(Throw);
    TrackRight->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
    // UE_LOG(LogTemp, Warning, TEXT(" Intend to Move right!"));
    if(!TrackLeft || !TrackRight){ UE_LOG(LogTemp, Error, TEXT("Intend turn right: No tracks for movement component..."));return;}
    TrackLeft->SetThrottle(Throw);
    TrackRight->SetThrottle(-Throw);
}

// Used by the AI.
void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
    // No need to call Super.
    auto Tank = GetOwner();
    auto ForwardVectorUnit = Tank->GetActorForwardVector().GetSafeNormal();
    auto MoveVelocityUnit = MoveVelocity.GetSafeNormal();
    auto DotProduct = FVector::DotProduct(ForwardVectorUnit, MoveVelocityUnit);
    UE_LOG(LogTemp, Warning, TEXT("%s vectoring to %s with forward vector of %s ===> dot product is %f"), 
        *Tank->GetName(),
        *MoveVelocityUnit.ToString(),
        *ForwardVectorUnit.ToString(),
        DotProduct 
    );
    
    // if(DotProduct < 0.9f){
    //     IntendTurnRight(DotProduct);
    // }else{
        IntendMoveFoward(DotProduct);
    // }
}


