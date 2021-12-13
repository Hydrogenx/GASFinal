// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerAttribute.h"			//<-- Journey
#include "AbilitySystemInterface.h"		//<-- Journey
#include "GASFinalCharacter.generated.h"

UCLASS(config=Game)
class AGASFinalCharacter : public ACharacter, public IAbilitySystemInterface //<-- Journey
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	AGASFinalCharacter();

	

protected:

	

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */


	

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }














	//Your Journey Starts Here

public:

	//AGASFinalCharacter();
	virtual void PossessedBy(AController* NewController) override;


	//virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;


	UFUNCTION(BlueprintCallable)
		virtual int32 GetCharacterLevel() const;


protected:

	void BeginPlay() override;

	UPROPERTY()
		int32 bAbilitiesInitialized;

	UPROPERTY(EditAnywhere, Replicated, Category = Abilities)
		int32 CharacterLevel;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Arsh)
		TArray<TSubclassOf<UGameplayAbility>> GrantedAbilities;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Arsh)
		TArray<TSubclassOf<UGameplayEffect>> GrantedEffects;

	//Data Table ile component içinden Attribute edit imkaný sunuyor.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Arsh)
		UAbilitySystemComponent* AbilitySystem;


	UPROPERTY()
		UPlayerAttribute* AttributeSet;


	void AddStartupGameplayAbilities();


	// Friended to allow access to handle functions above
	//friend UPlayerattribute;


















};

