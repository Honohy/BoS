
#include "BosMovementComponent.h"

#include "GameFramework/Character.h"


UBosMovementComponent::UBosMovementComponent()
{
	IsSprint = false;
}

void FSavedMove_BosMovement::Clear()
{
	Super::Clear();
	SavedRequestSprint = false;
}

uint8 FSavedMove_BosMovement::GetCompressedFlags() const
{
	return Super::GetCompressedFlags();
}

bool FSavedMove_BosMovement::CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* Character, float MaxDelta) const
{
	if (SavedRequestSprint != ((FSavedMove_BosMovement*)&NewMove)->SavedRequestSprint)
		return false;
	return Super::CanCombineWith(NewMove, Character, MaxDelta);
}

void FSavedMove_BosMovement::SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel,
	FNetworkPredictionData_Client_Character& ClientData)
{
	Super::SetMoveFor(Character, InDeltaTime, NewAccel, ClientData);
	UBosMovementComponent* MC = Cast<UBosMovementComponent>(Character->GetCharacterMovement());
	if (MC)
	{
		SavedRequestSprint = MC->IsSprint;
	}
}

void FSavedMove_BosMovement::PrepMoveFor(ACharacter* Character)
{
	Super::PrepMoveFor(Character);
	UBosMovementComponent* MC = Cast<UBosMovementComponent>(Character->GetCharacterMovement());
	if (MC)
	{
		MC->IsSprint = SavedRequestSprint;
	}
}

FNetworkPredictionData_Client_BosMovement::FNetworkPredictionData_Client_BosMovement(const UCharacterMovementComponent& ClientMovementConmponent)
	: Super(ClientMovementConmponent)
{
	
}

FSavedMovePtr FNetworkPredictionData_Client_BosMovement::AllocateNewMove()
{
	return FSavedMovePtr(new FSavedMove_BosMovement());
}


