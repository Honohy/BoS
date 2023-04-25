// Fill out your copyright notice in the Description page of Project Settings.


#include "BosCharacterPlayer.h"

ABosCharacterPlayer::ABosCharacterPlayer(const  FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void ABosCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABosCharacterPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

USpringArmComponent* ABosCharacterPlayer::GetCameraBoom()
{
	return nullptr;
}

UCameraComponent* ABosCharacterPlayer::GetCamera()
{
	return nullptr;
}
