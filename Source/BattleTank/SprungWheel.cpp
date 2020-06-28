// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "SprungWheel.h"

ASprungWheel::ASprungWheel()
{
	PrimaryActorTick.bCanEverTick = true;
	// We want this to tick after OnHit triggering, this means we want to be the tick group PostPhysic. DuringPhysic and default PrePhysic are too soon.
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	// BEWARE: These FName are the real name for the Physic Component to attach the components to in the BP editing!!!
	// BEWARE2: As we spawn this into the tank track, we need the root i.e. our physic constraint comp to not emulate physic.
	SpringConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Physics Constraint"));
	SetRootComponent(SpringConstraint);

	AxleMesh = CreateDefaultSubobject<USphereComponent>(FName("Axle Mesh"));
	AxleMesh->SetupAttachment(RootComponent);

	WheelMesh = CreateDefaultSubobject<USphereComponent>(FName("Wheel Mesh"));
	WheelMesh->SetupAttachment(AxleMesh);
	WheelMesh->SetNotifyRigidBodyCollision(true);
	WheelMesh->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);

	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Axle Constraint"));
	AxleWheelConstraint->SetupAttachment(AxleMesh);
	// Setup the rest in BP ...
}

void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	auto AttachedParentActor = GetAttachParentActor();
	if(AttachedParentActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Setting up constraints to parent actor: %s"), *AttachedParentActor->GetName());
		// We do not need bones names in our example this using NAME_None.
		auto BodyRoot = Cast<UPrimitiveComponent>(AttachedParentActor->GetRootComponent());
		if(!BodyRoot) return;
		SpringConstraint->SetConstrainedComponents
		(
			BodyRoot,
			NAME_None ,
			AxleMesh,
			NAME_None 
		);

		AxleWheelConstraint->SetConstrainedComponents
		(
			AxleMesh,
			NAME_None ,
			WheelMesh,
			NAME_None 
		);
		UE_LOG(LogTemp, Warning, TEXT("Finished setting up constraints to parent actor: %s"), *AttachedParentActor->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("The attach parent actor is null"));
	}
}

void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	ApplyForce();
}

void ASprungWheel::ApplyForce()
{
	WheelMesh->AddForce(AxleMesh->GetForwardVector() * TotalForceMagnitudeThisFrame);
}

void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Cancel force of the wheel! we intend to get this executed right after the on hit because we configured tickgroup PostPhysics.
	if(GetWorld()->TickGroup == TG_PostPhysics)
	{
		TotalForceMagnitudeThisFrame = 0;
	}
}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	// Why? Because we would this simultaneously from intend turn move righ AND intend move forward.
	TotalForceMagnitudeThisFrame += ForceMagnitude;
}

