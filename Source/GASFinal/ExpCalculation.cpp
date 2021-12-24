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
	//Custom Variable. Dýþarýdaki Data Tableden karakterin leveline göre gelecek olan gerekli exp miktarý setleniyor.
	ValidTransientAggregatorIdentifiers.AddTag(FGameplayTag::RequestGameplayTag("Calculation.Exp"));
}


void UExpCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecParams, FGameplayEffectCustomExecutionOutput& ExecOutputs) const
{
	//Capture Variables
	//Data Tableden gelen required exp
	float RequiredExp = 0.f;
	//Karakterin mevcut Exp Miktarý buna setleniyor.
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
		
		//Eðer Level alýrsa Efekte eklenen Conditional Gameplay Effect'i tetiklemek için aþaðýdaki Fonksiyonu kullan.
		ExecOutputs.MarkConditionalGameplayEffectsToTrigger();
		
		FString TheFloatStr = FString::SanitizeFloat(Exp);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TheFloatStr);
	}
	
}

