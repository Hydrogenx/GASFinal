// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "PlayerAttribute.h"
#include "ModMagCalc.generated.h"

/**
 * 
 */

UCLASS()
class GASFINAL_API UModMagCalc : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UModMagCalc();
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

};
