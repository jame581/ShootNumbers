// Fill out your copyright notice in the Description page of Project Settings.


#include "SNPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "SpaceShootNumbers/Game/SNGameModeBase.h"
#include "SpaceShootNumbers/UI/SNPlayerHUD.h"
#include <GameFramework/PlayerController.h>
#include <UMG/Public/Blueprint/UserWidget.h>

void ASNPlayerController::BeginPlay()
{
	PlayerScore = 0;
	PlayTimeInSecods = 0;

	LoadInGameUI();
	ShowInGameUI();
}

void ASNPlayerController::LoadInGameUI()
{
	if (IsValid(InGameUIClass))
	{
		InGameUI = CreateWidget<USNPlayerHUD>(this, InGameUIClass);
	}

	if (IsValid(GameOverUIClass))
	{
		GameOverUI = CreateWidget<UUserWidget>(this, GameOverUIClass);
	}
}

void ASNPlayerController::ShowGameOverUI()
{
	if (IsValid(GameOverUI))
	{
		GameOverUI->AddToViewport();
	}
}

void ASNPlayerController::ShowInGameUI()
{
	if (IsValid(InGameUI))
	{
		InGameUI->AddToViewport();
	}
}

void ASNPlayerController::PlayerDeath()
{
	ASNGameModeBase* MyGameMode = Cast<ASNGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (IsValid(MyGameMode))
	{
		MyGameMode->GameOver();
		DisableInput(this);
	}

	if (IsValid(InGameUI))
	{
		PlayerScore = InGameUI->GetPlayerScore();
		PlayTimeInSecods = InGameUI->GetPlayTimeInSecods();
	}

	ShowGameOverUI();
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
