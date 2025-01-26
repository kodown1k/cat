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
#include "ToolBuilderUtil.h"
#include "Engine/LocalPlayer.h"
#include "AbilityCastComponent.h"
#include "StoryComponent.h"	
#include "StatComponent.h"


DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AcattestCharacter

AcattestCharacter::AcattestCharacter()
{
	// Set size for collision capsule
	bIsFirstPerson = true;
	bIsCrouching3 = false;


	// Set size for collision capsuleD
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);


	// SpringArm for Third-Person Camera
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraAttachmentArm"));
	SpringArm->SetupAttachment(GetCapsuleComponent()); // Attach to the capsule
	SpringArm->TargetArmLength = 300.0f; // Set the desired camera distance
	SpringArm->bUsePawnControlRotation = true; // Allow camera to rotate with pawn's control rotation

	// Third-Person Camera
	ThirdPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	ThirdPersonCameraComponent->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	ThirdPersonCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// First-Person Camera

	// Create a CameraComponent	

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true; // Rotate camera based on controller

	// Mesh for First-Person view
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(GetCapsuleComponent());
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));
}

void AcattestCharacter::BeginPlay()
{
	Super::BeginPlay();
	ShowWidget();
}

//////////////////////////////////////////////////////////////////////////// Input

void AcattestCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AcattestCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent * EnhancedInputComponent = GetOwner()->GetComponentByClass<UEnhancedInputComponent>())
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AcattestCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AcattestCharacter::Look);

		EnhancedInputComponent->BindAction(UseAction, ETriggerEvent::Triggered, this, &AcattestCharacter::Use);

		// switch

		EnhancedInputComponent->BindAction(SwitchAction, ETriggerEvent::Triggered, this, &AcattestCharacter::SwitchCamera);
		// Crouch
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &AcattestCharacter::NewCrouch);

		

		auto StatComponent = FindComponentByClass<UStatComponent>();
		StatComponent->SetupPlayerInputComponent(EnhancedInputComponent);
		auto AbilityCastComponent = FindComponentByClass<UAbilityCastComponent>();
		AbilityCastComponent->SetupPlayerInputComponent(EnhancedInputComponent);
		auto StoryCastComponent = FindComponentByClass<UStoryComponent>();
		StoryCastComponent->SetupPlayerInputComponent(EnhancedInputComponent);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error,
		       TEXT(
			       "'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."
		       ), *GetNameSafe(this));
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


void AcattestCharacter::NewCrouch(const FInputActionValue& Value)
{
	if (!bIsCrouching3) // Sprawdzenie, czy posta� nie jest ju� w trybie crouch
	{
		bIsCrouching3 = true;

		// Zmie� pr�dko�� ruchu
		GetCharacterMovement()->MaxWalkSpeed = m_SpeedCrouch;

		// Zmie� skal� postaci 


		UE_LOG(LogTemp, Log, TEXT("%s is now crouching"), *GetName());
	}
	else if (bIsCrouching3) // Sprawdzenie, czy posta� jest w trybie crouch
	{
		bIsCrouching3 = false;

		// Przywr�� normaln� pr�dko�� ruchu
		GetCharacterMovement()->MaxWalkSpeed = m_SpeedWalk;

		// Przywr�� normaln� skal� postaci


		UE_LOG(LogTemp, Log, TEXT("%s has stopped crouching"), *GetName());
	}
}



void AcattestCharacter::SwitchCamera(const FInputActionValue& Value)
{
	if (bIsFirstPerson)
	{

		// Switch to third-person camera

		FirstPersonCameraComponent->SetActive(false);
		ThirdPersonCameraComponent->SetActive(true);
		bIsFirstPerson = false;
	}
	else
	{
		// Switch to first-person camera

		FirstPersonCameraComponent->SetActive(true);
		ThirdPersonCameraComponent->SetActive(false);
		bIsFirstPerson = true;

	}
}

void AcattestCharacter::Use(const FInputActionValue& Value)
{

}


void AcattestCharacter::ShowWidget()
{
	if (GEngine)
		
	if (WidgetBlueprintClass) // Sprawdzenie, czy klasa widgetu zosta�a przypisana
	{

		// Stw�rz instancj� widgetu
		MyWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetBlueprintClass);
		

		if (MyWidget)
		{
			MyWidget->AddToViewport(); // Dodaj widget do ekranu
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "widget dodany");
		}
	}
}

void AcattestCharacter::RemoveCurrentWidget()
{
	if (MyWidget) // Sprawd�, czy widget istnieje
	{
		MyWidget->RemoveFromParent(); // Usu� widget z widoku
		MyWidget = nullptr;           // Wyzeruj wska�nik widgetu
		UE_LOG(LogTemp, Log, TEXT("Widget removed successfully"));
	}
}


