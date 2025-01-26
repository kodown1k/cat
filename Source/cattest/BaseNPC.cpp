 #include "BaseNPC.h"
#include "Engine/DataTable.h"

// Konstruktor
ABaseNPC::ABaseNPC()
{
    // Inicjalizacja systemu dialogowego
    DialogueSystem = CreateDefaultSubobject<UDialogueSystem>(TEXT("DialogueSystem"));
    
    // Ustawienie wartoœci domyœlnych
    NPC_ID = 0;
}

// Funkcja rozpoczynaj¹ca dialog
void ABaseNPC::StartDialogue()
{
    // Logika rozpoczêcia dialogu
    UE_LOG(LogTemp, Log, TEXT("Rozpoczynamy dialog z NPC ID: %d"), NPC_ID);

    if (!DialogueSystem)
    {
        UE_LOG(LogTemp, Warning, TEXT("DialogueSystem is null!"));
        return;
    }

    if (!DialogueDataTable)
    {
        UE_LOG(LogTemp, Warning, TEXT("DialogueDataTable is null!"));
        return;
    }
    //UDataTable* DialogueDataTable, int32 NPC_ID;
    

    // £adujemy dane dialogowe i wyœwietlamy widget
    DialogueSystem->LoadDialogueData(DialogueDataTable, NPC_ID, DialogueWidgetClass);
    DialogueSystem->ShowDialogueWidget();
}

// Funkcja do wczytania danych dialogowych


// Funkcja wywo³ywana, gdy NPC pojawi siê w œwiecie gry
void ABaseNPC::BeginPlay()
{
    Super::BeginPlay();

    // Mo¿esz tu dodaæ logikê uruchamiaj¹c¹ dialog od razu lub po interakcji.
}

// Funkcja wywo³ywana co klatkê
void ABaseNPC::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Funkcja przypisuj¹ca wejœcia gracza
void ABaseNPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}
