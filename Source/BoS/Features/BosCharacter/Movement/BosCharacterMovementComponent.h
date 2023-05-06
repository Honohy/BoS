// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BosCharacterMovementComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BOS_API UBosCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
	friend class FSavedMove_Bos;

public:

	virtual FNetworkPredictionData_Client* GetPredictionData_Client() const override;
	virtual void UpdateFromCompressedFlags(uint8 Flags) override;
	FORCEINLINE bool IsSprinting() { return HasSprint; };
	UBosCharacterMovementComponent();
	virtual float GetMaxSpeed() const override;

protected:
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="BosMovement",meta=(ClampMin = 0.0f, ClampMax = 900.0f))
	float SprintSpeed = 350.0f; //Unit per sec
	float WalkSpeed = 250.0f; //Unit per sec
	void StartSprinting();
	void StopSprinting();

private:
	bool HasSprint;
	void ChangeMaxWalkSpeed(float InNewMaxWalkSpeed);
};

class FSavedMove_Bos : FSavedMove_Character
{
	typedef FSavedMove_Character Super;
public:
	virtual void Clear() override;
	virtual uint8 GetCompressedFlags() const override;
	virtual bool CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const override;
	virtual void SetMoveFor(ACharacter* C, float InDeltaTime, FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData) override;
	virtual void PrepMoveFor(ACharacter* C) override;

private:
	uint8 bSaveIsSprinting : 1;
};

class FNetworkPredictionData_Client_Character_Bos : public FNetworkPredictionData_Client_Character
{
	typedef FNetworkPredictionData_Client_Character Super;
	
public:
	FNetworkPredictionData_Client_Character_Bos(const UCharacterMovementComponent& ClientComponent);

	virtual FSavedMovePtr AllocateNewMove() override;
};