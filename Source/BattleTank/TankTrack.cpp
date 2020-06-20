// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
    // Trying to do the equivalent as Adding on Hit event in blueprint.
    Super::BeginPlay();
    // AddDynamic is a MACRO: just ignore squiggle.
    OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
    UE_LOG(LogTemp, Warning, TEXT("HITTING THE TRACK AINT YA"));
}

// Cancel Sideway force
void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    // Note here that we dont call Super::TickComponent, because our blueprint doesnt need it. (basicly this would allow the BP to call its own tick event in graph section)

	// Calculate the slippage speed 
    // Work out the required acceleration this frame to correct 
    // Apply sideway force to counteract our undesired sidewaz force
    
    // On doit voir A quel point le right vector est colinéaire avec le vecteur vitesse => grâce au cosinus 1 = ils sont colinéaires, 0 = orthogonaux
    // Le produit scalaire nous renvoyant un float, il s'agit implicitement d'une vitesse (m/s). Mais en fair c'ets cm/s car Unreal unit. (de par GetComponentVelocity)
    auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

    // What is the required acceleration this frame to correct ?
    auto CorrectionAccel  = -SlippageSpeed / DeltaTime * GetRightVector();

    // Cast to StaticMeshComp to get the mass of the tank.
    auto TankRootComp =  Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    // Calculate and apply sideways (F = ma)
    // Our tank is 40t => we need F = 40t * CorrectionAccel
    auto CorrectionForce = (TankRootComp->GetMass() * CorrectionAccel) / 2 ;
    TankRootComp->AddForce(CorrectionForce);

}

void UTankTrack::SetThrottle(float Throttle)
{
    auto Name = GetName();
    // UE_LOG(LogTemp, Warning, TEXT("Throttle set to %f for %s"), Throttle, *Name);

    // TODO: Clamp up throttle to not allow player to over drive. Multiplied by 100 since we got Newtons/100
    auto ForceApplied = GetForwardVector() * TrackMaxDrivingForce*100 * Throttle;
    auto ForceLocation = GetComponentLocation();
    auto RootComp =  Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    RootComp->AddForceAtLocation(ForceApplied, ForceLocation);
}