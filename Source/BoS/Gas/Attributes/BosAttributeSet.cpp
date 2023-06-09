// Fill out your copyright notice in the Description page of Project Settings.


#include "BosAttributeSet.h"
#include "Net/UnrealNetwork.h"

UBosAttributeSet::UBosAttributeSet()
{
}

void UBosAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UBosAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBosAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBosAttributeSet, Damage, COND_None, REPNOTIFY_Always);
}

void UBosAttributeSet::OnRep_Level(const FGameplayAttributeData& OldLevel)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBosAttributeSet,Level, OldLevel);
}

void UBosAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBosAttributeSet,Health, OldHealth);
}

void UBosAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBosAttributeSet,MaxHealth, OldMaxHealth);
}

void UBosAttributeSet::OnRep_Damage(const FGameplayAttributeData& OldDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UBosAttributeSet,Damage, OldDamage);
}
