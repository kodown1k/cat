// Fill out your copyright notice in the Description page of Project Settings.


#include "StoryComponent.h"


#include "NameableInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "Components/WidgetComponent.h"

// Sets default values for this component's properties
UStoryComponent::UStoryComponent()
{
    canPerformRaycast = true;	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
    QuestManager = CreateDefaultSubobject<AQuestManager>(TEXT("QuestManager"));
    UE_LOG(LogTemp, Warning, TEXT("QuestManager zosta³ stworzony dynamicznie!"));
	// ...
    
}

void UStoryComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	
}






// Called when the game starts
void UStoryComponent::BeginPlay()
{
    Super::BeginPlay();

    // Indeks 0 oznacza gracza nr 1 (w grze jednoosobowej)
    
    if (QuestManager)
    {
        UE_LOG(LogTemp, Warning, TEXT("QuestManager znaleziony w StoryComponent!"));
        if (QuestManagerDatatable)
        {
            QuestManager->SetQuestDataTable(QuestManagerDatatable);
            UE_LOG(LogTemp, Warning, TEXT("Zaladowano QuestDataTable"));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("QuestManagerDatatable jest NULL!"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Brak QuestManagera w StoryComponent!"));
    }

    if (InteractAction) {
        if (UEnhancedInputComponent* EnhancedInputComponent = GetOwner()->GetComponentByClass<UEnhancedInputComponent>())
        {
            EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this,
                &UStoryComponent::Interact);

        }
    }
    UE_LOG(LogTemp, Warning, TEXT("Zbindowano ia_togglemenu"));
    if (MenuAction) {
        if (UEnhancedInputComponent* EnhancedInputComponent = GetOwner()->GetComponentByClass<UEnhancedInputComponent>())
        {
            EnhancedInputComponent->BindAction(MenuAction, ETriggerEvent::Triggered, this,
                &UStoryComponent::OpenMenuWidget);
            UE_LOG(LogTemp, Warning, TEXT("Zbindowano ia_togglemenu"));
        }
    }

    if (QuestLogWidgetClass)
    {
        // Tworzymy instancjê widgetu, ale nie dodajemy go od razu do widoku
        QuestLogWidget = CreateWidget<UQuestJournal>(GetWorld(), QuestLogWidgetClass);

        if (QuestLogWidget)
        {
            QuestLogWidget->AddToViewport();
            QuestLogWidget->SetVisibility(ESlateVisibility::Hidden);
            UE_LOG(LogTemp, Warning, TEXT("QuestLogWidget created successfully!"));

        }


    }

    
    
    
    
        UE_LOG(LogTemp, Warning, TEXT("QuestManager initialized!"));

        // Przyk³adowy quest na start
        FQuestStruct1 NewQuest;
        NewQuest.QuestName = "Zbierz 5 jab³ek";
        NewQuest.RequiredAmount = 5;
        NewQuest.CurrentProgress = 0;

        QuestManager->GiveQuest(NewQuest);
        
    

    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UStoryComponent::InteractWithWorld, 0.2f, true);
}


// Called every frame
void UStoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
}

void UStoryComponent::InteractWithWorld() {

    
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PlayerController)
    {
        FVector CameraLocation;
        FRotator CameraRotation;

        // Pobierz lokalizacjê kamery gracza oraz kierunek patrzenia
        PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);
        
        // Pocz¹tek raycasta to pozycja gracza, a kierunek to kierunek patrzenia
        FVector StartLocation = GetOwner()->GetActorLocation();  // Pozywcja gracza (kamera)
        FVector ForwardVector = CameraRotation.Vector();  // Kierunek patrzenia (wektor)

        // Okreœlamy punkt koñcowy raycasta (np. 2000 jednostek przed kamer¹)
        FVector EndLocation = StartLocation + (ForwardVector * 300.f);

        FHitResult HitResult;
        FCollisionQueryParams CollisionParams;
        CollisionParams.AddIgnoredActor(GetOwner());  // Ignoruj samego gracza

        // Wykonaj LineTrace (Raycast)
        bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, CollisionParams);

        if (bHit)
        {
            // Próbujemy przekastowaæ aktora na ABaseNPC
            NewHitActor = Cast<ABaseNPC>(HitResult.GetActor());

            if (NewHitActor)
            {
                //UE_LOG(LogTemp, Log, TEXT("Nowy aktor: %s"), *NewHitActor->GetName());

                // Jeœli zmieni³ siê aktor, ukrywamy poprzedni widget
                if (HitActor && HitActor != NewHitActor)
                {
                    UE_LOG(LogTemp, Log, TEXT("Zmieniono aktora. Ukrywanie widgetu poprzedniego aktora: %s"), *HitActor->GetName());

                    // Tylko wtedy, gdy HitActor jest typu ABaseNPC
                    if (ABaseNPC* BaseNPC = Cast<ABaseNPC>(HitActor))
                    {
                        BaseNPC->ShowInteractionWidget(false);
                    }
                }

                HitActor = NewHitActor;

                // Tylko wtedy, gdy NewHitActor jest typu ABaseNPC
                if (NewHitActor)
                {
                    NewHitActor->ShowInteractionWidget(true);
                    UE_LOG(LogTemp, Log, TEXT("Pokazywanie widgetu dla aktora: %s"), *NewHitActor->GetName());
                }
            }
            else
            {
                //UE_LOG(LogTemp, Log, TEXT("Brak interakcji z aktorem"));

                // Jeœli nie ma interakcji, ukryj widget
                if (HitActor)
                {
                    // Sprawdzamy, czy HitActor to ABaseNPC przed wywo³aniem metody
                    if (ABaseNPC* BaseNPC = Cast<ABaseNPC>(HitActor))
                    {
                        BaseNPC->ShowInteractionWidget(false);
                    }

                    HitActor = nullptr;
                }
            }
        }
        else
        {
            if (HitActor)
            {
                //UE_LOG(LogTemp, Log, TEXT("Brak trafienia, ukrywanie widgetu dla aktora: %s"), *HitActor->GetName());

                // Sprawdzamy, czy HitActor to ABaseNPC przed wywo³aniem metody
                if (ABaseNPC* BaseNPC = Cast<ABaseNPC>(HitActor))
                {
                    BaseNPC->ShowInteractionWidget(false);
                }

                HitActor = nullptr;
            }
        }

        // Opcjonalne debugowanie: rysowanie linii w edytorze
