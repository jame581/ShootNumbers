// Fill out your copyright notice in the Description page of Project Settings.


#include "SNProjectile.h"
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include "SpaceShootNumbers/SpaceShootNumbers.h"

// Sets default values
ASNProjectile::ASNProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Sphere component
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetupAttachment(RootComponent);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SphereComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	//SphereComp->SetCollisionResponseToChannel(COLLISION_PROJECTILE, ECollisionResponse::ECR_Overlap);
	SphereComp->SetGenerateOverlapEvents(true);
	SphereComp->SetSphereRadius(26.0f);

	// Mesh component
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(SphereComp);

	//Movement component
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	MovementComp->InitialSpeed = 1000;
	MovementComp->MaxSpeed = 2000;
	MovementComp->ProjectileGravityScale = 0;

	// Projectile will be destroy after 5 seconds
	InitialLifeSpan = 5.0f;
}

// Called when the game starts or when spawned
void ASNProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASNProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

