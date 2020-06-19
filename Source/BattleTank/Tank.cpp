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
	// UE_LOG(LogTemp, Warning, TEXT("brobro: %s : TANK Ctor"), *GetName());
	PrimaryActorTick.bCanEverTick = false;	
	// Old:
	// TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	// Actuallly, add it manually in Components List! 
	// TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	// UE_LOG(LogTemp, Warning, TEXT("brobro: %s : TANK BeginPlay"), *GetName());
	Super::BeginPlay(); // Very much needed for the Tank BP to launch its own BeginPlay in Eventgraph !!!! 
}

void ATank::AimAt(FVector HitLocation)
{
	// ensure is an assertion which display special log for us when ptr is NULL. Handy.
	if(!ensure(TankAimingComponent)) {UE_LOG(LogTemp, Error, TEXT("OOOOH"));return;}
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
	if(ensure(Barrel) && bHasReloaded)
	{
		// UE_LOG(LogTemp, Warning, TEXT("FIRING!!"));

		auto LocationToSpawn = Barrel->GetSocketLocation(FName("Projectile"));
		auto RotationToSpawn = Barrel->GetSocketRotation(FName("Projectile"));
		auto ProjectileInstance = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, LocationToSpawn, RotationToSpawn);

		ProjectileInstance->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}

}