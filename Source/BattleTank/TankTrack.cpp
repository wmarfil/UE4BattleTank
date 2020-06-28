// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"
#include "SpawnPoint.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
    // Trying to do the equivalent as Adding on Hit event in blueprint.
    Super::BeginPlay();
    
    // OLD:
    // AddDynamic is a MACRO: just ignore squiggle.
    // OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

// OLD:
// void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
// {
//     // UE_LOG(LogTemp, Warning, TEXT("HITTING THE TRACK AINT YA"));
//     DriveTrack();
//     CancelSidewayForces();
//     CurrentThrottle = 0;
// }

void UTankTrack::SetThrottle(float Throttle)
{
    // OLD:
    // Clamping manage the multiple input a time glitch that makes you faster and other things like right and forward at the right time
    // CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle , -1, 1);

    // UE_LOG(LogTemp, Warning, TEXT("Setting throttle!!! %f"), Throttle);
    auto ThrottleToApply = FMath::Clamp<float>(Throttle , -1, 1);
    DriveTrack(ThrottleToApply);
}

// OLD: Our old way without using wheels and physic constraints.
// void UTankTrack::CancelSidewayForces()
// {
//     // Calculate the slippage speed 
//     // Work out the required acceleration this frame to correct 
//     // Apply sideway force to counteract our undesired sidewaz force
    
//     // On doit voir A quel point le right vector est colinéaire avec le vecteur vitesse => grâce au cosinus 1 = ils sont colinéaires, 0 = orthogonaux
//     // Le produit scalaire nous renvoyant un float, il s'agit implicitement d'une vitesse (m/s). Mais en fair c'ets cm/s car Unreal unit. (de par GetComponentVelocity)
//     auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

//     // What is the required acceleration this frame to correct ?
//     auto CorrectionAccel  = -SlippageSpeed / GetWorld()->GetDeltaSeconds() * GetRightVector();

//     // Cast to StaticMeshComp to get the mass of the tank.
//     auto TankRootComp =  Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
//     // Calculate and apply sideways (F = ma)
//     // Our tank is 40t => we need F = 40t * CorrectionAccel
//     auto CorrectionForce = (TankRootComp->GetMass() * CorrectionAccel) / 2 ;
//     TankRootComp->AddForce(CorrectionForce);
// }

// Called when track hit the ground.
void UTankTrack::DriveTrack(float ThrottleToApply)
{
    // -------------------OLD: (before our wheels we were merely applying a force into the track)
    // auto Name = GetName();
    // // UE_LOG(LogTemp, Warning, TEXT("Throttle set to %f for %s"), Throttle, *Name);

    // // TODO: Multiplied by 100 since we got Newtons/100
    // auto ForceApplied = GetForwardVector() * TrackMaxDrivingForce*100 * CurrentThrottle;
    // auto ForceLocation = GetComponentLocation();
    // auto RootComp =  Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    // RootComp->AddForceAtLocation(ForceApplied, ForceLocation);


    auto ForceApplied = TrackMaxDrivingForce*100 * ThrottleToApply;
    auto Wheels = GetWheels();
    auto ForceAppliedPerWheels = ForceApplied / Wheels.Num();
    for (auto Wheel : Wheels)
    {
        Wheel->AddDrivingForce(ForceAppliedPerWheels);
    }
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
    TArray<ASprungWheel*> FinalRes;
    TArray<USceneComponent*> SceneComponents;
    GetChildrenComponents(true, SceneComponents);
    for(auto SceneComp : SceneComponents)
    {
        auto SpawnPoint = Cast<USpawnPoint>(SceneComp);
        if(!SpawnPoint) continue;
        
        auto Actor = SpawnPoint->GetSpawnedActor();
        if(!Actor) continue;

        auto SprungWheel = Cast<ASprungWheel>(Actor);
        if(!SprungWheel) continue;
        
        FinalRes.Add(SprungWheel);
        // UE_LOG(LogTemp, Warning, TEXT("Impec"));
    }

    return FinalRes;
}

