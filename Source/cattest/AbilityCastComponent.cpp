#include "AbilityCastComponent.h"
#include "EnhancedInputComponent.h"

// Sets default values for this component's properties
UAbilityCastComponent::UAbilityCastComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    CurrentSpell = nullptr;
}

void UAbilityCastComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UAbilityCastComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UAbilityCastComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    if (UEnhancedInputComponent* EnhancedInputComponent = GetOwner()->GetComponentByClass<UEnhancedInputComponent>())
    {
        

        EnhancedInputComponent->BindAction(CastAbilityAction, ETriggerEvent::Triggered, this, &UAbilityCastComponent::CastCurrentSpell);

    }
}





void UAbilityCastComponent::CastCurrentSpell()
{
    AcattestCharacter* CharacterOwner = Cast<AcattestCharacter>(GetOwner());
    if (CharacterOwner) {
        UE_LOG(LogTemp, Warning, TEXT("cast0"));
    }
    UE_LOG(LogTemp, Warning, TEXT("cast1"));
    if (CurrentSpell) // Sprawdzenie, czy mamy przypisan� klas� czaru
    {
        // Tworzymy instancj� czaru na podstawie klasy (czyli np. Fireball)
        USpellBase* SpellInstance = NewObject<USpellBase>(this, CurrentSpell);
        UE_LOG(LogTemp, Warning, TEXT("cast2"));
        // Sprawdzamy, czy instancja czaru zosta�a poprawnie stworzona
        if (SpellInstance)
        {
            UE_LOG(LogTemp, Warning, TEXT("cast3"));
            // Wywo�ujemy metod� CastSpell na nowej instancji czaru
            AActor* OwnerActor = GetOwner(); // Pobieramy w�a�ciciela komponentu
            SpellInstance->CastSpell(OwnerActor);
        }
    }
}

void UAbilityCastComponent::SetCurrentSpell(TSubclassOf<USpellBase> NewSpell)
{
    if (NewSpell) // Sprawdzamy, czy przekazany czar nie jest nullem
    {
        CurrentSpell = NewSpell; // Przypisanie nowego czaru
    }
}