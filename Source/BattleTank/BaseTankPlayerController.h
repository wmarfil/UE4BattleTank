// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "BaseTankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ABaseTankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	ATank* GetControlledTank() const;

};
