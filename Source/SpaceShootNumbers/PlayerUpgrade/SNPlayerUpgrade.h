// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SNUpgradeInfo.h"
#include "SNPlayerUpgrade.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UProjectileMovementComponent;

UCLASS()
class SPACESHOOTNUMBERS_API ASNPlayerUpgrade : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	ASNPlayerUpgrade();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnOverlapBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected: // Components

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* BoxComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UProjectileMovementComponent* MovementComp;

protected: // Properties

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile Fire")
	FSNUpgradeInfo UpgradeInfo;
};
