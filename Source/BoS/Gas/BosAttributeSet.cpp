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
}

void UBosAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
}

void UBosAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
}
