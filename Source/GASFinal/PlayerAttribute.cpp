// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAttribute.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "GASFinalCharacter.h"

UPlayerAttribute::UPlayerAttribute()
	:Health(1.0f), Stamina(1.0f)
	
{

}



//MaxHP artýnca canýn da orantýlý olarak artmasý istendiðinde kullanýlacak algoritma; Örn: Max HP olan bir item alýnýnca canýn %5 ise itemden sonra canýn yine %5 olacak þekilde artýrýlmasý
/*

void UPlayerAttribute::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	// This is called whenever attributes change, so for max health/mana we want to scale the current totals to match
	Super::PreAttributeChange(Attribute, NewValue);

	// If a Max value changes, adjust current to keep Current % of Current to Max
	if (Attribute == GetMaxHealthAttribute()) // GetMaxHealthAttribute comes from the Macros defined at the top of the header
	{
		AdjustAttributeForMaxChange(Health, MaxHealth, NewValue, GetHealthAttribute());
	}
	else if (Attribute == GetMaxStaminaAttribute())
	{
		AdjustAttributeForMaxChange(Stamina, MaxStamina, NewValue, GetStaminaAttribute());
	}

}


void UPlayerAttribute::AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty)
{
	UAbilitySystemComponent* AbilityComp = GetOwningAbilitySystemComponent();
	const float CurrentMaxValue = MaxAttribute.GetCurrentValue();
	if (!FMath::IsNearlyEqual(CurrentMaxValue, NewMaxValue) && AbilityComp)
	{
		// Change current value to maintain the current Val / Max percent
		const float CurrentValue = AffectedAttribute.GetCurrentValue();
		float NewDelta = (CurrentMaxValue > 0.f) ? (CurrentValue * NewMaxValue / CurrentMaxValue) - CurrentValue : NewMaxValue;

		AbilityComp->ApplyModToAttributeUnsafe(AffectedAttributeProperty, EGameplayModOp::Additive, NewDelta);
	}
}

*/



/*
//DEBUG
//FString Value = FString::SanitizeFloat(GetMaxStamina());
FString Value = FString::SanitizeFloat(NewValue);
//FString test = Attribute.GetName();
GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, Value);
*/




//Clamp Attribute Base for Max.
void UPlayerAttribute::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute.GetUProperty() == FindFieldChecked<FProperty>(UPlayerAttribute::StaticClass(), GET_MEMBER_NAME_CHECKED(UPlayerAttribute, Health)))
	{
		NewValue = FMath::Clamp(NewValue, 0.f, MaxHealth.GetCurrentValue());
	}
	
	//... -->

}




//Attribute Setlenmeden önce PreAttributeChange çaðýrýlýr, Max HP v.s. clamp kontrolunun yapýldðý yer. <--Base Olmayan Clamp
void UPlayerAttribute::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	// This is called whenever attributes change, so for max health/mana we want to scale the current totals to match
	Super::PreAttributeChange(Attribute, NewValue);

	// If a value changes, adjust current to keep in Max
	if (Attribute == GetHealthAttribute()) // GetMaxHealthAttribute comes from the Macros defined at the top of the header
	{
		if (NewValue > GetMaxHealth())
		{
			NewValue = FMath::Clamp<float>(NewValue, 0, GetMaxHealth());
		}

		else if (NewValue<= 0)
		{
			NewValue = 0;			
		}
	}

	if (Attribute == GetStaminaAttribute()) // GetStaminaAttribute comes from the Macros defined at the top of the header
	{
		if (NewValue >= GetMaxStamina())
		{
			NewValue = FMath::Clamp<float>(NewValue, 0, GetMaxStamina());
		}
		else if (NewValue <= 0)
		{
			NewValue = 0;
		}

	}
		
	//... -->
}



// Post Gameplay Effect Execute. Old: For Base Value Clamp
void UPlayerAttribute::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

/*
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// Handle other health changes such as from healing or direct modifiers
		// First clamp it
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
	}

	else if (Data.EvaluatedData.Attribute == GetMaxStaminaAttribute())
	{
		// Handle other health changes such as from healing or direct modifiers
		// First clamp it
		SetStamina(FMath::Clamp(GetStamina(), 0.0f, GetMaxStamina()));
	}
*/

}




void UPlayerAttribute::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

// 	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttribute, MaxHealth, COND_None, REPNOTIFY_Always);
// 	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttribute, Health, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME(UPlayerAttribute, MaxHealth);
	DOREPLIFETIME(UPlayerAttribute, Health);
	DOREPLIFETIME(UPlayerAttribute, MaxStamina);
	DOREPLIFETIME(UPlayerAttribute, Stamina);
	//... -->

}


void UPlayerAttribute::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttribute, MaxHealth, OldValue);

}

void UPlayerAttribute::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttribute, Health, OldValue);

}

void UPlayerAttribute::OnRep_MaxStamina(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttribute, MaxStamina, OldValue);
}

void UPlayerAttribute::OnRep_Stamina(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttribute, Stamina, OldValue);
}





