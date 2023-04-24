// Fill out your copyright notice in the Description page of Project Settings.


#include "BosCharacter.h"
#include "AbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "BoS/Gas/BosAsc.h"
#include "BoS/Gas/Abilitiees/BosGameplayAbility.h"


// Sets default values
ABosCharacter::ABosCharacter(const FObjectInitializer& ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Overlap);
	bAlwaysRelevant = true;
	// Gas tags
	DeadTag = FGameplayTag::RequestGameplayTag(FName("State.Dead"));
	EffectRemoveOnDeathTag = FGameplayTag::RequestGameplayTag(FName("State.RemoveOnDeath"));
}

UAbilitySystemComponent* ABosCharacter::GetAbilitySystemComponent() const
{
	return BosAsc.Get();
}

// Called when the game starts or when spawned
void ABosCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABosCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ABosCharacter::IsAlive() const
{
	return GetHealth() > 0.0f;
}

int32 ABosCharacter::GetAbilityLevel(EBosAbilities AbilityId) const
{
	return 1;
}

void ABosCharacter::RemoveCharacterAbilities()
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

// Called to bind functionality to input
void ABosCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

