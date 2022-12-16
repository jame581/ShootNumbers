// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SNSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHOOTNUMBERS_API USNSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	USNSaveGame();
		
public: // Properties

	UPROPERTY(VisibleAnywhere, Category = "Save Info")
	FString PlayerName;

	UPROPERTY(VisibleAnywhere, Category = "Save Info")
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = "Save Info")
	uint32 UserIndex;

	UPROPERTY(VisibleAnywhere, Category = "Save Info")
	int32 PlayerScore;
	
	UPROPERTY(VisibleAnywhere, Category = "Save Info")
	int32 PlayTimeInSeconds;
};
