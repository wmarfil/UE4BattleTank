// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetBarrelReference(Barrel);
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	auto OurTankName = GetOwner()->GetName();
	if(Barrel)
	{
		auto BarrelLocation = Barrel->GetComponentLocation();
		// UE_LOG(LogTemp, Warning, TEXT("AIMING AT  %s --> %s ,      from %s"), *OurTankName, *HitLocation.ToString(), *BarrelLocation.ToString());
		FVector AimDirection;
		LaunchProjectile(HitLocation, AimDirection);
		
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Barrel set for %s, soft code it with our function BP !"), *OurTankName);
	}
	
}

void UTankAimingComponent::LaunchProjectile(FVector HitLocation, FVector& OutAimDirection)
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
	auto ProjectileLaunchSpeed = Cast<ATank>(GetOwner())->LaunchSpeed;
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		ProjectileLaunchSpeed,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if(bHaveAimSolution)
	{
		OutAimDirection = OutLaunchVelocity.GetSafeNormal();
		// UE_LOG(LogTemp, Warning, TEXT("%s ======> Aim Direction out of solution  %s"), *GetOwner()->GetName() , *AimDirection.ToString());
		MoveBarrelToward(OutAimDirection);
	}
	else
	{
		// UE_LOG(LogTemp, Warning, TEXT("%s ======> NO AIM SOLUTION"), *GetOwner()->GetName());
	}
}

void UTankAimingComponent::MoveBarrelToward(FVector AimDirection)
{
	// work out difference between current barrel rotation and aim direction, 
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *AimAsRotator.ToString());
	// Remove hard coded.
	Barrel->Elevate(5);
	// Move the barrel the rigt amount this frame
	
	// Given a max elevation speed and the frame time.


}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}






// was in movebarreltoward method:

// DrawDebugLine(
	// 	GetWorld(),
	// 	Barrel->GetSocketLocation(FName("Projectile")),
	// 	Barrel->GetSocketLocation(FName("Projectile")) + AimAsRotator.Vector() * 1000,
	// 	FColor(0, 200, 0),
	// 	false,
	// 	0.f,
	// 	0,
	// 	15.f
	// );

	// DrawDebugLine(
	// 	GetWorld(),
	// 	Barrel->GetComponentLocation(),
	// 	Barrel->GetComponentLocation() + Barrel->GetForwardVector() * 1000 ,
	// 	FColor(180, 0, 0),
	// 	false,
	// 	0.f,
	// 	0,
	// 	15.f
	// );