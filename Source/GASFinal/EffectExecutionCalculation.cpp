// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectExecutionCalculation.h"
#include "AbilitySystemComponent.h"
#include "PlayerAttribute.h"

struct DamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);
	

	DamageCapture()
	{
		// Snapshot happens at time of GESpec creation

		// We're not capturing anything from the Source in this example, but there could be like AttackPower attributes that you might want.

		// Capture optional Damage set on the damage GE as a CalculationModifier under the ExecutionCalculation
		//DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttribute, Armor, Source, true);
		

		// Capture the Target's Armor. Don't snapshot.
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttribute, Health, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPlayerAttribute, Armor, Target, false);
		
	}
};


static DamageCapture& GetDamageCapture()
{
	static DamageCapture DamageCaptureVar;
	return DamageCaptureVar;
}

UEffectExecutionCalculation::UEffectExecutionCalculation()
{
	
	RelevantAttributesToCapture.Add(GetDamageCapture().ArmorDef);
	RelevantAttributesToCapture.Add(GetDamageCapture().HealthDef);
	

	//Add this tag to project.
	ValidTransientAggregatorIdentifiers.AddTag(FGameplayTag::RequestGameplayTag("Calculation.Damage.Melee"));
	

}

void UEffectExecutionCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecParams, FGameplayEffectCustomExecutionOutput& ExecOutputs) const
{
	//Calc Variables
	float OutHealth = 5.0f;


	//Capture Variables
	float ArmorMagnetute = 5.f;
	float HealthMagnetute = 5.f;
	float AttackDamage = 5.f;

	

	ExecParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().ArmorDef, FAggregatorEvaluateParameters(), ArmorMagnetute);
	ExecParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageCapture().HealthDef, FAggregatorEvaluateParameters(), HealthMagnetute);
	

		//Scalable Float Listen
	//ExecParams.AttemptCalculateTransientAggregatorMagnitude(FGameplayTag::RequestGameplayTag("Calculation.Damage.Melee"), FAggregatorEvaluateParameters(), AttackDamage);
	
		//SetByCaller Listen
	const FGameplayEffectSpec& Spec = ExecParams.GetOwningSpec();
	AttackDamage = Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Calculation.Damage.Melee")), false, -1.0f), 0.0f;

	

	//Start Calculation
	OutHealth = HealthMagnetute - (AttackDamage - ArmorMagnetute); 


	//Output
	ExecOutputs.AddOutputModifier(FGameplayModifierEvaluatedData(GetDamageCapture().HealthProperty, EGameplayModOp::Override, OutHealth));
	
	

}