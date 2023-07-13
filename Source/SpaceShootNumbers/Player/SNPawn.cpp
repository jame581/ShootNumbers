// Fill out your copyright notice in the Description page of Project Settings.


#include "SNPawn.h"
#include "SpaceShootNumbers/Obstacle/SNObstacle.h"
#include "SpaceShootNumbers/PlayerUpgrade/SNUpgradeInfo.h"
#include "SNPlayerController.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/FloatingPawnMovement.h>
#include <Components/StaticMeshComponent.h>
#include <Components/SceneComponent.h>
#include <Components/BoxComponent.h>
#include <Engine/World.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
ASNPawn::ASNPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	MinimumRateOfFire = 0.5f;
	ProjectileDamage = 1;
	
	// Sphere component
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("SphereComp"));
	BoxComp->SetupAttachment(RootComponent);
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxComp->SetGenerateOverlapEvents(true);

	// Mesh component
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(BoxComp);

	// Spring arm component
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(BoxComp);
	SpringArmComp->TargetArmLength = 400.0f;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->CameraLagSpeed = 1.0f;

	// Camera component
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	// Projectile start position component
	ProjectileStartPosition = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileStartPosition"));
	ProjectileStartPosition->SetupAttachment(BoxComp);
	ProjectileStartPosition->SetVisibility(false);
	ProjectileStartPosition->SetComponentTickEnabled(false);

	//Movement component
	MovementComp = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComp"));
}

// Called when the game starts or when spawned
void ASNPawn::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ASNPawn::OnOverlapBegin);

	StartFire();
}

void ASNPawn::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void ASNPawn::StartFire()
{
	float firstDelay = FMath::Max((LastFireTime + RateOfFire) - GetWorld()->TimeSeconds, 0.f);
  	GetWorldTimerManager().SetTimer(TimerHandle_TimeBetweenShots, this, &ASNPawn::Fire, RateOfFire, true, firstDelay);
}

void ASNPawn::StopFire()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_TimeBetweenShots);
}

void ASNPawn::Fire()
{
	// Spawn a default weapon
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AActor* ActorProjectile = GetWorld()->SpawnActor(StarterProjectileClass, &ProjectileStartPosition->GetComponentTransform(), spawnParams);

	if (IsValid(ActorProjectile))
	{
		ASNProjectile* NewProjectile = Cast<ASNProjectile>(ActorProjectile);
		if (IsValid(NewProjectile))
		{
			NewProjectile->SetProjectileDamage(ProjectileDamage);
		}
	}

	LastFireTime = GetWorld()->TimeSeconds;

	if (ShootSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), ShootSound, 1, 1, 0);
	}
}

void ASNPawn::Death()
{
	ASNPlayerController* PlayerController = GetController<ASNPlayerController>();
	if (IsValid(PlayerController))
	{
		DisableInput(PlayerController);
		StopFire();

		PlayerController->PlayerDeath();
	}
}

void ASNPawn::OnOverlapBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASNObstacle* Obstacle = Cast<ASNObstacle>(OtherActor);
	if (IsValid(Obstacle))
	{
		Obstacle->Destroy();		
		Death();
	}
}

// Called to bind functionality to input
void ASNPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Axis for movement
	PlayerInputComponent->BindAxis("MoveRight", this, &ASNPawn::MoveRight);
}

void ASNPawn::ApplyUpgrade(FSNUpgradeInfo UpgradeInfo)
{
	switch (UpgradeInfo.UpgradeType)
	{
	case EUpgradeType::FireRate:
		UpgradeFireRate(UpgradeInfo.RateOfFire);
		break;

	case EUpgradeType::DamageUpdate:
		UpgradeDamage(UpgradeInfo.PlayerDamage);
		break;
	}

	ASNPlayerController* PlayerController = GetController<ASNPlayerController>();
	if (IsValid(PlayerController))
	{
		PlayerController->PlayerUpgradeApplied(UpgradeInfo);
	}
}

void ASNPawn::UpgradeFireRate(float FireRateUpgrade)
{
	RateOfFire -= FireRateUpgrade;

	if (RateOfFire < MinimumRateOfFire)
	{
		RateOfFire = MinimumRateOfFire;
	}

	StopFire();
	StartFire();
}

void ASNPawn::UpgradeDamage(int32 NewDamage)
{
	ProjectileDamage += NewDamage;
}
