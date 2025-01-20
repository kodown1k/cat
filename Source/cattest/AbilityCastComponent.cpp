#include "AbilityCastComponent.h"
#include "EnhancedInputComponent.h"

// Sets default values for this component's properties
UAbilityCastComponent::UAbilityCastComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    CurrentSpell = nullptr;
    CooldownTime = 3.0f; // Domyœlny cooldown 3 sekundy
    LastCastTime = -CooldownTime; // Pozwala rzuciæ czar od razu po starcie
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
    // SprawdŸ, czy mo¿emy rzuciæ czar (czy cooldown min¹³)
    if (GetWorld()->GetTimeSeconds() - LastCastTime < CooldownTime)
    {
        UE_LOG(LogTemp, Warning, TEXT("Ability is on cooldown!"));
        return;
    }

    AcattestCharacter* CharacterOwner = Cast<AcattestCharacter>(GetOwner());
    if (CharacterOwner) {
        UE_LOG(LogTemp, Warning, TEXT("cast0"));
    }
    UE_LOG(LogTemp, Warning, TEXT("cast1"));
    if (CurrentSpell) // Sprawdzenie, czy mamy przypisan¹ klasê czaru
    {
        // Tworzymy instancjê czaru na podstawie klasy (czyli np. Fireball)
        USpellBase* SpellInstance = NewObject<USpellBase>(this, CurrentSpell);
        UE_LOG(LogTemp, Warning, TEXT("cast2"));
        // Sprawdzamy, czy instancja czaru zosta³a poprawnie stworzona
        if (SpellInstance)
        {
            UE_LOG(LogTemp, Warning, TEXT("cast3"));
            // Wywo³ujemy metodê CastSpell na nowej instancji czaru
            AActor* OwnerActor = GetOwner(); // Pobieramy w³aœciciela komponentu
            SpellInstance->CastSpell(OwnerActor);

            // Ustawiamy czas ostatniego rzucenia
            LastCastTime = GetWorld()->GetTimeSeconds();
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