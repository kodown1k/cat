 #include "BaseNPC.h"
#include "Engine/DataTable.h"

// Konstruktor
ABaseNPC::ABaseNPC()
{
    // Inicjalizacja systemu dialogowego
    DialogueSystem = CreateDefaultSubobject<UDialogueSystem>(TEXT("DialogueSystem"));
    //ini nazw npc
    InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
    InteractionWidget->SetupAttachment(RootComponent);

    // Ustawienia Widget Componentu
    InteractionWidget->SetWidgetSpace(EWidgetSpace::Screen); // Wy�wietla widget jako 2D UI
    InteractionWidget->SetDrawSize(FVector2D(200, 50)); // Rozmiar
    InteractionWidget->SetVisibility(false); // Ukryty na starci
    UE_LOG(LogTemp, Warning, TEXT("stworzono widget nazw npc"));
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
    
    bIsDialogueActive = true;
    // �adujemy dane dialogowe i wy�wietlamy widget
    DialogueSystem->LoadDialogueData(DialogueDataTable, NPC_ID, DialogueWidgetClass);
    
}

// Funkcja do wczytania danych dialogowych


void ABaseNPC::SetNPCName(const FString& Name)
{
   
}


// Funkcja wywo�ywana, gdy NPC pojawi si� w �wiecie gry
void ABaseNPC::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("1"));
    //USTAW WIDGET NPCA NA POCZATKU GRY
    //__________________________________
    UE_LOG(LogTemp, Log, TEXT("ABaseNPC: BeginPlay()"));

    if (UUserWidget* Widget = Cast<UUserWidget>(InteractionWidget->GetWidget()))
    {
        if (Widget)
        {
            UTextBlock* TextBlock = Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("InteractionTextBlock")));
            if (TextBlock)
            {
                TextBlock->SetText(FText::FromString(TEXT("Nacisnij F")));
            }
        }
    }

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

void ABaseNPC::SetInteractionText(const FText& NewText)
{
    if (UUserWidget* Widget = Cast<UUserWidget>(InteractionWidget->GetWidget()))
    {
        UTextBlock* TextBlock = Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("InteractionTextBlock")));
        if (TextBlock)
        {
            TextBlock->SetText(NewText);
        }
    }
}

void ABaseNPC::ShowInteractionWidget(bool bShow)
{
    if (InteractionWidget)
    {
        // Je�eli widget jest przypisany, ustawiamy widoczno��
        InteractionWidget->SetVisibility(bShow);

        if (bShow)
        {
            UE_LOG(LogTemp, Log, TEXT("Pokazuj� widget interakcji!"));
        }
        else
        {
            UE_LOG(LogTemp, Log, TEXT("Ukrywam widget interakcji."));
        }
    }
    else
    {
        // Loguj, �e widget jest null
        UE_LOG(LogTemp, Warning, TEXT("Widget interakcji nie jest przypisany!"));
    }
}


void ABaseNPC::Interact_Implementation()
{
    // Wykonaj logik� interakcji, np. uruchomienie dialogu, zmiana stanu
    UE_LOG(LogTemp, Log, TEXT("Interakcja z %s"), *GetName());
}

// Implementacja funkcji GetInteractionText
FText ABaseNPC::GetInteractionText_Implementation() const
{
    // Zwr�� tekst, kt�ry ma by� pokazany w interakcji
    return InteractionText;
}