// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ExpCalculation.generated.h"

/**
 * 
 */
UCLASS()
class GASFINAL_API UExpCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	

public:

	UExpCalculation();

	

	void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecParams, FGameplayEffectCustomExecutionOutput& ExecOutputs) const;


private:
	UPROPERTY()
	uint32 bTriggerConditionalGameplayEffects : 1;

};
