 #include "BaseNPC.h"
#include "Engine/DataTable.h"

// Konstruktor
ABaseNPC::ABaseNPC()
{
    // Inicjalizacja systemu dialogowego
    DialogueSystem = CreateDefaultSubobject<UDialogueSystem>(TEXT("DialogueSystem"));
    
    // Ustawienie warto�ci domy�lnych
    NPC_ID = 0;
}

// Funkcja rozpoczynaj�ca dialog
void ABaseNPC::StartDialogue()
{
    // Logika rozpocz�cia dialogu
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
    

    // �adujemy dane dialogowe i wy�wietlamy widget
    DialogueSystem->LoadDialogueData(DialogueDataTable, NPC_ID, DialogueWidgetClass);
    DialogueSystem->ShowDialogueWidget();
}

// Funkcja do wczytania danych dialogowych


// Funkcja wywo�ywana, gdy NPC pojawi si� w �wiecie gry
void ABaseNPC::BeginPlay()
{
    Super::BeginPlay();

    // Mo�esz tu doda� logik� uruchamiaj�c� dialog od razu lub po interakcji.
}

// Funkcja wywo�ywana co klatk�
void ABaseNPC::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Funkcja przypisuj�ca wej�cia gracza
void ABaseNPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}
