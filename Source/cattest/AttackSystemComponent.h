#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputModule.h"
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

	// Funkcja wywo³ana przez EnhancedInput
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void SwordAttack();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void SwordAttackLogic();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void ResetAttack();

	// Indeks ataku (np. combo)
	int32 AttackIndex = 0;

public:
	// Sets default values for this component's properties
	UAttackSystemComponent();

	//ANIMACJE COMBO

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	TArray<UAnimMontage*> AttackMontages;


	



protected:
	FTimerHandle AttackComboTimerHandle;
	// Called when the game starts
	virtual void BeginPlay() override;

	void PlayMontage();

	TArray<bool> AnimationsLock;
	

	// Funkcja do wywo³ania delegata
	void TriggerOnSwordAttack();

	// Funkcja do resetowania ataku (resetuje flagi i indeks ataku)
	

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Funkcja do przypisywania akcji do komponentu wejœciowego
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