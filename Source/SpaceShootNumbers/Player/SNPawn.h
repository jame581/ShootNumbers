// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <Engine/EngineTypes.h>
#include "SpaceShootNumbers/Projectile/SNProjectile.h"
#include "SNPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UStaticMeshComponent;
class USphereComponent;
class UFloatingPawnMovement;
class USceneComponent;

struct FHitResult;

UCLASS()
class SPACESHOOTNUMBERS_API ASNPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASNPawn();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveRight(float Value);

	void StartFire();

	void StopFire();
	
	void Fire();

	void Death();

	UFUNCTION()
	virtual void OnOverlapBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected: // Components

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UFloatingPawnMovement* MovementComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* ProjectileStartPosition;

protected: // Properties

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile Fire")
	float RateOfFire;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile Fire")
	TSubclassOf<ASNProjectile> StarterProjectileClass;

	FTimerHandle TimerHandle_TimeBetweenShots;

	float LastFireTime;
};
