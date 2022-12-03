// Fill out your copyright notice in the Description page of Project Settings.


#include "SNPawn.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <Components/SphereComponent.h>
#include <GameFramework/FloatingPawnMovement.h>
#include <Components/StaticMeshComponent.h>

// Sets default values
ASNPawn::ASNPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Sphere component
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetupAttachment(RootComponent);
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	
	// Mesh component
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(SphereComp);

	// Spring arm component
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(SphereComp);
	SpringArmComp->TargetArmLength = 400.0f;
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->CameraLagSpeed = 1.0f;
	//SpringArmComp->bUsePawnControlRotation = true;

	// Camera component
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);

	//Movement component
	MovementComp = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComp"));
}

// Called when the game starts or when spawned
void ASNPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASNPawn::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

// Called every frame
void ASNPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASNPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Axis for movement
	PlayerInputComponent->BindAxis("MoveRight", this, &ASNPawn::MoveRight);

	// Jump action
	//PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASNPawn::Jump);
}

