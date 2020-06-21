// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankAimingComponent.h"

UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::Initialize(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	// Force the first fire to wait reload time.
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	// FiringStatus management:
	// FPlatform time feels like its hardware hard coded or some shit, cant cheat it.
	if (!((FPlatformTime::Seconds() - LastFireTime) > ReloadTime))
	{
		FiringStatus = EFiringStatus::Reloading;
	}
	else
	{
		if (IsBarrelMoving())
		{
			FiringStatus = EFiringStatus::Aiming;
		}
		else
		{
			FiringStatus = EFiringStatus::Locked;
		}
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if(ensure(Barrel))
	{
		return ! AimDirection.Equals(Barrel->GetForwardVector(), 0.01f);
	}
	return false;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (ensure(Barrel && Turret))
	{
		LaunchProjectile(HitLocation);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Barrel or Turret set for %s, soft code it with our function BP !"), *GetOwner()->GetName());
	}
}

void UTankAimingComponent::Fire()
{
	if (ensure(Barrel && ProjectileBlueprint))
	{
		if (FiringStatus != EFiringStatus::Reloading)
		{
			auto LocationToSpawn = Barrel->GetSocketLocation(FName("Projectile"));
			auto RotationToSpawn = Barrel->GetSocketRotation(FName("Projectile"));
			auto ProjectileInstance = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, LocationToSpawn, RotationToSpawn);

			ProjectileInstance->LaunchProjectile(LaunchSpeed);
			LastFireTime = FPlatformTime::Seconds();
		}
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
	if (!ensure(Barrel && Turret)){return;}

	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace);
	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		//UE_LOG(LogTemp, Warning, TEXT("%f: UTankAimingComponent::LaunchProjectile ===> Aim solution Found !"), GetWorld()->GetTimeSeconds());
		MoveBarrelToward(AimDirection);
		MoveTurretToward(AimDirection);
	}
	else
	{
		// UE_LOG(LogTemp, Warning, TEXT("%s ======> NO AIM SOLUTION"), *GetOwner()->GetName());
		//UE_LOG(LogTemp, Warning, TEXT("%f: UTankAimingComponent::LaunchProjectile ===> NO Aim solution !"), GetWorld()->GetTimeSeconds());
	}
}

void UTankAimingComponent::MoveBarrelToward(FVector AimDirectionLocal)
{
	if (!ensure(Barrel)){return;}

	// Work out difference between current barrel rotation and aim direction,
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirectionLocal.Rotation();
	// UE_LOG(LogTemp, Warning, TEXT("Barrel BarrelRotator (fw v.): %s"), *BarrelRotator.ToString());
	// UE_LOG(LogTemp, Warning, TEXT("Barrel AimAsRotator: %s"), *AimAsRotator.ToString());
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	// UE_LOG(LogTemp, Warning, TEXT("Barrel DeltaRotator: %s"), *DeltaRotator.ToString());
	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurretToward(FVector AimDirectionLocal)
{
	if (!ensure(Turret)){return;}
	// Work out difference between current turret rotation and aim direction,
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirectionLocal.Rotation();
	//UE_LOG(LogTemp, Warning, TEXT("Turret TurretRotator (fw v.): %s"), *TurretRotator.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("Turret AimAsRotator: %s"), *AimAsRotator.ToString());
	auto DeltaRotator = AimAsRotator - TurretRotator;
	float AngleToGo = DeltaRotator.Yaw;
	//UE_LOG(LogTemp, Warning, TEXT("%f: DeltaYAW between Turret and Aim direction: %f"),GetWorld()->GetTimeSeconds(), AngleToGo);
	if(AngleToGo > 180.f )
	{
		AngleToGo = -AngleToGo; // Take the other way around
	}
	Turret->MutateAzimuth(AngleToGo);
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