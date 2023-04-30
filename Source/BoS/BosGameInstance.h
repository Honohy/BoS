// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BosGameInstance.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class BOS_API UBosGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	virtual void Init() override;
};
