#include "AttackSystemComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Actor.h"
#include "InputActionValue.h"
#include "StatComponent.h"
#include "Game/MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

UAttackSystemComponent::UAttackSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
    
    AttackIndex = 0;

}


void UAttackSystemComponent::BeginPlay()
{
	Super::BeginPlay();
    AnimationsLock.Init(false, AttackMontagesStructure.Num());

    GetOwner()->GetComponents<UArrowComponent>(ArrowComponents);

    // Sprawdzamy, czy mamy co najmniej 2 komponenty
    if (ArrowComponents.Num() >= 3)
    {
        ArrowTopPoint = ArrowComponents[0];    // Przypisujemy pierwszy komponent
        ArrowBottomPoint = ArrowComponents[1]; // Przypisujemy drugi komponent
        ArrowSpherePoint = ArrowComponents[2]; // Przypisujemy drugi komponent
        UE_LOG(LogTemp, Warning, TEXT("ArrowTopPoint: %s"), *ArrowTopPoint->GetName());
        UE_LOG(LogTemp, Warning, TEXT("ArrowBottomPoint: %s"), *ArrowBottomPoint->GetName());
        UE_LOG(LogTemp, Warning, TEXT("ArrowBottomPoint: %s"), *ArrowBottomPoint->GetName());
        UE_LOG(LogTemp, Warning, TEXT("ArrowTopPoint found at: %s"), *ArrowTopPoint->GetComponentLocation().ToString());
        UE_LOG(LogTemp, Warning, TEXT("ArrowBottomPoint found at: %s"), *ArrowBottomPoint->GetComponentLocation().ToString());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Not enough ArrowComponents found!"));
    }

	// Sprawdzanie, czy akcja ataku jest ustawiona
	if (AttackAction)
	{
		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(GetOwner()->InputComponent);
		if (EnhancedInputComponent)
		{
			// Związanie akcji z metodą SwordAttack
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
    //    UE_LOG(LogTemp, Warning, TEXT("Indexmon %d"), AttackMontagesStructure.Num());

    //    // Zainicjowanie combo (jeśli saveAttack = false, można przejść do kolejnego ataku)
    //    if (!saveAttack)
    //    {
    //        // Jeśli atak jest zapiszony, wykonaj logikę combo
    //        if (AttackIndex < AttackMontagesStructure.Num())
    //        {
    //            if (UAnimInstance* AnimInstance = GetOwner()->FindComponentByClass<USkeletalMeshComponent>()->GetAnimInstance())
    //            {
    //                AnimInstance->Montage_Play(AttackMontagesStructure[AttackIndex].AttackMontages);
    //            }
    //        }
    //        AttackIndex++;
    //        UE_LOG(LogTemp, Warning, TEXT("ATAK+"));
    //        saveAttack = true;
    //        if (AttackIndex > AttackMontagesStructure.Num()) {
    //            AttackIndex = 0;
    //        }
    //    }
    //   

    //    // Sprawdzenie, czy mamy wystarczającą liczbę montażów do odtworzenia
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
        AlreadyDamagedActors.Empty();
        PlayMontage();
    }
    else {
        ResetAttack();
        
    }
    
}

void UAttackSystemComponent::PlayMontage() {
    UE_LOG(LogTemp, Warning, TEXT("INDEX %d"), AttackIndex);

    APawn* PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetPawn();
    
    if (AttackIndex < AnimationsLock.Num()) {
        if (!AnimationsLock[AttackIndex]) {
            AnimationsLock[AttackIndex] = true;
            if (AttackIndex < AttackMontagesStructure.Num())
            {
                if (UAnimInstance* AnimInstance = GetOwner()->FindComponentByClass<USkeletalMeshComponent>()->GetAnimInstance())
                {
                    
                    AnimInstance->Montage_Play(AttackMontagesStructure[AttackIndex].AttackMontages);
                    UGameplayStatics::PlaySoundAtLocation(GetWorld(), AttackMontagesStructure[AttackIndex].AttackSound, PlayerCharacter->GetActorLocation() + PlayerCharacter->GetActorForwardVector());
                }
                AttackIndex++;
            }
        }
    }
}

void UAttackSystemComponent::TriggerOnSwordAttack()
{
	// Broadcastuje delegata, który może zostać subskrybowany przez inne klasy
	OnSwordAttack.Broadcast(FInputActionValue());
	
}



void UAttackSystemComponent::ResetAttack()
{
	// Resetowanie stanu ataku
   // UE_LOG(LogTemp, Warning, TEXT("Resetting attack. Current AttackIndex = %d"), AttackIndex);
    AnimationsLock.Init(false, AnimationsLock.Num());
	isAttacking = false;
	AttackIndex = 0; // Reset combo
    AlreadyDamagedActors.Empty();

    /*if (AttackComboTimerHandle.IsValid())
    {
        GetWorld()->GetTimerManager().ClearTimer(AttackComboTimerHandle);
    }*/

}

void UAttackSystemComponent::SwordTraceLoop()
{
    FVector Location1 = ArrowTopPoint->GetComponentLocation();
    FVector Location2 = ArrowBottomPoint->GetComponentLocation();
    FVector Location3 = ArrowSpherePoint->GetComponentLocation();
    if (!ArrowTopPoint || !ArrowBottomPoint) return;
    
    PerformSphereTrace(GetWorld(), Location1, Location2, 12.0f, ECC_Pawn);
    PerformSphereTrace(GetWorld(), Location3, Location3, 36.0f, ECC_Pawn);

}

void UAttackSystemComponent::SwordTraceLoopKick()
{
    
    FVector Location3 = ArrowSpherePoint->GetComponentLocation();
    if (!ArrowTopPoint || !ArrowBottomPoint) return;

    
    PerformSphereTrace(GetWorld(), Location3, Location3, 36.0f, ECC_Pawn);

}

void UAttackSystemComponent::StartSwordTrace()
{
    StartAttackComboTimer();
}


void UAttackSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UAttackSystemComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Możesz zarejestrować dodatkowe akcje wejściowe, jeśli to konieczne
}

