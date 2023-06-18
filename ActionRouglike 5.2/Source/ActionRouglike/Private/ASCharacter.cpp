// Fill out your copyright notice in the Description page of Project Settings.


#include "ASCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include <EnhancedInputSubsystems.h>
#include "GameFramework/CharacterMovementComponent.h"
#include "SInteractionComponent.h"
#include "Animation/AnimMontage.h"
#include "SAttributeComponent.h"

// Sets default values
AASCharacter::AASCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	this->CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera");

	SpringArmComp->SetupAttachment(RootComponent);
	CameraComp->SetupAttachment(SpringArmComp);

	SpringArmComp->bUsePawnControlRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;

	//交互
	_interactionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");

	//属性
	_attributesComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");

}

// Called when the game starts or when spawned
void AASCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}



void AASCharacter::Move(const FInputActionValue& Value)
{
	if (Controller == nullptr)
	{
		return;
	}
	const FVector2D MoveValue = Value.Get<FVector2D>();
	const FRotator MovementRotation(0, Controller->GetControlRotation().Yaw, 0);

	// Forward/Backward direction
	if (MoveValue.Y != 0.f)
	{
		// Get forward vector
		//const FVector Direction = MovementRotation.RotateVector(FVector::ForwardVector);
		//AddMovementInput(Direction, MoveValue.Y);

		AddMovementInput(MovementRotation.Vector(), MoveValue.Y);	//不定向控制器，不做方向过滤
	}

	// Right/Left direction
	if (MoveValue.X != 0.f)
	{
		// Get right vector
		const FVector Direction = MovementRotation.RotateVector(FVector::RightVector);

		AddMovementInput(Direction, MoveValue.X);
	}
}


void AASCharacter::Look(const FInputActionValue& Value)
{
	if (Controller == nullptr)
	{
		return;
	}
	const FVector2D LookValue = Value.Get<FVector2D>();

	// Pitch
	if (LookValue.Y != 0.f)
	{
		AddControllerPitchInput(LookValue.Y);
	}

	// Yaw
	if (LookValue.X != 0.f)
	{
		AddControllerYawInput(LookValue.X);
	}
}

void AASCharacter::PrimaryAttack(const FInputActionValue& Value)
{
	PlayAnimMontage(_attackAim);
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &AASCharacter::PrimaryAttack_TimeElapsed, 0.2f);

	//GetWorldTimerManager().ClearTimer(TimerHandle_PrimaryAttack);	//停止计时器
}

/// <summary>
/// 攻击计时器回调
/// </summary>
void AASCharacter::PrimaryAttack_TimeElapsed()
{
	FVector handLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	FTransform spawnTM = FTransform(this->GetControlRotation(), handLocation);

	FActorSpawnParameters spawnParmas;
	spawnParmas.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(_projectileClass, spawnTM, spawnParmas);
}

void AASCharacter::JumpCall(const FInputActionValue& Value)
{
	ACharacter::Jump();
}

void AASCharacter::Interaction(const FInputActionValue& Value)
{
	if (_interactionComp)
		_interactionComp->PrimaryInteract();
}

// Called every frame
void AASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Get the player controller
	APlayerController* PC = Cast<APlayerController>(GetController());

	// Get the local player subsystem
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());

	// Clear out existing mapping, and add our mapping
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	// Get the EnhancedInputComponent
	UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	// Bind the actions
	PEI->BindAction(InputMove, ETriggerEvent::Triggered, this, &AASCharacter::Move);
	PEI->BindAction(InputLook, ETriggerEvent::Triggered, this, &AASCharacter::Look);
	PEI->BindAction(InputAttack, ETriggerEvent::Triggered, this, &AASCharacter::PrimaryAttack);
	PEI->BindAction(InputJump, ETriggerEvent::Triggered, this, &AASCharacter::JumpCall);
	PEI->BindAction(InputInteraction, ETriggerEvent::Triggered, this, &AASCharacter::Interaction);
}