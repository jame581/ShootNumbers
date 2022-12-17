// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SNPlayerScore.generated.h"

USTRUCT(BlueprintType)
struct FSNPlayerScore
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Score")
    int32 PlayerScore;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Score")
    int32 PlayTimeInSecods;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Score")
    FString PlayTimeInSecodsFormatted;
};
