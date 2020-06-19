// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "Tank.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrack, UTankTrack* RightTrack)
{
    // UE_LOG(LogTemp, Warning, TEXT(" Initialize Tank Movement Component"));
    TrackLeft = LeftTrack;
    TrackRight = RightTrack;
}

void UTankMovementComponent::IntendMoveFoward(float Throw)
{
    // TODO: Prevent double input = double the speed (scale).
    // UE_LOG(LogTemp, Warning, TEXT(" Intend to Move forward!"));
    if(!ensure(TrackLeft && TrackRight)){ return;}
    TrackLeft->SetThrottle(Throw);
    TrackRight->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
    // UE_LOG(LogTemp, Warning, TEXT(" Intend to Move right!"));
    if(!ensure(TrackLeft && TrackRight)){ return;}
    TrackLeft->SetThrottle(Throw);
    TrackRight->SetThrottle(-Throw);
}

// Called by the pathfinding (engine logic) when ATankAIController::MoveToActor() is called
void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
    // No need to call Super.
    auto Tank = GetOwner();
    auto ForwardVectorUnit = Tank->GetActorForwardVector().GetSafeNormal();
    auto MoveVelocityUnit = MoveVelocity.GetSafeNormal();
    
    auto DotProduct = FVector::DotProduct(ForwardVectorUnit, MoveVelocityUnit);  
    IntendMoveFoward(DotProduct);

    auto CrossProduct = FVector::CrossProduct(ForwardVectorUnit, MoveVelocityUnit);  
    IntendTurnRight(CrossProduct.Z);


    // UE_LOG(LogTemp, Warning, TEXT("%s vectoring to %s with forward vector of %s ===> DOT product is %f, CROSS Product Z: %f"), 
    //     *Tank->GetName(),
    //     *MoveVelocityUnit.ToString(),
    //     *ForwardVectorUnit.ToString(),
    //     DotProduct,
    //     CrossProduct.Z    
    // );
}


