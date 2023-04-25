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
	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
}

UAbilitySystemComponent* ABosPlayerState::GetAbilitySystemComponent() const
{
	return BosAsc;
}

UBosAttributeSet* ABosPlayerState::GetAttributeSetBase() const
{
	return BosAttributeSet;
}

bool ABosPlayerState::IsAlive() const
{
	return GetHealth() > 0.0f;
}

void ABosPlayerState::ShowAbilityConfirmCancelText(bool ShowText)
{
}

float ABosPlayerState::GetHealth() const
{
	return BosAttributeSet->GetHealth();
}

float ABosPlayerState::GetMaxHealth() const
{
	return BosAttributeSet->GetMaxHealth();
}

float ABosPlayerState::GetCharacterLevel() const
{
	return BosAttributeSet->GetLevel();
}

void ABosPlayerState::BeginPlay()
{
	Super::BeginPlay();
	if (BosAsc)
	{
		HealthChangedDelegateHandle = BosAsc->GetGameplayAttributeValueChangeDelegate(BosAttributeSet->GetHealthAttribute()).AddUObject(this,&ABosPlayerState::HealthChanged);
		MaxHealthChangedDelegateHandle = BosAsc->GetGameplayAttributeValueChangeDelegate(BosAttributeSet->GetMaxHealthAttribute()).AddUObject(this,&ABosPlayerState::MaxHealthChanged);
		LevelChangedDelegateHandle = BosAsc->GetGameplayAttributeValueChangeDelegate(BosAttributeSet->GetLevelAttribute()).AddUObject(this,&ABosPlayerState::LevelChanged);
		BosAsc->RegisterGameplayTagEvent(FGameplayTag::RequestGameplayTag(FName("State.Debuff.Stun")),EGameplayTagEventType::NewOrRemoved).AddUObject(this,&ABosPlayerState::StunTagChanged);
	}
}

void ABosPlayerState::HealthChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp,Warning,TEXT("Health changed"));
}

void ABosPlayerState::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp,Warning,TEXT("MaxHealth changed"));
}

void ABosPlayerState::LevelChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp,Warning,TEXT("Level changed"));
}

void ABosPlayerState::StunTagChanged(const FGameplayTag CallBackTag, int32 NewCount)
{
	if (NewCount > 0)
	{
		FGameplayTagContainer AbilityTagsToCancel;
		AbilityTagsToCancel.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability")));

		FGameplayTagContainer AbilityTagsToIgnore;
		AbilityTagsToIgnore.AddTag(FGameplayTag::RequestGameplayTag(FName("Ability.NotCanceledByStun")));

		BosAsc->CancelAbilities(&AbilityTagsToCancel, &AbilityTagsToIgnore);
	}

}

