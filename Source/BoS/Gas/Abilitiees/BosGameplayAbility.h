// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "UObject/Object.h"
#include "BosGameplayAbility.generated.h"

UENUM()
enum class EBosAbilities : uint8
{
	None,
	Confirm,
	Cancel
};
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
	EBosAbilities AbilityInputID;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EBosAbilities AbilityID;
	
	
};
