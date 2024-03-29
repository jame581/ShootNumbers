// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SNObstacle.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;
class UTextRenderComponent;
class UPrimitiveComponent;
class ASNPlayerUpgrade;
class USoundBase;

UCLASS()
class SPACESHOOTNUMBERS_API ASNObstacle : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	ASNObstacle();

	void IncreaseHealthRange(int32 HealthRangeAdd);

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnOverlapBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void HandleGameOver();

	UFUNCTION(BlueprintImplementableEvent)
	void ChangeObstacleColor();

	UFUNCTION(BlueprintCallable)
	void SpawnUpgrade();

protected: // Components

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* BoxComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UTextRenderComponent* TextRenderComp;

protected: // Properties

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Obstacle Properties")
	int32 Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Obstacle Properties")
	int32 MinHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Obstacle Properties")
	int32 MaxHealth;

	UPROPERTY(BlueprintReadOnly, Category = "Obstacle Properties")
	int32 StartHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Obstacle Properties")
	USoundBase* DestroySound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Obstacle Player Upgrade", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float ChangeToSpawn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Obstacle Player Upgrade")
	TArray<TSubclassOf<ASNPlayerUpgrade>> UpgradeClassesToSpawn;
};
