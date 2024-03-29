// Fill out your copyright notice in the Description page of Project Settings.


#include "SNObstacle.h"
#include "SpaceShootNumbers/Projectile/SNProjectile.h"
#include "SpaceShootNumbers/SpaceShootNumbers.h"
#include "SpaceShootNumbers/Game/SNGameModeBase.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include <Components/TextRenderComponent.h>
#include <Kismet/GameplayStatics.h>
#include "../PlayerUpgrade/SNPlayerUpgrade.h"

// Sets default values
ASNObstacle::ASNObstacle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Sphere component
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);
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

	// Projectile will be destroy after 30 seconds
	InitialLifeSpan = 30.0f;
}

void ASNObstacle::IncreaseHealthRange(int32 HealthRangeAdd)
{
	MinHealth += HealthRangeAdd;
	MaxHealth += HealthRangeAdd;
}

// Called when the game starts or when spawned
void ASNObstacle::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ASNObstacle::OnOverlapBegin);
	Health = FMath::RandRange(MinHealth, MaxHealth);
	StartHealth = Health;
	TextRenderComp->SetText(FText::FromString(FString::FromInt(Health)));

	ASNGameModeBase* MyGameMode = Cast<ASNGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (IsValid(MyGameMode))
	{
		MyGameMode->OnGameOverDelegate.AddDynamic(this, &ASNObstacle::HandleGameOver);
	}

	ChangeObstacleColor();
}

void ASNObstacle::OnOverlapBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASNProjectile* Projectile = Cast<ASNProjectile>(OtherActor);
	if (IsValid(Projectile))
	{
		int32 ProjectileDamage = Projectile->GetProjectileDamage();
		Projectile->Destroy();

		Health -= ProjectileDamage;
		Health = FMath::Max(Health, 0);
		TextRenderComp->SetText(FText::FromString(FString::FromInt(Health)));
		ChangeObstacleColor();
		if (Health <= 0)
		{
			ASNGameModeBase* MyGameMode = Cast<ASNGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
			if (IsValid(MyGameMode))
			{
				MyGameMode->PlayerScoreChanged(StartHealth);
			}
			SpawnUpgrade();

			if (DestroySound)
			{
				UGameplayStatics::PlaySound2D(GetWorld(), DestroySound, 1, 1, 0);
			}

			Destroy();
		}
	}
}

void ASNObstacle::HandleGameOver()
{
	MovementComp->StopMovementImmediately();
}

void ASNObstacle::SpawnUpgrade()
{
	float RandomChance = FMath::RandRange(0, 1);
	if (RandomChance <= ChangeToSpawn)
	{
		FActorSpawnParameters SpawnParameters;
		TSubclassOf<ASNPlayerUpgrade> SelectedPlayerUpgrade = UpgradeClassesToSpawn[FMath::RandRange(0, UpgradeClassesToSpawn.Num() - 1)];
		GetWorld()->SpawnActor<ASNPlayerUpgrade>(SelectedPlayerUpgrade, GetActorLocation(), GetActorRotation(), SpawnParameters);
	}
}