#if WITH_EDITOR
        if (bHit)
        {
            DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Blue, false, 1, 0, 1);
        }
        else
        {
            DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 1, 0, 1);
        }
#endif
    }
}

void UStoryComponent::Interact()
{
	// SprawdŸ, czy NPC w zasiêgu
	InteractWithNPC();
    UE_LOG(LogTemp, Log, TEXT("%s trying to interact"), *GetName());
}

void UStoryComponent::InteractWithNPC()
{
    // Pobierz kontroler gracza


            // Sprawdzamy, czy aktor implementuje interfejs IDialogueInterface
    if (HitActor && HitActor->Implements<UDialogueInterface>())
    {
        // Dopiero teraz robimy castowanie, bo wiemy, ¿e aktor implementuje interfejs
        IDialogueInterface* DialogueInterface = Cast<IDialogueInterface>(HitActor);

        if (DialogueInterface)
        {
            // Jeœli trafiliœmy w NPC z interfejsem, rozpoczynamy dialog

            canPerformRaycast = false;
            
                // Zarejestruj funkcjê ResumeRaycastAfterDialogue do delegata OnDialogueClosed w UDialogueSystem
               
            
            DialogueInterface->StartDialogue();
        }
    }


        // Opcjonalne debugowanie: rysowanie linii w edytorze

}




void UStoryComponent::ResumeRaycast()
{
    canPerformRaycast = true;
    UE_LOG(LogTemp, Log, TEXT("Raycast wznowiony!"));
}


void UStoryComponent::OpenMenuWidget()
{
    UE_LOG(LogTemp, Warning, TEXT("Toggle Journal"));
    if (QuestLogWidget)
    {
        // Sprawdzamy aktualn¹ widocznoœæ widgetu
        if (QuestLogWidget->IsVisible())
        {
            // Jeœli widget jest widoczny, ukrywamy go
            UE_LOG(LogTemp, Warning, TEXT("ukryj journal"));
            QuestLogWidget->SetVisibility(ESlateVisibility::Hidden);
        }
        else
        {
            // Jeœli widget nie jest widoczny, pokazujemy go
            UE_LOG(LogTemp, Warning, TEXT("pokaz journal"));
            QuestLogWidget->SetVisibility(ESlateVisibility::Visible);
            ShowQuestLog();
        }
    }
}


void UStoryComponent::ShowQuestLog()
{
    if (QuestLogWidget)
    {
        // Zak³adaj¹c, ¿e masz ju¿ metodê PopulateQuestList w widgetcie
        TArray<FQuestStruct1> ActiveQuests = QuestManager->GetActiveQuests();

        // Wyœwietlenie ich w logu
        for (const FQuestStruct1& Quest : ActiveQuests)
        {
            UE_LOG(LogTemp, Warning, TEXT("Aktualny quest: %s, Postêp: %d/%d"),
                *Quest.QuestName, Quest.CurrentProgress, Quest.RequiredAmount);
        }
        
        QuestLogWidget->PopulateQuestList(ActiveQuests);
        
    }
}

void UStoryComponent::UpdateDataTable(int32 QuestID, bool NewStatus)
{
    if (!QuestManagerDatatable)
    {
        UE_LOG(LogTemp, Error, TEXT("QuestManagerDatatable is NULL!"));
        return;
    }

    static const FString ContextString(TEXT("Quest Data Lookup"));

    // Pobranie wiersza na podstawie QuestID
    FQuestStruct1* QuestRow = QuestManagerDatatable->FindRow<FQuestStruct1>(
        *FString::FromInt(QuestID), ContextString);

    if (QuestRow)
    {
        // Aktualizacja wartoœci w strukturze
        QuestRow->bIsActive = NewStatus;

        UE_LOG(LogTemp, Warning, TEXT("Updated Quest ID: %d, New Active Status: %s"),
            QuestID, QuestRow->bIsActive ? TEXT("True") : TEXT("False"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Quest ID %d not found in DataTable!"), QuestID);
    }
}

bool UStoryComponent::IsQuestActive(int32 QuestID)
{
    if (!QuestManagerDatatable)
    {
        UE_LOG(LogTemp, Error, TEXT("QuestManagerDatatable is NULL!"));
        return false; // Jeœli DataTable nie istnieje, zwracamy false
    }

    static const FString ContextString(TEXT("Quest Data Lookup"));

    // Pobranie wiersza na podstawie QuestID
    FQuestStruct1* QuestRow = QuestManagerDatatable->FindRow<FQuestStruct1>(
        FName(*FString::FromInt(QuestID)), ContextString);

    if (QuestRow)
    {
        UE_LOG(LogTemp, Warning, TEXT("Quest ID: %d, Active Status: %s"),
            QuestID, QuestRow->bIsActive ? TEXT("True") : TEXT("False"));

        return QuestRow->bIsActive; // Zwracamy wartoœæ bIsActive
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Quest ID %d not found in DataTable!"), QuestID);
        return false; // Jeœli quest nie istnieje, zwracamy false
    }
}
