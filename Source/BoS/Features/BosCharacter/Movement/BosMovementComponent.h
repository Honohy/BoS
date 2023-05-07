
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BosMovementComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BOS_API UBosMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UBosMovementComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere,Category="Bos|Movement")
	float WalkSpeed;
	UPROPERTY(BlueprintReadOnly, EditAnywhere,Category="Bos|Movement")
	float SprintSpeed;
	UPROPERTY(BlueprintReadOnly)
	bool IsSprint;

	UFUNCTION(BlueprintCallable, Category="Bos|Movement")
	void SetSprintEnabled(bool InSprint);
	UFUNCTION(Server,BlueprintCallable, Unreliable, Category="Bos|Movement")
	void Server_SetSprintEnabled(bool InSprint);
	UFUNCTION(NetMulticast, BlueprintCallable, Unreliable, Category="Bos|Movement")
	void Multicast_SetSprintEnabled(bool InSprint);
};

class FSavedMove_BosMovement : public FSavedMove_Character
{
	friend class UBosMovementComponent;

public:
	typedef FSavedMove_Character Super;
	virtual void Clear() override;
	virtual uint8 GetCompressedFlags() const override;
	virtual bool CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* Character, float MaxDelta) const override;
	virtual void SetMoveFor(ACharacter* Character, float InDeltaTime, FVector const& NewAccel, class FNetworkPredictionData_Client_Character & ClientData) override;
	virtual void PrepMoveFor(ACharacter* Character) override;

	bool SavedRequestSprint : 1;
};

class FNetworkPredictionData_Client_BosMovement : public FNetworkPredictionData_Client_Character
{
	FNetworkPredictionData_Client_BosMovement(const UCharacterMovementComponent& ClientMovementConmponent);
	typedef FNetworkPredictionData_Client_Character Super;
	virtual FSavedMovePtr AllocateNewMove() override;
};