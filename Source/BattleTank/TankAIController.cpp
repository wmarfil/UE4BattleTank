// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h" // findcomponentnbyclass
#include "GameFramework/Pawn.h" // for detach pawn
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);
    if(InPawn)
    {
        auto PossessedTank = Cast<ATank>(InPawn);
        if(!ensure(PossessedTank)){return;}
        PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
    }
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    auto ControlledTank = Cast<ATank>(GetPawn());
    if (PlayerTank && ControlledTank)
    {
        auto AimingComp = ControlledTank->FindComponentByClass<UTankAimingComponent>();
        if (AimingComp)
        {
            AimingComp->AimAt(PlayerTank->GetActorLocation());
            if(AimingComp->GetFiringStatus() == EFiringStatus::Locked)
            {
                AimingComp->Fire();
            }
        }
        MoveToActor(PlayerTank, AcceptanceRadius);
    }
    else
    {
        // UE_LOG(LogTemp, Warning, TEXT("PlayerController Pawn not found..."));
    }
}

void ATankAIController::OnTankDeath()
{
    UE_LOG(LogTemp, Warning, TEXT("AIController receives tank died !"));
    GetPawn()->DetachFromControllerPendingDestroy();
}