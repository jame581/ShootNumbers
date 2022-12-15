// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SNSaveGameSubsystem.generated.h"

class USNSaveGame;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnSaveGameFinished, const FString&, SlotName, const int32, UserIndex, bool, bSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoadGameFinished, USNSaveGame*, LoadedGameData);


/**
 * Save and load game data subsystem
 */
UCLASS()
class SPACESHOOTNUMBERS_API USNSaveGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

	// Begin USubsystem overrides
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;
	
	// End USubsystem

	UFUNCTION(BlueprintCallable)
	virtual void SaveGame(int32 PlayerScore, int32 PlayTimeInSeconds, int32 UserIndex = -1);

	UFUNCTION(BlueprintCallable)
	virtual void LoadGame();

private:

	UFUNCTION()
	void SaveGameFinished(const FString& SlotName, const int32 UserIndex, bool bSuccess);
	
	UFUNCTION()
	void LoadGameFinished(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData);


public: // Delegates

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnSaveGameFinished OnSaveGameFinished;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnLoadGameFinished OnLoadGameFinished;
};
