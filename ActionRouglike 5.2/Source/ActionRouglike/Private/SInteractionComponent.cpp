// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"
#include "SGmaeplayInterface.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams objectQueryParams;
	objectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* myOwner = GetOwner();

	FVector eyeLocation;
	FRotator eyeRotation;

	myOwner->GetActorEyesViewPoint(eyeLocation, eyeRotation);

	FVector end = eyeLocation + (eyeRotation.Vector() * 1000);	//����յ�����

	/*����������*/
	//FHitResult hit;
	//bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(hit,eyeLocation,end, objectQueryParams);	//���߼��
	//if (AActor* hitActor = hit.GetActor(); hitActor != nullptr && hitActor->Implements<USGmaeplayInterface>())
	//{
	//	APawn* myPawn = Cast<APawn>(myOwner);
	//	ISGmaeplayInterface::Execute_Interact(hitActor, myPawn);
	//}

	//FColor lineColor = bBlockingHit ? FColor::Green : FColor::Red;
	//DrawDebugLine(GetWorld(), eyeLocation, end, lineColor, false, 2.0f, 0, 2.0f);


	/*���������*/
	TArray<FHitResult> hits;
	FCollisionShape shape;
	float radius = 30.0f;
	shape.SetSphere(radius);
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(hits, eyeLocation, end,FQuat::Identity ,objectQueryParams,shape);
	FColor sphereColor = bBlockingHit ? FColor::Green : FColor::Red;
	for (auto& hit : hits)
	{
		DrawDebugSphere(GetWorld(), hit.ImpactPoint, radius, 32/*����*/, sphereColor, false, 2.0f);
		if (AActor* hitActor = hit.GetActor(); hitActor != nullptr && hitActor->Implements<USGmaeplayInterface>())
		{
			APawn* myPawn = Cast<APawn>(myOwner);
			ISGmaeplayInterface::Execute_Interact(hitActor, myPawn);
			break;
		}
	}
	FColor lineColor = bBlockingHit ? FColor::Green : FColor::Red;
	DrawDebugLine(GetWorld(), eyeLocation, end, lineColor, false, 2.0f, 0, 2.0f);
	
}
