// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	ATank();
	// Called by the engine when the damage is dealt to this instance of tank class.
	float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
	UFUNCTION(BlueprintPure, Category = "Stats")
	float GetCurrentHealth() const;

	FTankDelegate OnDeath;

protected:
	// Note: No more references to aiming component, is accessed through FIndComonentByClass by other

private:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 80;
	UPROPERTY(VisibleAnywhere, Category = "Stats")
	int32 CurrentHealth;
};
