// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "UObject/Object.h"

#include "BosAsc.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FReceivedDamage,UBosAsc*, SourceAsc, float, CleanDamage, float, CalculatedDamage );
UCLASS()
class BOS_API UBosAsc : public UAbilitySystemComponent	
{
	GENERATED_BODY()

public:
	bool GasAbilityGiven = false;
	bool StartEffectApplied = false;

	FReceivedDamage OnDamageReceived;

	virtual void ReceiveDamage(UBosAsc* SourceAsc, float CleanDamage, float CalculatedDamage);
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category= "Ability")
	int32 AbilityCount;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category= "Ability")
	TArray<UAnimMontage*> SimpleAttackMontages;

	UFUNCTION(BlueprintCallable, Category= "Ability")
	void AddMeleeCount();
	UFUNCTION(BlueprintCallable, BlueprintPure, Category= "Ability")
	UAnimMontage* GetNexAnimMontage();
};
