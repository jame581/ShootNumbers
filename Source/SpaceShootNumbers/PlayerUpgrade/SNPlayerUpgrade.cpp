// Fill out your copyright notice in the Description page of Project Settings.


#include "SNPlayerUpgrade.h"
#include <Components/BoxComponent.h>
#include <Components/StaticMeshComponent.h>
#include "SpaceShootNumbers/Player/SNPawn.h"

// Sets default values
ASNPlayerUpgrade::ASNPlayerUpgrade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Sphere component
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetupAttachment(RootComponent);
	BoxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxComp->SetGenerateOverlapEvents(true);

	// Mesh component
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(BoxComp);

}

// Called when the game starts or when spawned
void ASNPlayerUpgrade::BeginPlay()
{
	Super::BeginPlay();
	
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ASNPlayerUpgrade::OnOverlapBegin);
}

void ASNPlayerUpgrade::OnOverlapBegin(class UPrimitiveComponent* newComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASNPawn* Player = Cast<ASNPawn>(OtherActor);
	if (IsValid(Player))
	{
		Destroy();
	}
}
