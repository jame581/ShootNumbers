// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SNUpgradeInfo.generated.h"


UENUM(BlueprintType)
enum EUpgradeType
{
	FireRate			UMETA(DisplayName = "Fire Rate"),
	DamageUpdate		UMETA(DisplayName = "Damage update"),
};


USTRUCT(BlueprintType)
struct FSNUpgradeInfo
{
    GENERATED_BODY()
	
	// Amount of decrease player rate of fire
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrade Info", meta = (ClampMin = "0.1", ClampMax = "2.0", UIMin = "0.1", UIMax = "2.0", EditCondition = "UpgradeType == EUpgradeType::FireRate", EditConditionHides))
	float RateOfFire;

	// Amount of player damage
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrade Info", meta = (ClampMin = "1", ClampMax = "5", UIMin = "1", UIMax = "5", EditCondition = "UpgradeType == EUpgradeType::DamageUpdate", EditConditionHides))
	int32 PlayerDamage = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Upgrade Info")
	TEnumAsByte<EUpgradeType> UpgradeType;
};
