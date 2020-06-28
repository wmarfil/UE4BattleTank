// Fill out your copyright notice in the Description page of Project Settings.
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"

// Sets default values for this component's properties
USpawnPoint::USpawnPoint()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void USpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
	// This allows to not trigger the BP and construction script of the spawned actor until the caller, ie here, we order it with UGameplayStatics::FinishSpawningActor
	SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(
		SpawningActor,
		GetComponentTransform()
	);
	// UE_LOG(LogTemp, Warning, TEXT("After spawn"));
	if(!SpawnedActor) return;

	// for second parameter: as we specified the world transform in SpawnActorDeferred via GetComponentTransform()
	// for actor to be spawned into, we just need to indicate FAttachmentTransformRules::KeepWorldTransform
	SpawnedActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	UGameplayStatics::FinishSpawningActor(SpawnedActor, GetComponentTransform());

}

void USpawnPoint::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

AActor* USpawnPoint::GetSpawnedActor() const {return SpawnedActor;}

