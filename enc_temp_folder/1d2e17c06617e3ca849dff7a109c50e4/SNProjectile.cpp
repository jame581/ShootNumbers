// Fill out your copyright notice in the Description page of Project Settings.


#include "SNProjectile.h"
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
//#include <ProjectileMovementComponent.h>

// Sets default values
ASNProjectile::ASNProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Sphere component
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetupAttachment(RootComponent);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	// Mesh component
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(SphereComp);

	//Movement component
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));

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
