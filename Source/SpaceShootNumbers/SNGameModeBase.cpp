// Fill out your copyright notice in the Description page of Project Settings.


#include "SNGameModeBase.h"

void ASNGameModeBase::GameOver()
{
	OnGameOverDelegate.Broadcast(true);
}

void ASNGameModeBase::PlayerScoreChanged(int32 NewPlayerScore)
{
	OnPlayerScoreChangedDelegate.Broadcast(NewPlayerScore);
}
