// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemInterface.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BoS/Common/BosEnum.h"
#include "BosCharacter.generated.h"

struct FGameplayTag;
class UBosAttributeSet;
class UBosAsc;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDead, ABosCharacter*, DiedCharacter);
UCLASS()
class BOS_API ABosCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABosCharacter(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintAssignable, Category="BoS|Charcter")
	FCharacterDead OnCharacterDied;
	UPROPERTY(BlueprintCallable, Category="BoS|Charcter")
	virtual bool IsAlive() const;
	UPROPERTY(BlueprintCallable, Category="BoS|Charcter")
	virtual int32 GetAbilityLevel(EBosAbilities AbilityId) const;
	virtual void RemoveCharacterAbilities();
	virtual void Die();
	UFUNCTION(BlueprintCallable, Category="BoS|Charcter")
	virtual void FinishDying();

	UFUNCTION(BlueprintCallable, Category="BoS|Charcter|Attributes");
	float GetHealth() const;
	
	UFUNCTION(BlueprintCallable, Category="BoS|Charcter|Attributes");
	float GetMaxHealth() const;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
protected:
	
	// Ability system 
	TWeakObjectPtr<UBosAsc> BosAsc;
	TWeakObjectPtr<UBosAttributeSet> BosAttributeSet;

	FGameplayTag DeadTag;
	FGameplayTag EffectRemoveOnDeathTag;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
