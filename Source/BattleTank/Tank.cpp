// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "GameFramework/Actor.h"
#include "TankBarrel.h"
#include "Projectile.h"
//#include "Engine/World.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;	
	// Old:
	// TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	// Actuallly, add it manually in Components List! 
	// TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation);
}

void ATank::Initialize(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void ATank::Fire()
{
	// FPlatform time feels like its hardware hard coded or some shit, cant cheat it.
	auto bHasReloaded = ( FPlatformTime::Seconds() - LastFireTime ) > ReloadTime;
	if(Barrel && bHasReloaded)
	{
		// UE_LOG(LogTemp, Warning, TEXT("FIRING!!"));

		auto LocationToSpawn = Barrel->GetSocketLocation(FName("Projectile"));
		auto RotationToSpawn = Barrel->GetSocketRotation(FName("Projectile"));
		auto ProjectileInstance = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, LocationToSpawn, RotationToSpawn);

		ProjectileInstance->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}

}