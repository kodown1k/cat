#include "InteractableActor.h"
#include "Components/WidgetComponent.h"

// Konstruktor
AInteractableActor::AInteractableActor()
{
    // Ustawienie wartoœci domyœlnych
    PrimaryActorTick.bCanEverTick = true;

    InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
}

// Funkcja wywo³ywana po rozpoczêciu gry
void AInteractableActor::BeginPlay()
{
    Super::BeginPlay();

    // Tutaj mo¿esz dodaæ logikê do pocz¹tkowego ustawienia widgetu
}

// Implementacja funkcji Interact
void AInteractableActor::Interact_Implementation()
{
    // Wykonaj logikê interakcji, np. uruchomienie dialogu, zmiana stanu
    UE_LOG(LogTemp, Log, TEXT("Interakcja z %s"), *GetName());
}

// Implementacja funkcji GetInteractionText
FText AInteractableActor::GetInteractionText_Implementation() const
{
    // Zwróæ tekst, który ma byæ pokazany w interakcji
    return InteractionText;
}