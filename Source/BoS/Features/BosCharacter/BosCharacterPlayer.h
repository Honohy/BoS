// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BoS/Features/BosCharacter/BosCharacterBase.h"
#include "UObject/Object.h"
#include "BosCharacterPlayer.generated.h"

class UCameraComponent;
class USpringArmComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHasBlock,bool, HasBlock);

UCLASS()
class BOS_API ABosCharacterPlayer : public ABosCharacterBase
{
	GENERATED_BODY()

public:
	ABosCharacterPlayer(const  FObjectInitializer& ObjectInitializer);
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;

	USpringArmComponent* GetCameraBoom();

	UCameraComponent* GetCamera();

	UFUNCTION(BlueprintCallable)
	float GetStartingCameraBoomArmLength();

	UFUNCTION(BlueprintCallable)
	FVector GetStartingCameraBoomLocation();
	
	UFUNCTION(Server, Unreliable)
	void SimpleStrike();

	// Block
	// Has block state
	UPROPERTY(ReplicatedUsing="OnRep_HasBlock")
	bool HasBLock;
	// Has block set state function
	UFUNCTION(BlueprintCallable, Category="Bos|Battle")
	void SetHasBlock(bool InHasBlock);
	// Has block replication
	UFUNCTION()
	void OnRep_HasBlock(bool OldHasBlock);
	// Has block delegate
	UPROPERTY(BlueprintAssignable)
	FOnHasBlock HasBockChanged;
	// Block end
	
protected:

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="Camera")
	float BaseTurnRate = 45.0f;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category="Camera")
	float BaseLookUpRate = 45.0f;
	
	UPROPERTY(BlueprintReadOnly,Category="Bos|Camera")
	float StartingCameraBoomArmLength;

	UPROPERTY(BlueprintReadOnly,Category="Bos|Camera")
	FVector StartingCameraBoomLocation;
	
	UPROPERTY(BlueprintReadOnly,Category="Bos|Camera")
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(BlueprintReadOnly, Category="Bos|Camera")
	UCameraComponent* FollowCamera;

	bool BosAsInputBound = false;

	virtual void BeginPlay() override;
	void BindBosInput();	
	void LookUp(float Value);
	void LookUpRate(float Value);
	void Turn(float Value);
	void TurnRate(float Value);
	void MoveForward(float Value);
	void MoveRight(float Value);
};
