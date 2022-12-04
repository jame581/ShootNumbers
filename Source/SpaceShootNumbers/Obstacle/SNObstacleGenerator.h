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
	// Called every frame
	virtual void Tick(float DeltaTime) override;

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
	virtual void HandleGameOver(bool bGameOver);

protected: // Properties

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Obstacle Generator Properties")
	float StartDelay;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Obstacle Generator Properties")
	float MinDelayBetweenSpawn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Obstacle Generator Properties")
	float MaxDelayBetweenSpawn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Obstacle Generator Properties")
	AActor* SpawnPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Obstacle Generator Properties")
	TSubclassOf<ASNObstacle> ClassToSpawn;

private:

	FTimerHandle TimerHandle_TimeBetweenSpawn;

	TArray<ASNObstacle*> ObstacleChunk;
};
