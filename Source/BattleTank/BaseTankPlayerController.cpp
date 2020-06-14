// Fill out your copyright notice in the Description page of Project Settings.

#include "Math/UnrealMathUtility.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Pawn.h"
#include "Tank.h"
#include "BaseTankPlayerController.h"


void ABaseTankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    //UE_LOG(LogTemp, Warning, TEXT("In ABaseTankPlayerController::BeginPlay"));
    auto ControlledTank = GetControlledTank();
    if (!ControlledTank)
    {
        UE_LOG(LogTemp, Error, TEXT("Player Controller not possessing a tank..."));
    }
    else
    {
        //UE_LOG(LogTemp, Warning, TEXT("Tank Controlled by player?: %s"), *ControlledTank->GetName());
    }
}

void ABaseTankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    AimTowardCrosshair();
    //UE_LOG(LogTemp, Warning, TEXT("Ticking PLAYER"));
}

ATank* ABaseTankPlayerController::GetControlledTank() const
{
    //UE_LOG(LogTemp, Warning, TEXT("In ABaseTankPlayerController::GetControlledTank"));
    return Cast<ATank>(GetPawn());
}

void ABaseTankPlayerController::AimTowardCrosshair()
{
    //UE_LOG(LogTemp, Warning, TEXT("In ABaseTankPlayerController::AimTowardCrosshair"));
    FVector OutHitLocation; // Out P.
    if(GetSightRayHitLocation(OutHitLocation))
    {
        //UE_LOG(LogTemp, Warning, TEXT("    Look Location: %s"), *OutHitLocation.ToString());
        auto ControlledTank = GetControlledTank();
        if (ControlledTank)
        {
            ControlledTank->AimAt(OutHitLocation);
        }
    }
}

// Get world location of linetrace through crosshair
bool ABaseTankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
    OutHitLocation = FVector(1.f, 2.f ,3.f);
    // Find the crosshair position. Do not make it dependant to the UI dot, it doesnt change very often therefore we can re decide where it is here.
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
    //UE_LOG(LogTemp, Warning, TEXT("viewport x: %d, viewport y: %d, vector2d result: %s"),ViewportSizeX, ViewportSizeY, *ScreenLocation.ToString());

    // "deproject" the screen position of the crosshair to a world position
    FVector OutLookDirection; 
    if (GetLookDirection(ScreenLocation, OutLookDirection))
    {
        // UE_LOG(LogTemp, Warning, TEXT("Deprojection on landscape direction result: %s"), *OutLookDirection.ToString());
        // Line-trace along (Raycast) that look direction (set a max range)
        bool res = GetLookVectorHitLocation(OutLookDirection, OutHitLocation);
        //UE_LOG(LogTemp, Warning, TEXT("Raycast HitLocation : %s"), *HitLocation.ToString());
        return res;
    }

    return false;
}

bool ABaseTankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& OutLookDirection) const
{
    FVector OutCameraHitLocation;

    return DeprojectScreenPositionToWorld(
        ScreenLocation.X,
        ScreenLocation.Y,
        OutCameraHitLocation,
        OutLookDirection
    );
}

// The intereting part !
bool ABaseTankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector &HitLocation) const
{
    FHitResult HitResult;
    
    FVector Start = PlayerCameraManager->GetCameraLocation();
    FVector End = Start + (LookDirection * LineTraceRange);
    
    // No need for now, using default values.
    // FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
    // FCollisionResponseParams CollisionResponseParams;

    // DrawDebugLine(
	// 	GetWorld(),
	// 	Start,
	// 	End,
	// 	FColor(255, 0, 0),
	// 	false,
	// 	0.f,
	// 	0,
	// 	5.f
	// );

    if(GetWorld()->LineTraceSingleByChannel(
            HitResult,
            Start,
            End,
            ECollisionChannel::ECC_Visibility
        )
    )
    {
        HitLocation = HitResult.Location;
        return true;
    }
    else
    {
        HitLocation = FVector(0);
        return false;
    }
}

