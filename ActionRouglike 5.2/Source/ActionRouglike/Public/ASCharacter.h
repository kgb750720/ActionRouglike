// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "ASCharacter.generated.h"

UCLASS()
class ACTIONROUGLIKE_API AASCharacter : public ACharacter
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, Category = "Attack")
		TSubclassOf<AActor> _projectileClass;
	UPROPERTY(EditAnywhere, Category = "Attack")
		class UAnimMontage* _attackAim;

	FTimerHandle TimerHandle_PrimaryAttack;	//攻击计时器引用
public:
	// Sets default values for this character's properties
	AASCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	class USInteractionComponent* _interactionComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "Components")
	class USAttributeComponent* _attributesComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputAction* InputMove;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* InputLook;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* InputAttack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* InputJump;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* InputInteraction;


	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void PrimaryAttack(const FInputActionValue& Value);
	
	void PrimaryAttack_TimeElapsed();

	void JumpCall(const FInputActionValue& Value);

	void Interaction(const FInputActionValue& Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
