#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputModule.h"

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "CollisionQueryParams.h"

#include "GameFramework/Character.h"
#include "cattestCharacter.h"

#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h" 
#include "AttackSystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSwordAttack, const FInputActionValue&, Value);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CATTEST_API UAttackSystemComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
	bool canAttack = true;

	UPROPERTY(EditAnywhere)
	bool saveAttack = false;

	UPROPERTY(EditAnywhere)
	bool isAttacking = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackAction;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnSwordAttack OnSwordAttack;

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void SwordAttackCombo();

	// Funkcja wywołana przez EnhancedInput
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void SwordAttack();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void SwordAttackLogic();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void ResetAttack();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void SwordTraceLoop();
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void SwordTraceLoopKick();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void StartSwordTrace();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void StartAttackComboTimer();
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void StopAttackComboTimer();
	
	TSet<AActor*> AlreadyDamagedActors;
	// Indeks ataku (np. combo)
	int32 AttackIndex = 0;

public:
	// Sets default values for this component's properties
	UAttackSystemComponent();

	//ANIMACJE COMBO

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TArray<UAnimMontage*> AttackMontages;

	UArrowComponent* ArrowTopPoint;
	UArrowComponent* ArrowBottomPoint;
	UArrowComponent* ArrowSpherePoint;
	TArray<UArrowComponent*> ArrowComponents;
	


protected:

	FTimerHandle AttackComboTimerHandle;
	// Called when the game starts
	virtual void BeginPlay() override;

	void PlayMontage();
	TArray<bool> AnimationsLock;
	

	// Funkcja do wywołania delegata
	void TriggerOnSwordAttack();

	
	void PerformSphereTrace(UWorld* World, FVector Start, FVector End, float Radius, ECollisionChannel TraceChannel, bool bDrawDebug);
	void PerformSphereTrace2(UWorld* World, FVector Start, FVector End, float Radius, ECollisionChannel TraceChannel, bool bDrawDebug);
	void OnAttackComboTimerEnd();


public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Funkcja do przypisywania akcji do komponentu wejściowego
	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);
};


//IA_ATTACK -> IF CAN ATTACK -> SWORD ATTACCK
// 
//SWORD ATTACK -> IF IS ATTACKING -> BOOL SAVE ATTACK
// -> SAVE ATTACK TRUE
// -> SAVE ATTACK FALSE -> SWITCH(ATTACK INDEX) -> ANIMACJE ATTACKU
// 
//SWORD ATTACK COMBO - > IF(SAVE ATTACK) -> set save atack false ->  SWITCH(ATTACK INDEX)
//
// STOP COMBO -> SET IS ATTACKING -> ATTACK INDEX TO 0
//
//aTTACK 1 -<< DO ONCE -> DELAY NP 0.1 -> PLAY MONTAGE -> SET ATTACK INNDEX +1 -> RESET DO ONCE