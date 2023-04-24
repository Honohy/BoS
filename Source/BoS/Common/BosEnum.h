// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BosEnum.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EBosAbilities : uint8
{
	None = 0,
	Confirm,
	Cancel
};
