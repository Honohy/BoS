// Fill out your copyright notice in the Description page of Project Settings.


#include "BosPlayerState.h"

#include "BoS/Gas/BosAsc.h"


// Sets default values
ABosPlayerState::ABosPlayerState()
{
	BosAsc = CreateDefaultSubobject<UBosAsc>(TEXT("AbilitySystemComponent"));
	BosAsc->SetIsReplicated(true);
	BosAsc->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	BosAttributeSet = CreateDefaultSubobject<UBosAttributeSet>(TEXT("AttributeSet"));
	NetUpdateFrequency = 100.0f;
	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Death"));
}

UAbilitySystemComponent* ABosPlayerState::GetAbilitySystemComponent() const
{
	return nullptr;
}

UBosAttributeSet* ABosPlayerState::GetAttributeSetBase() const
{
	return nullptr;
}

bool ABosPlayerState::IsAlive() const
{
	return true;
}

void ABosPlayerState::ShowAbilityConfirmCancelText(bool ShowText)
{
}

float ABosPlayerState::GetHealth() const
{
	return 0.0f;
}

float ABosPlayerState::GetMaxHealth() const
{
	return 0.0f;
}

float ABosPlayerState::GetCharacterLevel() const
{
	return 0.0f;
}

void ABosPlayerState::HealthChanged(const FOnAttributeChangeData)
{
}

void ABosPlayerState::MaxHealthChanged(const FOnAttributeChangeData)
{
}

void ABosPlayerState::LevelChanged(const FOnAttributeChangeData)
{
}

void ABosPlayerState::StunTagChanged(const FGameplayTag CallBackTag, int32 NewCount)
{
}

