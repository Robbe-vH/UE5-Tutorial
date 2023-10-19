// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveComponent.h"

// Sets default values for this component's properties
UMoveComponent::UMoveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMoveComponent::BeginPlay()
{
	Super::BeginPlay();

	// Set start location
	StartRelativeLocation = GetRelativeLocation();

	// Compute normalized distance
	MoveOffsetNorm = MoveOffset;
	MoveOffsetNorm.Normalize();
	MaxDistance = MoveOffset.Length();

	// Check if ticking is requried
	SetComponentTickEnabled(MoveEnable);
}

void UMoveComponent::EnableMovement(bool ShouldMove) {
	MoveEnable = ShouldMove;
	SetComponentTickEnabled(MoveEnable);
}

/// Reset to original position
void UMoveComponent::ResetMovement() {

	CurrentDistance = 0.0f;
	SetRelativeLocation(StartRelativeLocation);
}

void UMoveComponent::SetMoveDirection(int Direction)
{
	MoveDirection = Direction >= 1 ? 1 : -1;
}


// Called every frame
void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (MoveEnable) {
		// Set current distance
		CurrentDistance += DeltaTime * movementSpeed * MoveDirection;

		if (CurrentDistance >= MaxDistance || CurrentDistance <= 0.0f) {
			// Invert Direction
			MoveDirection *= -1;

			// Fire event
			OnEndpointReached.Broadcast(CurrentDistance >= MaxDistance);

			// Clamp distance
			CurrentDistance = FMath::Clamp(CurrentDistance, 0.0f, MaxDistance);
		}
	}

	// Compute and set current location
	SetRelativeLocation(StartRelativeLocation + MoveOffsetNorm * CurrentDistance);
}

