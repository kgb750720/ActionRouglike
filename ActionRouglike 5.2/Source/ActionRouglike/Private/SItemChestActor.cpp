// Fill out your copyright notice in the Description page of Project Settings.


#include "SItemChestActor.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ASItemChestActor::ASItemChestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(_TEXT("BaseMesh"));
	RootComponent = _baseMesh;

	_lidMesh = CreateDefaultSubobject<UStaticMeshComponent>(_TEXT("LidMesh"));
	_lidMesh->SetupAttachment(_baseMesh);

	_targetPitch = 110;
}


void ASItemChestActor::Interact_Implementation(APawn* InstigatorPawn)
{
	_lidMesh->SetRelativeRotation(FRotator(_targetPitch, 0, 0));
}

// Called when the game starts or when spawned
void ASItemChestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASItemChestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

