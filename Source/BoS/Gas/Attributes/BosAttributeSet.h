// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BosAttributeSet.generated.h"

// Uses macros from AttributeSet.h
//This is a MACRO that automatically generate all the boilerplate code for the property without you having to type out everything.

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class BOS_API UBosAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UBosAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	// Health
	UPROPERTY(BlueprintReadOnly, Category="Health",ReplicatedUsing= OnRep_Health)
	FGameplayAttributeData Health;
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);
	ATTRIBUTE_ACCESSORS(UBosAttributeSet,Health);
	
	UPROPERTY(BlueprintReadOnly, Category="MaxHealth",ReplicatedUsing= OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UBosAttributeSet,MaxHealth);
	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
	
	// Damage
	UPROPERTY(BlueprintReadOnly, Category="Damage",ReplicatedUsing= OnRep_Health)
	FGameplayAttributeData Damage;
	UFUNCTION()
	virtual void OnRep_Damage(const FGameplayAttributeData& OldHealth);
	

};
