// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "SprungWheel.h"

ASprungWheel::ASprungWheel()
{
	PrimaryActorTick.bCanEverTick = true;
	// BEWARE: These FName are the real name for the Physic Component to attach the components to in the BP editing!!!
	// BEWARE2: As we spawn this into the tank track, we need to root to not emulate physic, which is the case for physic constraint comp.
	PhysicsConstraintComp = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Physics Constraint Comp"));
	SetRootComponent(PhysicsConstraintComp);

	WheelMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel Mesh Comp"));
	WheelMesh->SetupAttachment(RootComponent);
	// Setup the rest in BP ...
}

void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	auto AttachedParentActor = GetAttachParentActor();
	if(AttachedParentActor)
	{
		// UE_LOG(LogTemp, Warning, TEXT("The attach parent actor: %s"), *AttachedParentActor->GetName());
		// We do not need bones names in our example this using NAME_None.
		auto BodyRoot = Cast<UPrimitiveComponent>(AttachedParentActor->GetRootComponent());
		if(!BodyRoot) return;
		PhysicsConstraintComp->SetConstrainedComponents
		(
			BodyRoot,
			NAME_None ,
			WheelMesh,
			NAME_None 
		);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("The attach parent actor is null"));
	}
}

void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