void UAttackSystemComponent::StartAttackComboTimer()
{
    GetWorld()->GetTimerManager().SetTimer(
        AttackComboTimerHandle,     // Uchwyt timera
        this,                       // Obiekt
        &UAttackSystemComponent::SwordTraceLoop, // Funkcja, która zostanie wywołana
        0.02f,                       // Czas w sekundach
        true                      // cycling timer
    );

    UE_LOG(LogTemp, Warning, TEXT("Attack Combo Timer Started!"));
}

void UAttackSystemComponent::StopAttackComboTimer()
{
    if (GetWorld()->GetTimerManager().IsTimerActive(AttackComboTimerHandle))
    {
        GetWorld()->GetTimerManager().ClearTimer(AttackComboTimerHandle);
        UE_LOG(LogTemp, Warning, TEXT("Attack Combo Timer Stopped!"));
    }
}

void UAttackSystemComponent::OnAttackComboTimerEnd()
{
    UE_LOG(LogTemp, Warning, TEXT("Attack Combo Timer Ended!"));
}

void UAttackSystemComponent::PerformSphereTrace(UWorld* World, FVector Start, FVector End, float Radius, ECollisionChannel TraceChannel)
{
    if (!World)
    {
        return;
    }

    // Parametry kolizji
    FCollisionQueryParams TraceParams(FName(TEXT("CapsuleTraceMulti")), true);
    TraceParams.bTraceComplex = true;
    TraceParams.AddIgnoredActor(GetOwner()); // Ignorowanie właściciela

    // Wyniki śladu
    TArray<FHitResult> HitResults;

    FVector Direction = End - Start;
    float Length = Direction.Size();
    Direction.Normalize();

    const float CapsuleLength = Length;
    FRotator rotation = UKismetMathLibrary::FindLookAtRotation(Start, End).Add(90, 0, 0);
    FVector CapsuleCenter = (Start + End) * 0.5f;

    // Wykonaj wiele trafień
    bool bHit = World->SweepMultiByChannel(
        HitResults,
        Start,
        End,
        rotation.Quaternion(),
        TraceChannel,
        FCollisionShape::MakeCapsule(Radius, CapsuleLength),
        TraceParams
    );

    if (UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
    {
        bDebugMode = MyGameInstance->bDebug;
    }
    if (bDebugMode)
    {
        FColor LineColor = bHit ? FColor::Red : FColor::Green;
        DrawDebugCapsule(
            World,
            CapsuleCenter,
            CapsuleLength * 0.5f,
            Radius,
            rotation.Quaternion(),
            LineColor,
            false,
            0.1f
        );
    }

    // Zbiór do przechowywania już trafionych aktorów (uniknięcie wielokrotnego przetwarzania)
    

    // Obsługa wyników
    if (bHit)
    {
        
        for (const FHitResult& Hit : HitResults)
        {
            AActor* HitActor = Hit.GetActor();
            if (HitActor && !AlreadyDamagedActors.Contains(HitActor))
            {
                UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s at Location: %s"),
                    *HitActor->GetName(),
                    *Hit.ImpactPoint.ToString());
                AlreadyDamagedActors.Add(HitActor); // Dodaj aktora do listy trafionych
                UStatComponent* Damagable = HitActor->FindComponentByClass<UStatComponent>();
                if (Damagable)
                {
                    Damagable->GetDamaged(10); // Zadaj obrażenia
                }
            }
        }
    }
}


