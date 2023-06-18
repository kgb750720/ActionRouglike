// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ASMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class ACTIONROUGLIKE_API AASMagicProjectile : public AActor
{
	GENERATED_BODY()
	

public:	
	UPROPERTY(VisibleAnywhere)
		USphereComponent* sphereComp;

	UPROPERTY(VisibleAnywhere)
		UProjectileMovementComponent* movementComp;

	UPROPERTY(VisibleAnywhere)
		UParticleSystemComponent* effectComp;

	// Sets default values for this actor's properties
	AASMagicProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//参数获取 OnComponentBeginOverlap -> 定义 -> 定义 从 OnComponentBeginOverlap 后面参数复制过来，删掉宏格式中的多余,即为绑定参数
	void OnActionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
