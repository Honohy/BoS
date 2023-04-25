// Fill out your copyright notice in the Description page of Project Settings.


#include "BosPlayerController.h"

#include "BoS/Features/BosCharacter/BosPlayerState.h"


// Sets default values
ABosPlayerController::ABosPlayerController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ABosPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	ABosPlayerState* CurrentPlayerState = InPawn->GetPlayerState<ABosPlayerState>();
	if (CurrentPlayerState)
	{
		CurrentPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(PlayerState, InPawn);
	}
}

// Called every frame
void ABosPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

