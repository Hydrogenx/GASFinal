// Copyright Epic Games, Inc. All Rights Reserved.

#include "GASFinalCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// AGASFinalCharacter

AGASFinalCharacter::AGASFinalCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)






	//Your Journey Starts Here --->



	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
	AbilitySystem->SetIsReplicated(true);

	// Create the attribute set, this replicates by default
	AttributeSet = CreateDefaultSubobject<UPlayerAttribute>(TEXT("AttributeSet"));
	CharacterLevel = 1;



	//Your Journey Ends Here <---














}

//////////////////////////////////////////////////////////////////////////
// Input

void AGASFinalCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AGASFinalCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGASFinalCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	
	
}

void AGASFinalCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AGASFinalCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}








//Your Journey Starts Here --->


	UAbilitySystemComponent* AGASFinalCharacter::GetAbilitySystemComponent() const
	{
		return AbilitySystem;
	}

int32 AGASFinalCharacter::GetCharacterLevel() const
{
	return CharacterLevel;
}

void AGASFinalCharacter::Die_Implementation(AActor* KilledBy)
{
	FGameplayEventData Payload;
	Payload.Target = KilledBy;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(AbilitySystem->GetOwnerActor(), FGameplayTag::RequestGameplayTag("Status.Die"), Payload);
//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("VALID"));
	
}


void AGASFinalCharacter::BeginPlay()
{
	Super::BeginPlay();



	AddStartupGameplayAbilities();

	//Bu satýr abilitynin cliente replicate olmasýný saðlýyor
	AbilitySystem->InitAbilityActorInfo(this, this);

}



void AGASFinalCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);


}




void AGASFinalCharacter::AddStartupGameplayAbilities()
{
	//check(AbilitySystem);

	if (GetLocalRole() == ROLE_Authority)
	{

		// Grant abilities, but only on the server	
		for (TSubclassOf<UGameplayAbility>& StartupAbility : GrantedAbilities)
		{
			AbilitySystem->GiveAbility(FGameplayAbilitySpec(StartupAbility, GetCharacterLevel(), 0, this));

		}




		// Now apply passives
		for (TSubclassOf<UGameplayEffect>& GameplayEffect : GrantedEffects)
		{
			FGameplayEffectContextHandle EffectContext = AbilitySystem->MakeEffectContext();
			EffectContext.AddSourceObject(this);

			FGameplayEffectSpecHandle NewHandle = AbilitySystem->MakeOutgoingSpec(GameplayEffect, GetCharacterLevel(), EffectContext);
			if (NewHandle.IsValid())
			{
				FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystem->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystem);
			}
		}






	}
}


//Your Journey Ends Here <---

