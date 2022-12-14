// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SNPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHOOTNUMBERS_API ASNPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:

	//UFUNCTION()
	//virtual void HandleGameOver(int32 InPlayTimeInSecods, int32 InPlayerScore);

	UFUNCTION()
	virtual void PlayerDeath();

	UFUNCTION(BlueprintCallable)
	int32 GetPlayerScore() const;

	UFUNCTION(BlueprintCallable)
	int32 GetPlayTimeInSecods() const;

	UFUNCTION(BlueprintCallable)
	FString GetPlayTimeInSecodsFormatted() const;

private: // Properties

	int32 PlayerScore;

	int32 PlayTimeInSecods;
};
