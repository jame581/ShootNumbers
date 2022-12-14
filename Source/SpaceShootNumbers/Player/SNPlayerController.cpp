// Fill out your copyright notice in the Description page of Project Settings.


#include "SNPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "SpaceShootNumbers/SNGameModeBase.h"
#include <GameFramework/PlayerController.h>

void ASNPlayerController::BeginPlay()
{
	//ASNGameModeBase* MyGameMode = Cast<ASNGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	//if (IsValid(MyGameMode))
	//{
	//	MyGameMode->OnGameOverDelegate.AddDynamic(this, &ASNPlayerController::HandleGameOver);
	//}
}

//void ASNPlayerController::HandleGameOver()
//{
//	//PlayerDeath();
//
//	//PlayerScore = InPlayerScore;
//	//PlayTimeInSecods = InPlayTimeInSecods;
//}

void ASNPlayerController::PlayerDeath()
{
	ASNGameModeBase* MyGameMode = Cast<ASNGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (IsValid(MyGameMode))
	{
		MyGameMode->GameOver();
		DisableInput(this);
	}
}

int32 ASNPlayerController::GetPlayerScore() const
{
	return PlayerScore;
}

int32 ASNPlayerController::GetPlayTimeInSecods() const
{
	return PlayTimeInSecods;
}

FString ASNPlayerController::GetPlayTimeInSecodsFormatted() const
{
	FTimespan CurrentPlayTime = FTimespan::FromSeconds(PlayTimeInSecods);
	return FString::Printf(TEXT("%02d:%02d:%02d"), CurrentPlayTime.GetHours(), CurrentPlayTime.GetMinutes(), CurrentPlayTime.GetSeconds());
}
