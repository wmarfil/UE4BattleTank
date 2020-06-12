// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTankPlayerController.h"


void ABaseTankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("In ABaseTankPlayerController::BeginPlay"));
    auto ControlledTank = GetControlledTank();
    if (!ControlledTank)
    {
        UE_LOG(LogTemp, Error, TEXT("Player Controller not possessing a tank..."));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Tank Controlled by player?: %s"), *ControlledTank->GetName());
    }
}

void ABaseTankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    //UE_LOG(LogTemp, Warning, TEXT("Ticking PLAYER"));
}

ATank* ABaseTankPlayerController::GetControlledTank() const
{
    UE_LOG(LogTemp, Warning, TEXT("In ABaseTankPlayerController::GetControlledTank"));
    return Cast<ATank>(GetPawn());

}

