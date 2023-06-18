// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGmaeplayInterface.h"
#include "SItemChestActor.generated.h"
class UStaticMeshComponent;

UCLASS()
class ACTIONROUGLIKE_API ASItemChestActor : public AActor, public ISGmaeplayInterface
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere)
		float _targetPitch;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* _baseMesh;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* _lidMesh;
	// Sets default values for this actor's properties
	ASItemChestActor();

	void Interact_Implementation(APawn* InstigatorPawn);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
