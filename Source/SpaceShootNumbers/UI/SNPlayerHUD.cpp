// Fill out your copyright notice in the Description page of Project Settings.


#include "SNPlayerHUD.h"
#include "SpaceShootNumbers/Game/SNGameModeBase.h"
#include <UMG/Public/Components/TextBlock.h>
#include <Kismet/GameplayStatics.h>

void USNPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerScore = 0;
	PlayTimeInSeconds = 0;

	if (IsValid(ScoreLabel))
	{
		ScoreLabel->SetText(FText::FromString(TEXT("0")));
	}

	if (IsValid(TimeLabel))
	{
		TimeLabel->SetText(FText::FromString(TEXT("00:00:00")));
	}

	GetWorld()->GetTimerManager().SetTimer(ElapsedTimeHandle, this, &USNPlayerHUD::UpdateUITime, 1.0f, true, 2.0f);

	ASNGameModeBase* MyGameMode = Cast<ASNGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (IsValid(MyGameMode))
	{
		MyGameMode->OnPlayerScoreChangedDelegate.AddDynamic(this, &USNPlayerHUD::AddPlayerScore);
		MyGameMode->OnGameOverDelegate.AddDynamic(this, &USNPlayerHUD::HandleGameOver);
	}
}

void USNPlayerHUD::UpdateUITime()
{
	PlayTimeInSeconds++;

	FTimespan CurrentPlayTime = FTimespan::FromSeconds(PlayTimeInSeconds);

	if (IsValid(TimeLabel))
	{
		FString TimeString = FString::Printf(TEXT("%02d:%02d:%02d"), CurrentPlayTime.GetHours(), CurrentPlayTime.GetMinutes(), CurrentPlayTime.GetSeconds());
		TimeLabel->SetText(FText::FromString(TimeString));
	}
}

void USNPlayerHUD::UpdatePlayerScore()
{
	if (IsValid(ScoreLabel))
	{
		FString PlayerScoreString = FString::FromInt(PlayerScore);
		ScoreLabel->SetText(FText::FromString(PlayerScoreString));
	}
}

void USNPlayerHUD::HandleGameOver()
{
	GetWorld()->GetTimerManager().ClearTimer(ElapsedTimeHandle);
}

void USNPlayerHUD::AddPlayerScore(int32 AddScore)
{
	PlayerScore += AddScore;
	UpdatePlayerScore();
}

int32 USNPlayerHUD::GetPlayerScore() const
{
	return PlayerScore;
}

int32 USNPlayerHUD::GetPlayTimeInSecods() const
{
	return PlayTimeInSeconds;
}
