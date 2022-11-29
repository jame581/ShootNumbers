// Fill out your copyright notice in the Description page of Project Settings.


#include "SNPawn.h"

// Sets default values
ASNPawn::ASNPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASNPawn::BeginPlay()
{
	Super::BeginPlay();
	
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

}

