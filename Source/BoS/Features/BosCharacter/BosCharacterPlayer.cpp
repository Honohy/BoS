// Fill out your copyright notice in the Description page of Project Settings.


#include "BosCharacterPlayer.h"

#include "BosPlayerState.h"
#include "BoS/Gas/BosAsc.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "BoS/Common/BosEnum.h"
#include "Net/UnrealNetwork.h"

ABosCharacterPlayer::ABosCharacterPlayer(const  FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bReplicates = true;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(FName("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SetRelativeLocation(FVector(0.0,0.0,70.0));

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	FollowCamera->SetupAttachment(CameraBoom);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionProfileName(FName("NoCollision"));

	DeadTag = FGameplayTag::RequestGameplayTag("State.Dead");
}

void ABosCharacterPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABosCharacterPlayer, HasBLock);
}

void ABosCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ABosCharacterPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABosCharacterPlayer::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &ABosCharacterPlayer::LookUp);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ABosCharacterPlayer::LookUpRate);
	PlayerInputComponent->BindAxis("Turn", this, &ABosCharacterPlayer::Turn);
	PlayerInputComponent->BindAxis("TurnRate", this, &ABosCharacterPlayer::TurnRate);
	
	PlayerInputComponent->BindAction("LM Btn WeaponAttack",IE_Pressed, this, &ABosCharacterPlayer::SimpleStrike);

	BindBosInput();
}

void ABosCharacterPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	ABosPlayerState* LocalPlayerState = GetPlayerState<ABosPlayerState>();

	// Initialize star values
	if (LocalPlayerState)
	{
		BosAsc = Cast<UBosAsc>(LocalPlayerState->GetAbilitySystemComponent());
		BosAsc->InitAbilityActorInfo(LocalPlayerState,this);
		BosAttributeSet = LocalPlayerState->GetAttributeSetBase();
		BosAsc->SetTagMapCount(DeadTag,0);
		SetHealth(GetMaxHealth());
		AddStartEffects();
		AddCharacterAbilities();
		InitializeAttributes();
	}
	
}

USpringArmComponent* ABosCharacterPlayer::GetCameraBoom()
{
	return CameraBoom;
}

UCameraComponent* ABosCharacterPlayer::GetCamera()
{
	return FollowCamera;
}

float ABosCharacterPlayer::GetStartingCameraBoomArmLength()
{
	return GetCameraBoom()->TargetArmLength;
}

FVector ABosCharacterPlayer::GetStartingCameraBoomLocation()
{
	return FVector::ZeroVector;
}

void ABosCharacterPlayer::SetHasBlock(bool InHasBlock)
{
	HasBLock = InHasBlock;
}

void ABosCharacterPlayer::SimpleStrike_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("SimpleStrike"));
}

void ABosCharacterPlayer::LookUp(float Value)
{
	if (!IsAlive()) return;
	AddControllerPitchInput(Value);
}

void ABosCharacterPlayer::LookUpRate(float Value)
{
	if (!IsAlive()) return;
	AddControllerPitchInput(Value * BaseLookUpRate);
}

void ABosCharacterPlayer::Turn(float Value)
{
	if (!IsAlive()) return;
	AddControllerYawInput(Value);
}

void ABosCharacterPlayer::TurnRate(float Value)
{
	if (!IsAlive()) return;
	AddControllerYawInput(Value * BaseTurnRate);
}

void ABosCharacterPlayer::MoveForward(float Value)
{
	if (!IsAlive()) return;
	AddMovementInput(GetActorForwardVector(), Value);
}

void ABosCharacterPlayer::MoveRight(float Value)
{
	if (!IsAlive()) return;
	AddMovementInput(GetActorRightVector(),Value);
}

void ABosCharacterPlayer::OnRep_HasBlock(bool OldHasBlock)
{
	HasBockChanged.Broadcast(OldHasBlock);
}

void ABosCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
	StartingCameraBoomLocation = CameraBoom->GetRelativeLocation();
	StartingCameraBoomArmLength = CameraBoom->TargetArmLength;
}

void ABosCharacterPlayer::BindBosInput()
{
	if (!BosAsInputBound && BosAsc.IsValid() && IsValid(InputComponent))
	{
		BosAsc->BindAbilityActivationToInputComponent(InputComponent,FGameplayAbilityInputBinds(
			FString("ConfirmTarget"),FString("CancelTarget"),
			FString("EBosAbilities"),(int32)EBosAbilities::Confirm, (int32)EBosAbilities::Cancel));
		
		BosAsInputBound = true;
	}
}
