// Fill out your copyright notice in the Description page of Project Settings.


#include "BosGameplayAbility.h"
#include "BoS/Gas/BosAsc.h"

UBosGameplayAbility::UBosGameplayAbility()
{
}

void UBosGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);
	if (AbilityActivated)
	{
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	}
}
