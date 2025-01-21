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
    if (CastAbilityAction) {
        if (UEnhancedInputComponent* EnhancedInputComponent = GetOwner()->GetComponentByClass<UEnhancedInputComponent>())
        {
            EnhancedInputComponent->BindAction(CastAbilityAction, ETriggerEvent::Triggered, this, &UAbilityCastComponent::CastCurrentSpell);
        }
    }
}

void UAbilityCastComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    // Mo¿esz dodaæ logikê sprawdzaj¹c¹ cooldown w tej funkcji
}

void UAbilityCastComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
   
}

void UAbilityCastComponent::CastCurrentSpell()
{
    UE_LOG(LogTemp, Warning, TEXT("test!"));
    // SprawdŸ, czy cooldown min¹³
    if (GetWorld()->GetTimeSeconds() - LastCastTime < CooldownTime)
    {
        UE_LOG(LogTemp, Warning, TEXT("Ability is on cooldown!"));
        return;
    }

    AcattestCharacter* CharacterOwner = Cast<AcattestCharacter>(GetOwner());
    if (CharacterOwner)
    {
        UE_LOG(LogTemp, Warning, TEXT("Casting spell!"));
    }

    // Sprawdzenie, czy mamy przypisan¹ klasê czaru
    if (CurrentSpell)
    {
        // Tworzymy instancjê czaru na podstawie klasy (czyli np. Fireball)
        USpellBase* SpellInstance = NewObject<USpellBase>(this, CurrentSpell);
        if (SpellInstance)
        {
            // Wywo³ujemy metodê CastSpell na nowej instancji czaru
            AActor* OwnerActor = GetOwner(); // Pobieramy w³aœciciela komponentu
            SpellInstance->CastSpell(OwnerActor);

            // Ustawiamy czas ostatniego rzucenia
            LastCastTime = GetWorld()->GetTimeSeconds();
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to create spell instance."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No spell assigned!"));
    }
}

void UAbilityCastComponent::SetCurrentSpell(TSubclassOf<USpellBase> NewSpell)
{
    if (NewSpell) // Sprawdzamy, czy przekazany czar nie jest nullem
    {
        CurrentSpell = NewSpell; // Przypisanie nowego czaru
        UE_LOG(LogTemp, Warning, TEXT("New spell set!"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid spell!"));
    }
}
