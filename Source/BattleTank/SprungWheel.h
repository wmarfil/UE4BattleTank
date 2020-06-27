// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SprungWheel.generated.h"

class UPhysicsConstraintComponent;
class UStaticMeshComponent;

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	ASprungWheel();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Setup")
	UStaticMeshComponent* SupportMesh = nullptr;
	UPROPERTY(EditAnywhere, Category = "Setup")
	UStaticMeshComponent* WheelMesh = nullptr;
	UPROPERTY(EditAnywhere, Category = "Setup")
	UPhysicsConstraintComponent* PhysicsConstraintComp = nullptr;

};
