// Fill out your copyright notice in the Description page of Project Settings.


#include "SNPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "SpaceShootNumbers/SNGameModeBase.h"
#include <GameFramework/PlayerController.h>

void ASNPlayerController::PlayerDeath()
{
	ASNGameModeBase* MyGameMode = Cast<ASNGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (IsValid(MyGameMode))
	{
		MyGameMode->GameOver();
		DisableInput(this);
	}
}
