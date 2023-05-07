// Fill out your copyright notice in the Description page of Project Settings.


#include "BosCharacterMovementComponent.h"


void FSavedMove_Bos::Clear()
{
	FSavedMove_Character::Clear();
	bSaveIsSprinting = 0;
}

uint8 FSavedMove_Bos::GetCompressedFlags() const
{
	bool Result = Super::GetCompressedFlags();
	/*
	FLAG_JumpPressed	= 0x01,	// Jump pressed
	FLAG_WantsToCrouch	= 0x02,	// Wants to crouch
	FLAG_Reserved_1		= 0x04,	// Reserved for future use
	FLAG_Reserved_2		= 0x08,	// Reserved for future use
	// Remaining bit masks are available for custom flags.
	FLAG_Custom_0		= 0x10, // IsSprinting
	FLAG_Custom_1		= 0x20,
	FLAG_Custom_2		= 0x40,
	FLAG_Custom_3		= 0x80,
	*/
	if (bSaveIsSprinting)
	{
		Result |= FLAG_Custom_0;
	}

	return Result;
}

bool FSavedMove_Bos::CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const
{
	return FSavedMove_Character::CanCombineWith(NewMove, InCharacter, MaxDelta);
}

void FSavedMove_Bos::SetMoveFor(ACharacter* C, float InDeltaTime, FVector const& NewAccel,
	FNetworkPredictionData_Client_Character& ClientData)
{
	FSavedMove_Character::SetMoveFor(C, InDeltaTime, NewAccel, ClientData);
}

void FSavedMove_Bos::PrepMoveFor(ACharacter* C)
{
	FSavedMove_Character::PrepMoveFor(C);
}

// Sets default values for this component's properties
UBosCharacterMovementComponent::UBosCharacterMovementComponent()
{
}

float UBosCharacterMovementComponent::GetMaxSpeed() const
{
	float result = Super::GetMaxSpeed();
	if (HasSprint)
		result = SprintSpeed;
	return result;
}

void UBosCharacterMovementComponent::StartSprinting()
{
	HasSprint = true;
	bForceMaxAccel = true;
	ChangeMaxWalkSpeed(SprintSpeed);
}

void UBosCharacterMovementComponent::StopSprinting()
{
	HasSprint = false;
	bForceMaxAccel = 0;
	ChangeMaxWalkSpeed(WalkSpeed);
}

void UBosCharacterMovementComponent::ChangeMaxWalkSpeed(float InNewMaxWalkSpeed)
{
	MaxWalkSpeed = InNewMaxWalkSpeed;
}


