// Fill out your copyright notice in the Description page of Project Settings.


#include "SNObstacleGenerator.h"
#include "SNObstacle.h"
#include "Kismet/GameplayStatics.h"
#include "SpaceShootNumbers/Game/SNGameModeBase.h"
#include "SpaceShootNumbers/Player/SNPlayerController.h"
#include "SpaceShootNumbers/Player/SNPawn.h"
#include "SpaceShootNumbers/PlayerUpgrade/SNUpgradeInfo.h"

// Sets default values
ASNObstacleGenerator::ASNObstacleGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StartDelay = 1.f;
	MinDelayBetweenSpawn = 2.f;
	MaxDelayBetweenSpawn = 5.f;
	HealthRangeAdd = 0;
	DifficultyRaiseValue = 2;
	DifficultyRaiseOnPlayerUpgrade = 2;
	DifficultyRaiseInterval = 10.f;
}

// Called when the game starts or when spawned
void ASNObstacleGenerator::BeginPlay()
{
	Super::BeginPlay();

	ASNGameModeBase* MyGameMode = Cast<ASNGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (IsValid(MyGameMode))
	{
		MyGameMode->OnGameOverDelegate.AddDynamic(this, &ASNObstacleGenerator::HandleGameOver);
		MyGameMode->OnPlayerUpgraded.AddDynamic(this, &ASNObstacleGenerator::UpgradeApplied);
	}

	GetWorldTimerManager().SetTimer(TimerHandle_IncreaseDifficulty, this, &ASNObstacleGenerator::RaiseDifficulty, DifficultyRaiseInterval, true, 10.f);
}

void ASNObstacleGenerator::SpawnNewWave()
{
	CreateObstacleChunk();
	FinishSpawnObstacleChunk();
	int32 NextSpawn = FMath::RandRange(MinDelayBetweenSpawn, MaxDelayBetweenSpawn);
	GetWorldTimerManager().SetTimer(TimerHandle_TimeBetweenSpawn, this, &ASNObstacleGenerator::SpawnNewWave, NextSpawn, false);
}


void ASNObstacleGenerator::StartSpawnObstacles()
{	
	GetWorldTimerManager().SetTimer(TimerHandle_TimeBetweenSpawn, this, &ASNObstacleGenerator::SpawnNewWave, StartDelay, false);
}

void ASNObstacleGenerator::StopSpawnObstacles()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_TimeBetweenSpawn);
	GetWorldTimerManager().ClearTimer(TimerHandle_IncreaseDifficulty);
}

void ASNObstacleGenerator::CreateObstacleChunk()
{
	ObstacleChunk.Empty(9);

	FTransform TransformToSpawn = SpawnPoint->GetActorTransform();
	FVector NewSpawnLocation = TransformToSpawn.GetLocation();

	for (int32 i = 0; i < 9; i++)
	{
		ASNObstacle* Obstacle = GetWorld()->SpawnActorDeferred<ASNObstacle>(ClassToSpawn, TransformToSpawn);

		if (IsValid(Obstacle))
		{
			ObstacleChunk.Add(Obstacle);
			NewSpawnLocation.Y += 100.f;
			TransformToSpawn.SetLocation(NewSpawnLocation);
			Obstacle->IncreaseHealthRange(HealthRangeAdd);
		}
	}
}

void ASNObstacleGenerator::FinishSpawnObstacleChunk()
{
	for (auto& ObstacleToSpawn : ObstacleChunk)
	{
		UGameplayStatics::FinishSpawningActor(ObstacleToSpawn, ObstacleToSpawn->GetActorTransform());
	}
}

void ASNObstacleGenerator::HandleGameOver()
{
	StopSpawnObstacles();
}

void ASNObstacleGenerator::RaiseDifficulty()
{
	HealthRangeAdd += DifficultyRaiseValue;
}

void ASNObstacleGenerator::UpgradeApplied(FSNUpgradeInfo UpgradeInfo)
{
	switch (UpgradeInfo.UpgradeType)
	{
	case FireRate:
	case DamageUpdate:
		DifficultyRaiseValue += DifficultyRaiseOnPlayerUpgrade;
		break;
	}
}
