// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "SprungWheel.h"

ASprungWheel::ASprungWheel()
{
	PrimaryActorTick.bCanEverTick = true;
	// BEWARE: These FName are the real name for the Physic Component to attach the components to in the BP editing!!!
	SupportMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Support Mesh Comp"));
	SetRootComponent(SupportMesh);
	WheelMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel Mesh Comp"));
	WheelMesh->SetupAttachment(RootComponent);
	PhysicsConstraintComp = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Physics Constraint Comp"));
	PhysicsConstraintComp->SetupAttachment(RootComponent);
	// Setup Physic COnstraint

	// PhysicsConstraintComp->SetConstrainedComponents(SupportMesh, WheelMesh);
	// PhysicsConstraintComp->execSetLinearZLimit()
}

void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
}

void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

