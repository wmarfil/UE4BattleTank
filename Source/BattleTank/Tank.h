// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel *BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 4000.f;
	//float LaunchSpeed = 10000.f; // 1000 m/s A CONFIRMER

protected:
	// Note: No more references to aiming component, is accessed through FIndComonentByClass by other

private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Firing")
	TSubclassOf<AProjectile> ProjectileBlueprint; // Doc: https://docs.unrealengine.com/en-US/Programming/UnrealArchitecture/TSubclassOf/index.html
	// If we just pust UClass* insead of TSubClass we would have a too big class list in BP UI.

	UTankBarrel *Barrel = nullptr;

	// EditDefaultsOnly doesnt let instance modify occur, only through BP!
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTime = 3.f;

	double LastFireTime = 0;
};
