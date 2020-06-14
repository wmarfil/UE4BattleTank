// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float DegreePerSeconds)
{
    // Move the barrel the right amount this frame
    // Given a max elevation speed, and the frame time
    UE_LOG(LogTemp, Warning, TEXT("In UTankBarrel::Elevate at speed %f degree per sed"), DegreePerSeconds);
}