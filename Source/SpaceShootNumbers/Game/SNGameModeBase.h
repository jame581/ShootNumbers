// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpaceShootNumbers/PlayerUpgrade/SNUpgradeInfo.h"
#include "SNGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameOver);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerScoreChanged, int32, AddScore);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerUpgraded, FSNUpgradeInfo, UpgradeInfo);

/**
 * Space shoot number game mode base 
 */
UCLASS()
class SPACESHOOTNUMBERS_API ASNGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	UFUNCTION()
	virtual void GameOver();

	UFUNCTION()
	virtual void PlayerScoreChanged(int32 AddScore);

	UFUNCTION()
	void UpgradeApplied(FSNUpgradeInfo UpgradeInfo);

public:

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnGameOver OnGameOverDelegate;	

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnPlayerScoreChanged OnPlayerScoreChangedDelegate;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnPlayerUpgraded OnPlayerUpgraded;
};
