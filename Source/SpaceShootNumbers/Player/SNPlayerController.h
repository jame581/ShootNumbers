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

	void LoadInGameUI();

	void ShowGameOverUI();

	void ShowInGameUI();
	
public:

	UFUNCTION()
	virtual void PlayerDeath();

	UFUNCTION(BlueprintCallable)
	int32 GetPlayerScore() const;

	UFUNCTION(BlueprintCallable)
	int32 GetPlayTimeInSecods() const;

	UFUNCTION(BlueprintCallable)
	FString GetPlayTimeInSecodsFormatted() const;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class USNPlayerHUD> InGameUIClass;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	class USNPlayerHUD* InGameUI;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> GameOverUIClass;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	class UUserWidget* GameOverUI;

private: // Properties

	int32 PlayerScore;

	int32 PlayTimeInSecods;
};
