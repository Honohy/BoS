// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoS/Features/BosCharacter/BosCharacterBase.h"
#include "UObject/Object.h"
#include "BosCharacterPlayer.generated.h"

class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class BOS_API ABosCharacterPlayer : public ABosCharacterBase
{
	GENERATED_BODY()

public:
	ABosCharacterPlayer(const  FObjectInitializer& ObjectInitializer);
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

	USpringArmComponent* GetCameraBoom();

	UCameraComponent* GetCamera();
	
};
