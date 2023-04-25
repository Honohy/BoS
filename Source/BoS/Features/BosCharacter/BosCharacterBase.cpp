// Fill out your copyright notice in the Description page of Project Settings.


#include "BosCharacterBase.h"
#include "Bos/Gas/Attributes/BosAttributeSet.h"
#include "BoS/Gas/BosAsc.h"
#include "BoS/Gas/Abilitiees/BosGameplayAbility.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
ABosCharacterBase::ABosCharacterBase(const FObjectInitializer& ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Overlap);
	bAlwaysRelevant = true;
	
	// Gas tags
	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
	EffectRemoveOnDeathTag = FGameplayTag::RequestGameplayTag(FName("State.RemoveOnDeath"));
	
}

UAbilitySystemComponent* ABosCharacterBase::GetAbilitySystemComponent() const
{
	//return BosAsc.Get();
	return nullptr;
}

// Called when the game starts or when spawned
void ABosCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABosCharacterBase::AddCharacterAbilities()
{
	if (GetRemoteRole() != EGameplayAbilityActivationMode::Authority || !BosAsc.IsValid() ||
		!BosAsc->GasAbilityGiven)
		return;
	for (TSubclassOf<UBosGameplayAbility>& CurrentAbility : Abilities)
	{
		BosAsc->GiveAbility(FGameplayAbilitySpec(CurrentAbility, GetAbilityLevel(CurrentAbility.GetDefaultObject()->AbilityInputID),
			static_cast<int32>(CurrentAbility.GetDefaultObject()->AbilityInputID)));
	}
	BosAsc->GasAbilityGiven = true;
}


void ABosCharacterBase::InitializeAttributes()
{
	if (!BosAsc.IsValid())
		return;
	if (!DefaultAttributes)
	{
		UE_LOG(LogTemp, Error, TEXT("%s() Missing DefaultAttributes for %s. Please fill in the character's Blueprint."), *FString(__FUNCTION__), *GetName());
		return;
	}

	FGameplayEffectContextHandle EffectContext;
	EffectContext.AddSourceObject(this);
	FGameplayEffectSpecHandle NewHandle = BosAsc->MakeOutgoingSpec(DefaultAttributes, GetCharacterLevel(), EffectContext);
	if (NewHandle.IsValid())
		BosAsc->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), BosAsc.Get());
}

void ABosCharacterBase::AddStartEffects()
{
	if (GetLocalRole() != ROLE_Authority || !BosAsc.IsValid() || BosAsc->StartEffectApplied)
		return;
	FGameplayEffectContextHandle EffectContext = BosAsc->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (TSubclassOf<UGameplayEffect> CurrentEffect : StartEffects)
	{
		FGameplayEffectSpecHandle NewSpecHandle = BosAsc->MakeOutgoingSpec(CurrentEffect,GetCharacterLevel(),EffectContext);
		if (NewSpecHandle.IsValid())
			BosAsc->ApplyGameplayEffectSpecToTarget(*NewSpecHandle.Data.Get(),BosAsc.Get());
	}

	BosAsc->StartEffectApplied = true;
}

void ABosCharacterBase::SetHealth(float Health)
{
	if (BosAttributeSet.IsValid())
		BosAttributeSet->SetHealth(Health);
}

// Called every frame
void ABosCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ABosCharacterBase::IsAlive() const
{
	return true;
}

int32 ABosCharacterBase::GetAbilityLevel(EBosAbilities AbilityId) const
{
	return 1;
}

void ABosCharacterBase::RemoveCharacterAbilities()
{
	if (GetRemoteRole() != EGameplayAbilityActivationMode::Authority || !BosAsc.IsValid() || !BosAsc->GasAbilityGiven)
	{
		return;
	}
	TArray <FGameplayAbilitySpecHandle> AbilitiesToRemove;
	for (const FGameplayAbilitySpec &Spec : BosAsc->GetActivatableAbilities())
	{
		if ((Spec.SourceObject == this) && Abilities.Contains(Spec.Ability.GetClass()))
		{
			AbilitiesToRemove.Add(Spec.Handle);
		}
	}
	for (int32 i = 0; i < AbilitiesToRemove.Num(); i++)
	{
		BosAsc->ClearAbility(AbilitiesToRemove[i]);
	}

	BosAsc->GasAbilityGiven = false;
}

void ABosCharacterBase::Die()
{
	RemoveCharacterAbilities();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCharacterMovement()->GravityScale = 0;
	GetCharacterMovement()->Velocity = FVector::ZeroVector;
	if (BosAsc.IsValid())
	{
		GetAbilitySystemComponent()->CancelAbilities();
		FGameplayTagContainer EffectTagToRemove;
		EffectTagToRemove.AddTag(EffectRemoveOnDeathTag);
		int32 NumOfEffectremoving = BosAsc->RemoveActiveEffectsWithTags(EffectTagToRemove);
		BosAsc->AddLooseGameplayTag(DeadTag);
	}
	
	OnCharacterDied.Broadcast(this);
}

void ABosCharacterBase::FinishDying()
{
	Destroy();
}

int32 ABosCharacterBase::GetCharacterLevel()
{
	if (!BosAttributeSet.IsValid())
		return -1;
	return BosAttributeSet->GetLevel();
}

float ABosCharacterBase::GetHealth() const
{
	if (!BosAttributeSet.IsValid())
		return 0.0f;
	return BosAttributeSet->GetHealth();
}

float ABosCharacterBase::GetMaxHealth() const
{
	if (BosAttributeSet.IsValid())
	return BosAttributeSet->GetMaxHealth();
	return 0.0f;
}
