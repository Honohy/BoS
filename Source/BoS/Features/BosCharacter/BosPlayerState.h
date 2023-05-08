// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerState.h"
#include "GameplayTags.h"
#include "BoS/Gas/Attributes/BosAttributeSet.h"
#include "GameplayEffectTypes.h"
#include "BosPlayerState.generated.h"

class UBosAttributeSet;
class UBosAsc;
UCLASS()
class BOS_API ABosPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABosPlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UBosAttributeSet* GetAttributeSetBase() const;

	UFUNCTION(BlueprintCallable, Category="Bos|PlayerState")
	bool IsAlive() const;
	UFUNCTION(BlueprintCallable, Category="Bos|PlayerState|UI")
	void ShowAbilityConfirmCancelText(bool ShowText);
	
	UFUNCTION(BlueprintCallable, Category="Bos|PlayerStat|Attributes")
	float GetHealth() const;
	UFUNCTION(BlueprintCallable, Category="Bos|PlayerStat|Attributes")
	float GetMaxHealth() const;
	UFUNCTION(BlueprintCallable, Category="Bos|PlayerStat|Attributes")
	float GetCharacterLevel() const;

protected:
	UPROPERTY(EditDefaultsOnly)
	UBosAsc* BosAsc;
	UPROPERTY()
	UBosAttributeSet* BosAttributeSet;

	FGameplayTag DeadTag;
	FDelegateHandle HealthChangedDelegateHandle;
	FDelegateHandle MaxHealthChangedDelegateHandle;
	FDelegateHandle LevelChangedDelegateHandle;

	virtual void BeginPlay() override;
	
	virtual void HealthChanged(const FOnAttributeChangeData& Data);
	virtual void MaxHealthChanged(const FOnAttributeChangeData& Data);
	virtual void LevelChanged(const FOnAttributeChangeData& Data);

	virtual void StunTagChanged(const FGameplayTag CallBackTag, int32 NewCount);
};
