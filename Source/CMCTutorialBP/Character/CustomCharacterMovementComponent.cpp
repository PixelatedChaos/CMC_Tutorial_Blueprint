// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCharacterMovementComponent.h"

//Constructor
UCustomCharacterMovementComponent::UCustomCharacterMovementComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bUseSeparateBrakingFriction = true;
	bUseMovementProfiles = true;
}

void UCustomCharacterMovementComponent::K2_StartNewPhysics_Implementation(float deltaTime, int32 Iterations)
{
	Super::StartNewPhysics(deltaTime, Iterations);
}

void UCustomCharacterMovementComponent::StartNewPhysics(float deltaTime, int32 Iterations)
{
	K2_StartNewPhysics(deltaTime, Iterations);
}

bool UCustomCharacterMovementComponent::K2_DoJump_Implementation(bool bReplayingMoves)
{
	return Super::DoJump(bReplayingMoves);
}

bool UCustomCharacterMovementComponent::DoJump(bool bReplayingMoves)
{
	return K2_DoJump(bReplayingMoves);
}

void UCustomCharacterMovementComponent::SetCurrentMovementProfile_Implementation(FMovementProfile NewProfile)
{
	CustomMaxSpeed = NewProfile.CustomMaxSpeed;
	CustomMaxAcceleration = NewProfile.CustomMaxAcceleration;
	CustomMaxDeceleration = NewProfile.CustomMaxDeceleration;
	AirControl = NewProfile.CustomAirControl;
	BrakingFriction = NewProfile.CustomBrakingFriction;
	GravityScale = NewProfile.CustomGravityScale;
	JumpZVelocity = NewProfile.CustomJumpForce;
	SetMovementMode(NewProfile.DesiredMovementMode);
}

FVector UCustomCharacterMovementComponent::K2_ScaleInputAcceleration_Implementation(const FVector& InputAcceleration) const
{
	return Super::ScaleInputAcceleration(InputAcceleration);
}

FVector UCustomCharacterMovementComponent::ScaleInputAcceleration(const FVector& InputAcceleration) const
{
	return K2_ScaleInputAcceleration(InputAcceleration);
}

