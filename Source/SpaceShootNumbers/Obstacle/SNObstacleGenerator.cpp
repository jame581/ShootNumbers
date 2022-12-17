// Fill out your copyright notice in the Description page of Project Settings.


#include "SNObstacleGenerator.h"
#include "SNObstacle.h"
#include "Kismet/GameplayStatics.h"
#include "SpaceShootNumbers/Game/SNGameModeBase.h"

// Sets default values
ASNObstacleGenerator::ASNObstacleGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StartDelay = 1.f;
	MinDelayBetweenSpawn = 2.f;
	MaxDelayBetweenSpawn = 5.f;
}

// Called when the game starts or when spawned
void ASNObstacleGenerator::BeginPlay()
{
	Super::BeginPlay();

	ASNGameModeBase* MyGameMode = Cast<ASNGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (IsValid(MyGameMode))
	{
		MyGameMode->OnGameOverDelegate.AddDynamic(this, &ASNObstacleGenerator::HandleGameOver);
	}
}

// Called every frame
void ASNObstacleGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
