// Fill out your copyright notice in the Description page of Project Settings.


#include "BosAsc.h"

void UBosAsc::ReceiveDamage(UBosAsc* SourceAsc, float CleanDamage, float CalculatedDamage)
{
	OnDamageReceived.Broadcast(SourceAsc,CleanDamage,CalculatedDamage);
}
