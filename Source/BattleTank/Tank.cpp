// Fill out your copyright notice in the Description page of Project Settings.

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
	CurrentHealth = StartingHealth;
}

float ATank::GetCurrentHealth() const
{
	return (float)CurrentHealth / (float) StartingHealth;
}

float ATank::TakeDamage
(
    float DamageAmount,
    struct FDamageEvent const & DamageEvent,
    class AController * EventInstigator,
    AActor * DamageCauser
)
{
	//UE_LOG(LogTemp, Warning, TEXT("Damage amount: %f "), DamageAmount);
	if(DamageCauser)
	{
		//UE_LOG(LogTemp, Warning, TEXT("DamageCauser(actor): %s"), DamageAmount, *DamageCauser->GetName());
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("NULL reference Damage causer!"));
	}

	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	auto DamageToApply = FMath::Clamp<int32>(DamagePoints, 0, CurrentHealth);
	//UE_LOG(LogTemp, Warning, TEXT("DamageToApply: %d "), DamageToApply);
	CurrentHealth -= DamageToApply;
	if(CurrentHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("DEAD"));
		OnDeath.Broadcast();
	}
	return DamageToApply;
}