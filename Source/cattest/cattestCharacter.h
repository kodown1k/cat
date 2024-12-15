#pragma once

// Copyright Epic Games, Inc. All Rights Reserved.



#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "GameFramework/SpringArmComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "cattestCharacter.generated.h"


class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class USpringArmComponent;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AcattestCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* ThirdPersonCameraComponent;

	

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	//uyse input action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* UseAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	//uyse input action
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ChangeCameraAction;

	//Crouch Input Acction
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* UseCrouch2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Crouch3", meta = (AllowPrivateAccess = "true"))
	bool bIsCrouching3 = false;
	
	
	

	bool bIsFirstPerson = true;
	//ZMIENNE KAMR



	//WIDGETY

	
	

public:
	AcattestCharacter();

	
	
	

	
protected:
	virtual void Tick(float DeltaTime) override;
	/** Called for movement input */ //ARGUMENT FINPUT ACTION POWINIEN BYC TYLKO WKLADANY JEZELI MAMY WIECEJ NIZ DWA STANY JEZELI USTAWILISMY W IA_AKCJA JAKO TRIGGER TO NIE JEST TO POTRZEBNE
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	void Use(const FInputActionValue& Value);
	void ChangeCamera();
	void Crouch2();
	void UnCrouch2();   // Dezaktywuje crouch
	void CCrouch2();    // Aktywuje crouch

	

protected:
	// APawn interface
	virtual void NotifyControllerChanged() override;
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface
	bool isCrouching3 = false;
	
	
	float CrouchSpeed = 350.f; // Prêdkoœæ w trybie crouch
	float NormalSpeed = 800.f; // Normalna prêdkoœæ

	FVector CrouchScale = FVector(1.f, 1.f, 0.5f); // Skala w trybie crouch
	FVector NormalScale = FVector(1.f, 1.f, 1.f); // Normalna skala


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> WidgetBlueprintClass;

	


public:

	virtual void BeginPlay() override;
	//virtual void EndPlay();
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	USpringArmComponent* GetSpringArm() const { return SpringArm; }
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	UCameraComponent* GetThirdPersonCameraComponent() const { return ThirdPersonCameraComponent; }
	UPROPERTY()
	UUserWidget* CurrentWidget;

	/** Widget class to spawn for the heads up display. */
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UPawnStats> PlayerHUDClass;

	/** The widget instance that we are using as our HUD. */
	UPROPERTY()
	class UPawnStats* PlayerHUD;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	UProgressBar* HealthBar;
};

