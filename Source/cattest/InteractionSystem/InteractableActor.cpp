#include "InteractableActor.h"
#include "Components/WidgetComponent.h"

// Konstruktor
AInteractableActor::AInteractableActor()
{
    // Ustawienie warto�ci domy�lnych
    PrimaryActorTick.bCanEverTick = true;

    InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
}

// Funkcja wywo�ywana po rozpocz�ciu gry
void AInteractableActor::BeginPlay()
{
    Super::BeginPlay();

    // Tutaj mo�esz doda� logik� do pocz�tkowego ustawienia widgetu
}

// Implementacja funkcji Interact
void AInteractableActor::Interact_Implementation()
{
    // Wykonaj logik� interakcji, np. uruchomienie dialogu, zmiana stanu
    UE_LOG(LogTemp, Log, TEXT("Interakcja z %s"), *GetName());
}

// Implementacja funkcji GetInteractionText
FText AInteractableActor::GetInteractionText_Implementation() const
{
    // Zwr�� tekst, kt�ry ma by� pokazany w interakcji
    return InteractionText;
}