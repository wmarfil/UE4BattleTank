// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetBarrelReference(Barrel);
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	auto OurTankName = GetOwner()->GetName();
	if(Barrel)
	{
		auto BarrelLocation = Barrel->GetComponentLocation();
		// UE_LOG(LogTemp, Warning, TEXT("AIMING AT  %s --> %s ,      from %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation.ToString());
		LaunchProjectile(HitLocation);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Barrel set for %s, soft code it with our function BP !"), *OurTankName);
	}
	
}

void UTankAimingComponent::LaunchProjectile(FVector HitLocation)
{
	// Params:
	// 1: Getworld I guess
	// 2: TossVelocity is actually the direction vector... the lenght will be the speed
	// 3: 

	// SuggestProjectileVelocity
	// (
	// 	const UObject * WorldContextObject,
	// 	FVector & TossVelocity,
	// 	FVector StartLocation,
	// 	FVector EndLocation,
	// 	float TossSpeed,
	// 	bool bHighArc,
	// 	float CollisionRadius,
	// 	float OverrideGravityZ,
	// 	ESuggestProjVelocityTraceOption::Type TraceOption,
	// 	const FCollisionResponseParams & ResponseParam,
	// 	const TArray < AActor * > & ActorsToIgnore,
	// 	bool bDrawDebug
	// )
	if(!Barrel){return;}

	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		Cast<ATank>(GetOwner())->LaunchSpeed,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if(bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("%s ======> aiming at  %s"), *GetOwner()->GetName() , *AimDirection.ToString());
	}
}

void UTankAimingComponent::MoveBarrelToward(FVector AimDirection)
{
	// work out difference between current barrel rotation and aim direction, 
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), AimAsRotator.ToString());


	// move the barrel the rigt amount this frame
	// given a max elevation speed and the frame time.
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet)
{
	Barrel = BarrelToSet;
}

