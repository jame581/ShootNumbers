// Fill out your copyright notice in the Description page of Project Settings.


#include "SNGameModeBase.h"

void ASNGameModeBase::GameOver()
{
	OnGameOverDelegate.Broadcast();
}

void ASNGameModeBase::PlayerScoreChanged(int32 AddScore)
{
	OnPlayerScoreChangedDelegate.Broadcast(AddScore);
}

void ASNGameModeBase::UpgradeApplied(FSNUpgradeInfo UpgradeInfo)
{
	OnPlayerUpgraded.Broadcast(UpgradeInfo);
}
