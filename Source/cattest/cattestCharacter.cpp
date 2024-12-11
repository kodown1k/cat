// Copyright Epic Games, Inc. All Rights Reserved.

#include "cattestCharacter.h"
#include "cattestProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AcattestCharacter

AcattestCharacter::AcattestCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	bIsCrouching = false;
	CrouchHeight = 55.0f;
	StandHeight = 88.0f;
	CurrentCapsuleHeight = StandHeight;
}

//////////////////////////////////////////////////////////////////////////// Input

void AcattestCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AcattestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AcattestCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AcattestCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AcattestCharacter::Look);

		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &AcattestCharacter::StartCrouch);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AcattestCharacter::StopCrouch);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void AcattestCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AcattestCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AcattestCharacter::StartCrouch(const FInputActionValue& Value)
{
	if (!bIsCrouching)
	{
		bIsCrouching = true;
		
		GetCharacterMovement()->MaxWalkSpeed /= 2;
		// Wykonywanie funkcji AcattestCharacter::UpdateCrouchHeight w interwale (w pętli). Co 0.01 sekundy.
		GetWorld()->GetTimerManager().SetTimer(CrouchTimer, this, &AcattestCharacter::UpdateCrouchHeight, 0.01f, true);
	}
}

void AcattestCharacter::StopCrouch(const FInputActionValue& Value)
{
	if (bIsCrouching)
	{
		bIsCrouching = false;
		
		GetCharacterMovement()->MaxWalkSpeed *= 2;
		// Wykonywanie funkcji AcattestCharacter::UpdateCrouchHeight w interwale (w pętli). Co 0.01 sekundy.
		GetWorld()->GetTimerManager().SetTimer(CrouchTimer, this, &AcattestCharacter::UpdateCrouchHeight, 0.01f, true);
	}
}

/**
 * Płynna zmiana wysokości kapsuły.
 */
void AcattestCharacter::UpdateCrouchHeight()
{
	CurrentCapsuleHeight = FMath::FInterpTo(CurrentCapsuleHeight, bIsCrouching ? CrouchHeight : StandHeight, GetWorld()->GetDeltaSeconds(), 5.0f);
	GetCapsuleComponent()->SetCapsuleHalfHeight(CurrentCapsuleHeight);
    
	if (FMath::IsNearlyEqual(CurrentCapsuleHeight, bIsCrouching ? CrouchHeight : StandHeight))
	{
		GetWorld()->GetTimerManager().ClearTimer(CrouchTimer);
	}
}

/**
 * Logika sprawdzająca czy mozna podskoczyć.
 */
void AcattestCharacter::Jump() 
{
	if (!bIsCrouching)
	{
		Super::Jump();
	}
}
