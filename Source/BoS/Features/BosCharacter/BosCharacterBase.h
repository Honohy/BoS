// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BoS/Common/BosEnum.h"
#include "BosCharacterBase.generated.h"

class UGameplayEffect;
struct FGameplayTag;
class UBosAttributeSet;
class UBosAsc;
class UBosGameplayAbility;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDead, ABosCharacterBase*, DiedCharacter);
UCLASS()
class BOS_API ABosCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	ABosCharacterBase(const class FObjectInitializer& ObjectInitializer);
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Delegates
	UPROPERTY(BlueprintAssignable, Category="BoS|Charcter")
	FCharacterDead OnCharacterDied;

	// Methods
	UFUNCTION(BlueprintCallable, Category="BoS|Charcter")
	virtual bool IsAlive() const;
	UFUNCTION(BlueprintCallable, Category="BoS|Charcter")
	virtual int32 GetAbilityLevel(EBosAbilities AbilityID) const;
	virtual void RemoveCharacterAbilities();

	//Chaaracter
	//Character's level
	UFUNCTION(BlueprintCallable, Category="BoS|Charcter")
	virtual void FinishDying();
	UFUNCTION(BlueprintCallable, Category="BoS|Charcter|Attributes")
	int32 GetCharacterLevel();
	
	// Character's health
	UFUNCTION(BlueprintCallable, Category="BoS|Charcter|Attributes")
	float GetHealth() const;
	
	// Character's max health
	UFUNCTION(BlueprintCallable, Category="BoS|Charcter|Attributes")
	float GetMaxHealth() const;
	
	virtual void Die();
		
protected:
		
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Ability system
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Bos|Abilities")
	TArray<TSubclassOf<UBosGameplayAbility>> Abilities;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Bos|Abilities")
	TSubclassOf<UGameplayEffect> DefaultAttributes;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Bos|Abilities")
	TArray<TSubclassOf<UGameplayEffect>> StartEffects;

	TWeakObjectPtr<UBosAsc> BosAsc;
	TWeakObjectPtr<UBosAttributeSet> BosAttributeSet;
	FGameplayTag DeadTag;
	FGameplayTag EffectRemoveOnDeathTag;

	virtual void AddCharacterAbilities();
	virtual void InitializeAttributes();
	virtual void AddStartEffects();
	virtual void SetHealth(float Health);
	
};
