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
}