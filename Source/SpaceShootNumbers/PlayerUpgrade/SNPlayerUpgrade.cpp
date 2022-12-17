// Fill out your copyright notice in the Description page of Project Settings.


#include "SNPlayerUpgrade.h"
#include "SpaceShootNumbers/Player/SNPawn.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
ASNPlayerUpgrade::ASNPlayerUpgrade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Sphere component
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetupAttachment(RootComponent);
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxComp->SetGenerateOverlapEvents(true);

	// Mesh component
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(BoxComp);

	//Movement component
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	MovementComp->ProjectileGravityScale = 0;
	MovementComp->InitialSpeed = 1000;
	MovementComp->MaxSpeed = 1000;
	MovementComp->Velocity = FVector(-1, 0, 0);

	// Upgrade will be destroy after 30 seconds
	InitialLifeSpan = 30.0f;
}

// Called when the game starts or when spawned
void ASNPlayerUpgrade::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ASNPlayerUpgrade::OnOverlapBegin);
}

void ASNPlayerUpgrade::OnOverlapBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASNPawn* Player = Cast<ASNPawn>(OtherActor);
	if (IsValid(Player))
	{
		Player->ApplyUpgrade(UpgradeInfo);

		if (PickUpSound)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), PickUpSound, 0.8, 1, 0);
		}

		Destroy();
	}
}
