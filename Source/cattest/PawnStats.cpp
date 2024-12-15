// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnStats.h"

// Sets default values for this component's properties
UPawnStats::UPawnStats()
{
    m_currentHealth = 50;
    m_maxHealth = 100;
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
    AActor* Owner = GetOwner();
	// ...
    if (Owner)
    {
        CattestCharacter = Cast<AcattestCharacter>(Owner);
    }
}


// Called when the game starts
void UPawnStats::BeginPlay()
{
    Super::BeginPlay();

   
    
}



// Called every frame
void UPawnStats::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    AActor* Owner = GetOwner();

    // Rzutowanie Owner na AcattestCharacter
    //if (zatrzask == false) {
    //    if (Owner)
    //    {
    //        // Sprawdü, czy Owner jest instancjπ AcattestCharacter
    //        CattestCharacter = Cast<AcattestCharacter>(Owner);
    //        if (GEngine)
    //            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "0");
    //        if (CattestCharacter)
    //        {
    //            // Sprawdü, czy CurrentWidget jest ustawione
    //            MyWidget = Cast<UUserWidget>(CattestCharacter->CurrentWidget);
    //            if (GEngine)
    //                GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "1");
    //            if (MyWidget)
    //            {

    //                if (GEngine)
    //                    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "2");
    //                //TU MOZNA PRZYPISYWAC WIDGETY DO ZMIENNYCH;
    //                HealthBar = Cast<UProgressBar>(MyWidget->GetWidgetFromName(TEXT("HealthBar")));

    //                if (HealthBar)
    //                {
    //                    if (GEngine)
    //                        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "3");
    //                    // Ustaw wartoúÊ procentowπ zdrowia
    //                    zatrzask = true;


    //                }
    //                else {

    //                }
    //            }
    //            else {

    //            }
    //        }
    //    }
    //}
    GetHealed2(1);
    
}


void UPawnStats::GetHealed2(int val)
{
    m_currentHealth += val;
    if (m_currentHealth > m_maxHealth)
    {
        m_currentHealth = m_maxHealth;
    }

    float HealthPercentage = (float)m_currentHealth / m_maxHealth;

    // Uzyskaj dostÍp do postaci


    if (CattestCharacter && CattestCharacter->HealthBar)
    {
        // Zaktualizuj wartoúÊ procentowπ paska zdrowia
        CattestCharacter->HealthBar->SetPercent(HealthPercentage);
    }

};


void UPawnStats::GetDamaged2(int val) {
	m_currentHealth -= val;
	if (m_currentHealth <= 0) {
		m_currentHealth = 0;
		m_deathStatus = true;
	}
};


void UPawnStats::AffectRegeneration(int val) {
	m_hpRegen += val;
}
void UPawnStats::AffectSpeed(int val) {
	m_speed += val;
}