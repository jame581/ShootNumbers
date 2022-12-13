// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
	virtual void HandleGameOver(bool bGameOver);

public:

	UFUNCTION(BlueprintCallable)
	void SetPlayerScore(int32 NewPlayerScore);

	UFUNCTION(BlueprintCallable)
	int32 GetPlayTimeInSecods();

protected: // Properties

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ScoreLabel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* TimeLabel;
	
	UPROPERTY(BlueprintReadOnly)
	int32 PlayerScore;

	UPROPERTY(BlueprintReadOnly)
	int32 PlayTimeInSeconds;

private:

	FTimerHandle ElapsedTimeHandle;
};
