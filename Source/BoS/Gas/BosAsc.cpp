// Fill out your copyright notice in the Description page of Project Settings.


#include "BosAsc.h"

void UBosAsc::ReceiveDamage(UBosAsc* SourceAsc, float CleanDamage, float CalculatedDamage)
{
	OnDamageReceived.Broadcast(SourceAsc,CleanDamage,CalculatedDamage);
}

void UBosAsc::AddMeleeCount()
{
	AbilityCount++;
	if (AbilityCount >= SimpleAttackMontages.Num())
		AbilityCount = 0;
}

UAnimMontage* UBosAsc::GetNexAnimMontage()
{
	if (AbilityCount >= SimpleAttackMontages.Num())
		return nullptr;
	return SimpleAttackMontages[AbilityCount];
}
