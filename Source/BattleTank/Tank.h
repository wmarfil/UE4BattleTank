// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	ATank();

protected:
	// Note: No more references to aiming component, is accessed through FIndComonentByClass by other

private:
	virtual void BeginPlay() override;
};
