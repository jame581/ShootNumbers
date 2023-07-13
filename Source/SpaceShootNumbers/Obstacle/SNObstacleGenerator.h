// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SNObstacleGenerator.generated.h"

class ASNObstacle;

UCLASS()
class SPACESHOOTNUMBERS_API ASNObstacleGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASNObstacleGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintCallable)
	virtual void SpawnNewWave();

	UFUNCTION(BlueprintCallable)
	virtual void StartSpawnObstacles();

	UFUNCTION(BlueprintCallable)
	virtual void StopSpawnObstacles();

protected:

	virtual void CreateObstacleChunk();

	virtual void FinishSpawnObstacleChunk();

	UFUNCTION()
	virtual void HandleGameOver();

	virtual void RaiseDifficulty();

	UFUNCTION()
	void UpgradeApplied(FSNUpgradeInfo UpgradeInfo);

protected: // Properties

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Obstacle Generator Properties")
	float StartDelay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Obstacle Generator Properties")
	float MinDelayBetweenSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Obstacle Generator Properties")
	float MaxDelayBetweenSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Obstacle Generator Properties", meta = (ClampMin = "5.0", ClampMax = "50.0", UIMin = "5.0", UIMax = "50.0"))
	float DifficultyRaiseInterval;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Obstacle Generator Properties", meta = (ClampMin = "1", ClampMax = "100", UIMin = "1", UIMax = "100"))
	int32 DifficultyRaiseValue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Obstacle Generator Properties", meta = (ClampMin = "1", ClampMax = "100", UIMin = "1", UIMax = "100"))
	int32 DifficultyRaiseOnPlayerUpgrade;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Obstacle Generator Properties")
	AActor* SpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Obstacle Generator Properties")
	TSubclassOf<ASNObstacle> ClassToSpawn;

private:

	FTimerHandle TimerHandle_TimeBetweenSpawn;

	FTimerHandle TimerHandle_IncreaseDifficulty;

	TArray<ASNObstacle*> ObstacleChunk;

	int32 HealthRangeAdd;
};
