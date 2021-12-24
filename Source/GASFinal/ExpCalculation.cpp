// Fill out your copyright notice in the Description page of Project Settings.


#include "ExpCalculation.h"
#include "AbilitySystemComponent.h"
#include "PlayerAttribute.h"

struct DamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Exp);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CharacterLevel);
	DamageCapture()
	{
		//Source
		//DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttribute, Attack, Source, true);


		// Capture the Target's Armor. Don't snapshot.
		//DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttribute, Exp, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttribute, Exp, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttribute, CharacterLevel, Target, false);
	}
};


static DamageCapture& GetDamageCapture()
{
	static DamageCapture DamageCaptureVar;
	return DamageCaptureVar;
}

UExpCalculation::UExpCalculation()
{
	RelevantAttributesToCapture.Add(GetDamageCapture().ExpDef);
	RelevantAttributesToCapture.Add(GetDamageCapture().CharacterLevelDef);
	
	//Add this tag to project.
	//Custom Variable. D��ar�daki Data Tableden karakterin leveline g�re gelecek olan gerekli exp miktar� setleniyor.
	ValidTransientAggregatorIdentifiers.AddTag(FGameplayTag::RequestGameplayTag("Calculation.Exp"));
}


void UExpCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecParams, FGameplayEffectCustomExecutionOutput& ExecOutputs) const
{
	//Capture Variables
	//Data Tableden gelen required exp
	float RequiredExp = 0.f;
	//Karakterin mevcut Exp Miktar� buna setleniyor.
	float Exp = 0.f;
	//Karakterin Mevcut Leveli buna setleniyor.
	float CharacterLevel = 0.f;


	ExecParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().ExpDef, FAggregatorEvaluateParameters(), Exp);
	ExecParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().CharacterLevelDef, FAggregatorEvaluateParameters(), CharacterLevel);
	ExecParams.AttemptCalculateTransientAggregatorMagnitude(FGameplayTag::RequestGameplayTag("Calculation.Exp"), FAggregatorEvaluateParameters(), RequiredExp);

	
	//FString Test;
	/*
	FString TheFloatStr = FString::SanitizeFloat(Exp);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TheFloatStr);
	*/



	//Start Calculation
	if (Exp >= RequiredExp)
	{
		CharacterLevel++;
		ExecOutputs.AddOutputModifier(FGameplayModifierEvaluatedData(GetDamageCapture().CharacterLevelProperty, EGameplayModOp::Override, CharacterLevel));
		
		//E�er Level al�rsa Efekte eklenen Conditional Gameplay Effect'i tetiklemek i�in a�a��daki Fonksiyonu kullan.
		ExecOutputs.MarkConditionalGameplayEffectsToTrigger();
		
		FString TheFloatStr = FString::SanitizeFloat(Exp);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TheFloatStr);
	}
	
}

