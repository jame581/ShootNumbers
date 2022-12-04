// Fill out your copyright notice in the Description page of Project Settings.


#include "SNObstacle.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Components/TextRenderComponent.h>
#include "SpaceShootNumbers/Projectile/SNProjectile.h"
#include "SpaceShootNumbers/SpaceShootNumbers.h"

// Sets default values
ASNObstacle::ASNObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Sphere component
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetupAttachment(RootComponent);
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	//BoxComp->SetCollisionResponseToChannel(COLLISION_PROJECTILE, ECollisionResponse::ECR_Overlap);
	BoxComp->SetGenerateOverlapEvents(true);

	// Mesh component
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(BoxComp);

	// Mesh component
	TextRenderComp = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComp"));
	TextRenderComp->SetupAttachment(BoxComp);
	
	//Movement component
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	MovementComp->ProjectileGravityScale = 0;
	MovementComp->InitialSpeed = 1000;
	MovementComp->MaxSpeed = 2000;
	MovementComp->Velocity = FVector(-1, 0, 0);

	// Projectile will be destroy after 20 seconds
	InitialLifeSpan = 20.0f;
}

// Called when the game starts or when spawned
void ASNObstacle::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ASNObstacle::OnOverlapBegin);
	Health = FMath::RandRange(MinHealth, MaxHealth);
	TextRenderComp->SetText(FText::FromString(FString::FromInt(Health)));
}

void ASNObstacle::OnOverlapBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASNProjectile* Projectile = Cast<ASNProjectile>(OtherActor);
	if (IsValid(Projectile))
	{
		Projectile->Destroy();

		Health--;
		Health = FMath::Max(Health, 0);
		TextRenderComp->SetText(FText::FromString(FString::FromInt(Health)));
		
		if (Health <= 0)
		{
			Destroy();
		}
	}
}