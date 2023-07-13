// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SpaceShootNumbers/PlayerUpgrade/SNUpgradeInfo.h"
#include "SNPlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class SPACESHOOTNUMBERS_API USNPlayerHUD : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

	virtual void UpdateUITime();

	virtual void UpdatePlayerScore();

	UFUNCTION()
	virtual void HandleGameOver();

public:

	UFUNCTION(BlueprintCallable)
	void AddPlayerScore(int32 AddScore);

	UFUNCTION(BlueprintCallable)
	void UpdatePlayerDamage(int32 PlayerDamageIncrease);

	UFUNCTION(BlueprintCallable)
	int32 GetPlayerScore() const;

	UFUNCTION(BlueprintCallable)
	int32 GetPlayerDamage() const;

	UFUNCTION(BlueprintCallable)
	int32 GetPlayTimeInSecods() const;

	UFUNCTION(BlueprintImplementableEvent)
	void UpgradeApplied(FSNUpgradeInfo UpgradeInfo);

protected: // Properties

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ScoreLabel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TimeLabel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* DamageLabel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* UpgradeInfoLabel;
	
	UPROPERTY(BlueprintReadOnly)
	int32 PlayerScore;
			
	UPROPERTY(BlueprintReadOnly)
	int32 PlayerDamage;

	UPROPERTY(BlueprintReadOnly)
	int32 PlayTimeInSeconds;

private:

	FTimerHandle ElapsedTimeHandle;
};
