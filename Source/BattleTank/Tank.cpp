// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "GameFramework/Actor.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Tank.h"

ATank::ATank()
{
	// UE_LOG(LogTemp, Warning, TEXT("brobro: %s : TANK Ctor"), *GetName());
	PrimaryActorTick.bCanEverTick = false;
	// Old:
	// TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	// Actuallly, add it manually in Components List! And accesed by the FindComponentByClass method
	// TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
}

void ATank::BeginPlay()
{
	// UE_LOG(LogTemp, Warning, TEXT("brobro: %s : TANK BeginPlay"), *GetName());
	Super::BeginPlay(); // Very much needed for the Tank BP to launch its own BeginPlay in Eventgraph !!!!
}

void ATank::Initialize(UTankBarrel *BarrelToSet)
{
	Barrel = BarrelToSet;
}

void ATank::Fire()
{
	// FPlatform time feels like its hardware hard coded or some shit, cant cheat it.
	auto bHasReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTime;
	if (ensure(Barrel) && bHasReloaded)
	{
		// UE_LOG(LogTemp, Warning, TEXT("FIRING!!"));

		auto LocationToSpawn = Barrel->GetSocketLocation(FName("Projectile"));
		auto RotationToSpawn = Barrel->GetSocketRotation(FName("Projectile"));
		auto ProjectileInstance = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, LocationToSpawn, RotationToSpawn);

		ProjectileInstance->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}