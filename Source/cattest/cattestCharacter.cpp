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
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/UserWidget.h"
#include "PawnStats.h"



DEFINE_LOG_CATEGORY(LogTemplateCharacter);

////////////////////////////////////////////////////////////////////////
// AcattestCharacter

AcattestCharacter::AcattestCharacter()

{	
	
	bIsFirstPerson = true;
	
	
	
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

	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass(TEXT("/Game/UI/WB_HUD"));
	if (WidgetClass.Succeeded())
	{
		UE_LOG(LogTemp, Error, TEXT("Znaleziono widget!"));
		WidgetBlueprintClass = WidgetClass.Class;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Nie znaleziono widgeta!"));
	}
	

		
}

void AcattestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Twoja logika Tick
}

void AcattestCharacter::BeginPlay()
{
	Super::BeginPlay(); // Wywo³anie oryginalnej funkcji BeginPlay

	UE_LOG(LogTemplateCharacter, Error, TEXT("WIDGET1 dadadada DODANY"));

	if (WidgetBlueprintClass)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetBlueprintClass);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "widget dodany");
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("WidgetBlueprintClass jest pusty!"));
	}
	
}

//void AcattestCharacter::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);  // Wywo³aj bazow¹ implementacjê ticka
//
//	if (!bIsFirstPerson)  // Je¿eli nie jesteœmy w trybie pierwszoosobowym
//	{
//		// Pobieramy rotacjê kontrolera, ale tylko wokó³ osi Yaw
//		FRotator CameraRotation = GetControlRotation(); // Rotacja kontrolera bazuj¹ca na kamerze
//		FRotator NewRotation = FRotator(0.f, CameraRotation.Yaw, 0.f);  // Nowa rotacja postaci tylko po osi Z (Yaw)
//
//		SetActorRotation(NewRotation);  // Ustawiamy rotacjê postaci
//	}
//}
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
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AcattestCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AcattestCharacter::Look);
		// use
		EnhancedInputComponent->BindAction(UseAction, ETriggerEvent::Triggered, this, &AcattestCharacter::Use);
		
		// switch
		
		EnhancedInputComponent->BindAction(ChangeCameraAction, ETriggerEvent::Triggered, this, &AcattestCharacter::ChangeCamera);
		// Crouch
		EnhancedInputComponent->BindAction(UseCrouch2, ETriggerEvent::Triggered, this, &AcattestCharacter::Crouch2);
		
		
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
	printf("test");
	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AcattestCharacter::ChangeCamera()
{
	// input is a Vector2D

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

void AcattestCharacter::Crouch2()
{
	if (!bIsCrouching3)
	{
		CCrouch2();
	}
	else
	{
		UnCrouch2();
	}
}

void AcattestCharacter::CCrouch2()
{
	if (!bIsCrouching3) // Sprawdzenie, czy postaæ nie jest ju¿ w trybie crouch
	{
		bIsCrouching3 = true;

		// Zmieñ prêdkoœæ ruchu
		GetCharacterMovement()->MaxWalkSpeed = CrouchSpeed;

		// Zmieñ skalê postaci 
		
		
		UE_LOG(LogTemp, Log, TEXT("%s is now crouching"), *GetName());
	}
}

void AcattestCharacter::UnCrouch2()
{
	if (bIsCrouching3) // Sprawdzenie, czy postaæ jest w trybie crouch
	{
		bIsCrouching3 = false;

		// Przywróæ normaln¹ prêdkoœæ ruchu
		GetCharacterMovement()->MaxWalkSpeed = NormalSpeed;

		// Przywróæ normaln¹ skalê postaci
		

		UE_LOG(LogTemp, Log, TEXT("%s has stopped crouching"), *GetName());
	}
}

void AcattestCharacter::Use(const FInputActionValue& Value)
{
	UE_LOG(LogTemplateCharacter, Log, TEXT("Use action triggered!"));
	// Tutaj dodaj kod funkcjonalnoœci dla akcji "Use"
}