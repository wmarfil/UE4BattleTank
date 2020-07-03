// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
	Locked,
	Aiming,
	Reloading,
	OutOfAmmo
};

// Forward Declaration !
class UTankBarrel;
class UTankTurret;
class AProjectile;

// Holds barrel's properties and Elevate method.(this is a tooltip test)
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Firing") // TODO: maybe protected actually is better
	void Fire();

	void AimAt(FVector HitLocation);
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet);

	EFiringStatus GetFiringStatus() const;
	UFUNCTION(BlueprintCallable, Category = "Setup")
	int32 GetAmmoCount() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	EFiringStatus FiringStatus = EFiringStatus::Aiming;

private:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime,enum ELevelTick TickType,FActorComponentTickFunction * ThisTickFunction) override;
	void MoveBarrelToward(FVector AimDirectionLocal);
	void MoveTurretToward(FVector AimDirectionLocal);
	bool IsBarrelMoving();

	UTankBarrel *Barrel = nullptr;
	UTankTurret *Turret = nullptr;

	// EditDefaultsOnly doesnt let instance modify occur, only through BP!
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTime = 3.f;
	double LastFireTime = 0;
	FVector AimDirection;

	// If we just pust UClass* insead of TSubClass we would have a too big class list in BP UI.
	UPROPERTY(EditAnywhere, Category = "Firing")
	TSubclassOf<AProjectile> ProjectileBlueprint; // Doc: https://docs.unrealengine.com/en-US/Programming/UnrealArchitecture/TSubclassOf/index.html
	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 4000.f;
	//float LaunchSpeed = 10000.f; // 1000 m/s A CONFIRMER

	UPROPERTY(EditAnywhere, Category = "Firing")
	int32 AmmoCount = 20;
};
