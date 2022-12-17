// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SNUpgradeInfo.generated.h"


UENUM()
enum EUpgradeType
{
	FireRate    UMETA(DisplayName = "Fire Rate"),
};


USTRUCT(BlueprintType)
struct FSNUpgradeInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrade Info")
    int32 RateOfFire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrade Info")
	TEnumAsByte<EUpgradeType> UpgradeType;
};
