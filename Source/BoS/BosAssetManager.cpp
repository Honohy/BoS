// Fill out your copyright notice in the Description page of Project Settings.


#include "BosAssetManager.h"

#include "AbilitySystemGlobals.h"

void UBosAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
	UAbilitySystemGlobals::Get().InitGlobalData();
	UE_LOG(LogTemp, Warning, TEXT("Asset manager initialized"));
}
