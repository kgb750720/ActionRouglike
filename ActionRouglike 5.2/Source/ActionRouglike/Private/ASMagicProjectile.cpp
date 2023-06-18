// Fill out your copyright notice in the Description page of Project Settings.


#include "ASMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "SAttributeComponent.h"

// Sets default values
AASMagicProjectile::AASMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	//sphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	//sphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	//sphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	sphereComp->SetCollisionProfileName("Projectile");
	//为属性组件添加伤害事件
	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &AASMagicProjectile::OnActionOverlap);
	RootComponent = RootComponent;

	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	movementComp->InitialSpeed = 1000.0f;
	movementComp->ProjectileGravityScale = 0.1f;
	movementComp->bRotationFollowsVelocity = true;
	movementComp->bInitialVelocityInLocalSpace = true;

	effectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	effectComp->SetupAttachment(sphereComp);

}

// Called when the game starts or when spawned
void AASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AASMagicProjectile::OnActionOverlap(UPrimitiveComponent* OverlappedComponent
	, AActor* OtherActor
	, UPrimitiveComponent* OtherComp
	, int32 OtherBodyIndex, bool bFromSweep
	, const FHitResult& SweepResult)
{
	if (OtherActor == nullptr)
		return;
	USAttributeComponent* attributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
	if (attributeComp == nullptr)
		return;
	attributeComp->ApplyHeathChange(-20.0f);
	Destroy();
}

// Called every frame
void AASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

