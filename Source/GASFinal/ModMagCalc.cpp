// Fill out your copyright notice in the Description page of Project Settings.


#include "ModMagCalc.h"

#define DECLARE_ATTRIBUTE_CAPTUREDEF(P) \
	FProperty* P##Property; \
	FGameplayEffectAttributeCaptureDefinition P##Def; \

#define DEFINE_ATTRIBUTE_CAPTUREDEF(S, P, T, B) \
{ \
	P##Property = FindFieldChecked<FProperty>(S::StaticClass(), GET_MEMBER_NAME_CHECKED(S, P)); \
	P##Def = FGameplayEffectAttributeCaptureDefinition(P##Property, EGameplayEffectAttributeCaptureSource::T, B); \
}


struct SDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);

	SDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttribute, Health, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttribute, Armor, Target, true);
	}
};

static const SDamageStatics& DamageStatics()
{
	static SDamageStatics DStatics;
	return DStatics;
}

UModMagCalc::UModMagCalc()
{
	RelevantAttributesToCapture.Add(DamageStatics().HealthDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);

	
}





//float UModMagCalc::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
//{
//	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
//	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
//
//	FAggregatorEvaluateParameters EvaluationParameters;
//	EvaluationParameters.SourceTags = SourceTags;
//	EvaluationParameters.TargetTags = TargetTags;
//
//	float Damage = 0.0f;
//	GetCapturedAttributeMagnitude(DamageStatics().HealthDef, Spec, EvaluationParameters, Damage);
//
//	float Armor = 0.0f;
//	GetCapturedAttributeMagnitude(DamageStatics().ArmorDef, Spec, EvaluationParameters, Armor);
//
//	return Damage - Armor;
//}





float UModMagCalc::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	return -35.0f;
}