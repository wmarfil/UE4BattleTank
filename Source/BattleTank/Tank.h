// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;
class UTankAimingComponent;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetBarrelReference(UTankBarrel* BarrelToSet);
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetTurretReference(UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 4000.f;
	//float LaunchSpeed = 10000.f; // 1000 m/s A CONFIRMER

protected:
	// TIP: Forward declare the properties/ function of the header file, and include them in the cpp file.
	UTankAimingComponent* TankAimingComponent = nullptr;
	// Useless now that we make it manually addable in the component list rather than hard coded in the constructor of Tank like TankAimingComponent.
	// UPROPERTY(BlueprintReadOnly, Category = "Setup")
	// UTankMovementComponent* TankMovementComponent = nullptr;

private:	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere, Category = "Firing")
	TSubclassOf<AProjectile> ProjectileBlueprint; // Doc: https://docs.unrealengine.com/en-US/Programming/UnrealArchitecture/TSubclassOf/index.html
	// If we just pust UClass* insead of TSubClass we would have a too big class list in BP UI.

	UTankBarrel* Barrel = nullptr;

	// EditDefaultsOnly doesnt let instance modify occur, only through BP!
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTime = 3.f;

	double LastFireTime = 0;
};
