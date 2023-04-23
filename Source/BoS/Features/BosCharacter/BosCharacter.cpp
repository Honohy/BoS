// Fill out your copyright notice in the Description page of Project Settings.


#include "BosCharacter.h"
#include "AbilitySystemComponent.h"


// Sets default values
ABosCharacter::ABosCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(FName("AbilitySystemComponent"));
}

UAbilitySystemComponent* ABosCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
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

// Called to bind functionality to input
void ABosCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

