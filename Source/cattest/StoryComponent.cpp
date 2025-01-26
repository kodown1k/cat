// Fill out your copyright notice in the Description page of Project Settings.


#include "StoryComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UStoryComponent::UStoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UStoryComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = GetOwner()->GetComponentByClass<UEnhancedInputComponent>())
	{
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this,
			&UStoryComponent::Interact);

	}
}




// Called when the game starts
void UStoryComponent::BeginPlay()
{
	Super::BeginPlay();
    if (InteractAction) {
        if (UEnhancedInputComponent* EnhancedInputComponent = GetOwner()->GetComponentByClass<UEnhancedInputComponent>())
        {
            EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this,
                &UStoryComponent::Interact);

        }
    }

    //if (MainMenuWidgetRef)
    //{
    //    // Uzyskaj APlayerController (zak³adaj¹c, ¿e komponent jest przypisany do aktora, który ma kontroler gracza)
    //    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

    //    if (PlayerController)
    //    {
    //        // Stwórz widget za pomoc¹ GameplayStatics
    //        UUserWidget* MainMenuWidget = CreateWidget<UUserWidget>(PlayerController, MainMenuWidgetRef);

    //        if (MainMenuWidget)
    //        {
    //            // Dodaj widget do viewportu
    //            MainMenuWidget->AddToViewport();
    //            UE_LOG(LogTemp, Error, TEXT("Dodant do viewport"));
    //        
    //        }
    //    }
    //    else
    //    {
    //        UE_LOG(LogTemp, Error, TEXT("PlayerController is null."));
    //    }
    //}
    //else
    //{
    //    UE_LOG(LogTemp, Error, TEXT("MainMenuWidgetRef is invalid."));
    //}
    

	// ...
	
}


// Called every frame
void UStoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
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
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0); // Indeks 0 oznacza gracza nr 1 (w grze jednoosobowej)

    if (PlayerController)
    {
        FVector CameraLocation;
        FRotator CameraRotation;

        // Pobierz lokalizacjê kamery gracza oraz kierunek patrzenia
        PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

        // Pocz¹tek raycasta to pozycja gracza, a kierunek to kierunek patrzenia
        FVector StartLocation = GetOwner()->GetActorLocation();  // Pozycja gracza (kamera)
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
            // Sprawdzamy, czy trafiliœmy w obiekt implementuj¹cy nasz interfejs
            if (IDialogueInterface* DialogueInterface = Cast<IDialogueInterface>(HitResult.GetActor()))
            {
                // Jeœli trafiliœmy w NPC z interfejsem, rozpoczynamy dialog
                DialogueInterface->StartDialogue();
            }
        }

        // Opcjonalne debugowanie: rysowanie linii w edytorze
#if WITH_EDITOR
        if (bHit)
        {
            DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, 1, 0, 1);
        }
        else
        {
            DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 1, 0, 1);
        }
#endif
    }
}