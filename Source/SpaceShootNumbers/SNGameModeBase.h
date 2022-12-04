// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SNGameModeBase.generated.h"

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameOver, bool, bGameOver);

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

public:

	FOnGameOver OnGameOverDelegate;
	
};
