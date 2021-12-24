// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h" //<--
#include "AbilitySystemBlueprintLibrary.h"
#include "PlayerAttribute.generated.h"

/**
 * 
 */


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)





UCLASS()
class GASFINAL_API UPlayerAttribute : public UAttributeSet
{
	GENERATED_BODY()
	



public:
		UPlayerAttribute();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;


	//Max Health
	UPROPERTY(BlueprintReadOnly, Category = "Arsh", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UPlayerAttribute, MaxHealth)
	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);


	//Health
	UPROPERTY(BlueprintReadOnly, Category = "Arsh", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UPlayerAttribute, Health)
	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

	//Stamina

	UPROPERTY(BlueprintReadOnly, Category = "Arsh", ReplicatedUsing = OnRep_Stamina)
		FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UPlayerAttribute, Stamina)
		UFUNCTION()
		virtual void OnRep_Stamina(const FGameplayAttributeData& OldStamina);

	//MaxStamina
	UPROPERTY(BlueprintReadOnly, Category = "Arsh", ReplicatedUsing = OnRep_MaxStamina)
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UPlayerAttribute, MaxStamina)
	UFUNCTION()
	virtual void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina);


	



	UPROPERTY(BlueprintReadOnly, Category = "Arsh", ReplicatedUsing = OnRep_Armor)
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UPlayerAttribute, Armor)
	UFUNCTION()
	virtual void OnRep_Armor(const FGameplayAttributeData& OldArmor);


	UPROPERTY(BlueprintReadOnly, Category = "Arsh", ReplicatedUsing = OnRep_Attack)
	FGameplayAttributeData Attack;
	ATTRIBUTE_ACCESSORS(UPlayerAttribute, Attack)
	UFUNCTION()
	virtual void OnRep_Attack(const FGameplayAttributeData& OldAttack);


	UPROPERTY(BlueprintReadOnly, Category = "Arsh", ReplicatedUsing = OnRep_CharacterLevel)
	FGameplayAttributeData CharacterLevel;
	ATTRIBUTE_ACCESSORS(UPlayerAttribute, CharacterLevel)
	UFUNCTION()
	virtual void OnRep_CharacterLevel(const FGameplayAttributeData& OldCharacterLevel);


	UPROPERTY(BlueprintReadOnly, Category = "Arsh", ReplicatedUsing = OnRep_CharacterLevel)
	FGameplayAttributeData Exp;
	ATTRIBUTE_ACCESSORS(UPlayerAttribute, Exp)
	UFUNCTION()
	virtual void OnRep_Exp(const FGameplayAttributeData& OldExp);

	UPROPERTY(BlueprintReadOnly, Category = "Arsh", ReplicatedUsing = OnRep_ExpBounty)
	FGameplayAttributeData ExpBounty;
	ATTRIBUTE_ACCESSORS(UPlayerAttribute, ExpBounty)
	UFUNCTION()
	virtual void OnRep_ExpBounty(const FGameplayAttributeData& OldExpBounty);






public:
	UAbilitySystemBlueprintLibrary* Library;






protected:
	//void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);

	


};
