#include "AttackSystemComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Actor.h"
#include "InputActionValue.h"



UAttackSystemComponent::UAttackSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
    
    AttackIndex = 0;

}

void UAttackSystemComponent::BeginPlay()
{
	Super::BeginPlay();
    AnimationsLock.Init(false, AttackMontages.Num());
	// Sprawdzanie, czy akcja ataku jest ustawiona
	if (AttackAction)
	{
		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(GetOwner()->InputComponent);
		if (EnhancedInputComponent)
		{
			// Zwi¹zanie akcji z metod¹ SwordAttack
			EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &UAttackSystemComponent::SwordAttack);
		}
	}
}

void UAttackSystemComponent::SwordAttack() {
    if (canAttack) {
        SwordAttackLogic();
    }
}


void UAttackSystemComponent::SwordAttackLogic()
{   
    UE_LOG(LogTemp, Warning, TEXT("isattackingg %d"), isAttacking);
    if (isAttacking) {
        saveAttack = true;
    }
    else {
        isAttacking = true;
        
        PlayMontage();
    }

    //if (isAttacking)
    //{
    //    // Sprawdzanie, czy akcja ataku jest w toku
    //    isAttacking = true;
    //    UE_LOG(LogTemp, Warning, TEXT("Index %d"), AttackIndex);
    //    UE_LOG(LogTemp, Warning, TEXT("Indexmon %d"), AttackMontages.Num());

    //    // Zainicjowanie combo (jeœli saveAttack = false, mo¿na przejœæ do kolejnego ataku)
    //    if (!saveAttack)
    //    {
    //        // Jeœli atak jest zapiszony, wykonaj logikê combo
    //        if (AttackIndex < AttackMontages.Num())
    //        {
    //            if (UAnimInstance* AnimInstance = GetOwner()->FindComponentByClass<USkeletalMeshComponent>()->GetAnimInstance())
    //            {
    //                AnimInstance->Montage_Play(AttackMontages[AttackIndex]);
    //            }
    //        }
    //        AttackIndex++;
    //        UE_LOG(LogTemp, Warning, TEXT("ATAK+"));
    //        saveAttack = true;
    //        if (AttackIndex > AttackMontages.Num()) {
    //            AttackIndex = 0;
    //        }
    //    }
    //   

    //    // Sprawdzenie, czy mamy wystarczaj¹c¹ liczbê monta¿ów do odtworzenia
    //   
    //    else
    //    {
    //        UE_LOG(LogTemp, Warning, TEXT("No Montage for AttackIndex %d"), AttackIndex);
    //    }

    //    // Broadcastowanie ataku
    //    TriggerOnSwordAttack();

    //    // Ustawienie timera na resetowanie saveAttack po czasie (np. 0.5 sekundy)
    //    
    //    if (AttackComboTimerHandle.IsValid())
    //    {
    //        GetWorld()->GetTimerManager().ClearTimer(AttackComboTimerHandle);
    //    }

    //    // Ustawienie timera na resetowanie saveAttack po czasie (np. 0.5 sekundy)
    //    GetWorld()->GetTimerManager().SetTimer(AttackComboTimerHandle, this, &UAttackSystemComponent::ResetAttack, 1.0f, false);
    //}
}

void UAttackSystemComponent::SwordAttackCombo()
{
    UE_LOG(LogTemp, Warning, TEXT("SA %d"), saveAttack);
    if (saveAttack) {
        saveAttack = false;
        PlayMontage();
    }
    else {
        ResetAttack();
        
    }
    
}

void UAttackSystemComponent::PlayMontage() {
    UE_LOG(LogTemp, Warning, TEXT("INDEX %d"), AttackIndex);

    if (AttackIndex < AnimationsLock.Num()) {
        if (!AnimationsLock[AttackIndex]) {
            AnimationsLock[AttackIndex] = true;
            if (AttackIndex < AttackMontages.Num())
            {
                if (UAnimInstance* AnimInstance = GetOwner()->FindComponentByClass<USkeletalMeshComponent>()->GetAnimInstance())
                {
                    
                    AnimInstance->Montage_Play(AttackMontages[AttackIndex]);
                }
                AttackIndex++;
            }
        }
    }
}

void UAttackSystemComponent::TriggerOnSwordAttack()
{
	// Broadcastuje delegata, który mo¿e zostaæ subskrybowany przez inne klasy
	OnSwordAttack.Broadcast(FInputActionValue());
	
}

void UAttackSystemComponent::ResetAttack()
{
	// Resetowanie stanu ataku
    UE_LOG(LogTemp, Warning, TEXT("Resetting attack. Current AttackIndex = %d"), AttackIndex);
    AnimationsLock.Init(false, AnimationsLock.Num());
	isAttacking = false;
	AttackIndex = 0; // Reset combo
	

    /*if (AttackComboTimerHandle.IsValid())
    {
        GetWorld()->GetTimerManager().ClearTimer(AttackComboTimerHandle);
    }*/

}

void UAttackSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UAttackSystemComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Mo¿esz zarejestrowaæ dodatkowe akcje wejœciowe, jeœli to konieczne
}
