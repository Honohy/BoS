// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "UObject/Object.h"
#include "BoS/Common/BosEnum.h"
#include "BosGameplayAbility.generated.h"


/**
 * 
 */
UCLASS()
class BOS_API UBosGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UBosGameplayAbility();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EBosAbilities AbilityInputID = EBosAbilities::None;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EBosAbilities AbilityID = EBosAbilities::None;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	bool AbilityActivated;
	
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	
};
