// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    //UE_LOG(LogTemp, Warning, TEXT("In ATankAIController::BeginPlay"));
    
    // auto ControlledTank = GetControlledTank();
    // if (!ControlledTank)
    // {
    //     UE_LOG(LogTemp, Error, TEXT("AI Controller not possessing a tank..."));
    // }
    // else
    // {
    //     UE_LOG(LogTemp, Warning, TEXT("Tank Controlled by AI ?: %s"), *ControlledTank->GetName());
    // }    
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    //UE_LOG(LogTemp, Warning, TEXT("Ticking AI"));

    auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    if (PlayerTank)
    {
        //UE_LOG(LogTemp, Warning, TEXT("Player pawn found : %s"), *PlayerTank->GetName());
        
        auto ControlledTank = Cast<ATank>(GetPawn());
        if (ControlledTank)
        {
            ControlledTank->AimAt(PlayerTank->GetActorLocation());
            ControlledTank->Fire();
            MoveToActor(PlayerTank, AcceptanceRadius);
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("PlayerController Pawn not found..."));
    }
}