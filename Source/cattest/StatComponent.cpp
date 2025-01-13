// Fill out your copyright notice in the Description page of Project Settings.


#include "StatComponent.h"

// Sets default values for this component's properties
UStatComponent::UStatComponent()
{
    CattestCharacter = Cast<AcattestCharacter>(GetOwner());
    m_currentHealth = 50;
    m_maxHealth = 100;
    m_currentEnergy = 50;
    m_maxEnergy = 100;
    m_healthRegen = 1;
    m_energyRegen = 10;
    m_sprintSpeed = 1000;
    m_baseSpeed = 600;
    m_currentExp = 0;
    m_lvl = 1;
    m_maxExp =100;

    bIsDead = false;
    bIsSprinting = false;
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UStatComponent::BeginPlay()
{
    Super::BeginPlay();
    GetWorld()->GetTimerManager().SetTimer(OneSecTimer, this, &UStatComponent::GetRegen, 1.0f, true);
    // Uzyskaj referencjê do postaci (actor) - zak³adaj¹c, ¿e komponent jest do³¹czony do postaci
   
}

// Called every frame
void UStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    AcattestCharacter* CharacterOwner = Cast<AcattestCharacter>(GetOwner());
    
    

    if (CharacterOwner && CharacterOwner->MyWidget && (!HealthBar && !EnergyBar && !ExpBar))
    {
        // Rzutuj MyWidget na klasê BP_HUD
        UUserWidget* MyHUD = CharacterOwner->MyWidget;

        // ZnajdŸ HealthBar i StaminaBar w BP_HUD
        HealthBar = Cast<UProgressBar>(MyHUD->GetWidgetFromName(TEXT("HealthBar")));
        EnergyBar = Cast<UProgressBar>(MyHUD->GetWidgetFromName(TEXT("EnergyBar")));
        ExpBar = Cast<UProgressBar>(MyHUD->GetWidgetFromName(TEXT("ExpBar")));
        if (HealthBar)
        {
            UE_LOG(LogTemp, Warning, TEXT("HealthBar zosta³ przypisany!"));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Nie uda³o siê znaleŸæ HealthBar!"));
        }
       
    }
    

}

void UStatComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponentc) {

    if (UEnhancedInputComponent* EnhancedInputComponent = GetOwner()->GetComponentByClass<UEnhancedInputComponent>())
    {
        EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this,
            &UStatComponent::Sprint);
        
    }

}

void UStatComponent::Sprint(const FInputActionValue& Value)
{
    AcattestCharacter* CharacterOwner = Cast<AcattestCharacter>(GetOwner()); // Pobieramy w³aœciciela komponentu (Actor)
    if (CharacterOwner->GetIsCrouching()) {
        return;
    }
    // Sprawdzenie, czy w³aœciciel komponentu jest prawid³owy
    if (!CharacterOwner)
    {
        UE_LOG(LogTemp, Error, TEXT("Owner is not a valid ACharacter!"));
        return; // Zatrzymanie funkcji, jeœli w³aœciciel nie jest poprawny
    }

    if (!bIsSprinting) // Sprawdzenie, czy postaæ nie jest ju¿ w trybie sprintu
    {
        bIsSprinting = true;

        // Zmieñ prêdkoœæ ruchu
        CharacterOwner->GetCharacterMovement()->MaxWalkSpeed = m_sprintSpeed;

        // Zmieñ skalê postaci (jeœli chcesz, np. zmniejszaj¹c j¹ podczas sprintu)

        UE_LOG(LogTemp, Log, TEXT("%s is now sprinting"), *GetName());
    }
    else if (bIsSprinting) // Sprawdzenie, czy postaæ jest w trybie sprintu
    {
        bIsSprinting = false;

        // Przywróæ normaln¹ prêdkoœæ ruchu
        CharacterOwner->GetCharacterMovement()->MaxWalkSpeed = m_baseSpeed;

        // Przywróæ normaln¹ skalê postaci (jeœli zmienia³a siê wczeœniej)

        UE_LOG(LogTemp, Log, TEXT("%s has stopped sprinting"), *GetName());
    }
}


void UStatComponent::GetHealed2(int val)
{
    if (bIsDead) {
        return;
    }
    
    m_currentHealth += val;
    if (m_currentHealth > m_maxHealth)
    {
        m_currentHealth = m_maxHealth;
    }

    float HealthPercentage = (float)m_currentHealth / m_maxHealth;
    
    if (HealthBar)
    {
        HealthBar->SetPercent(HealthPercentage);
    }

    // Uzyskaj dostêp do postaci

};

void UStatComponent::GetDamaged2(int val)
{
    if (bIsDead) {
        return;
    }

    m_currentHealth -= val;
    if (m_currentHealth <= 0 && !bIsDead)
    {
        m_currentHealth = 0;
        bIsDead = true;
        if (APlayerController* PlayerController = Cast<APlayerController>(CattestCharacter->GetController()))
        {
            if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
            {
                Subsystem->ClearAllMappings();
                UE_LOG(LogTemp, Log, TEXT("Player input disabled using Enhanced Input."));
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to access Enhanced Input Subsystem."));
            }
            if (USkeletalMeshComponent* Mesh = CattestCharacter->GetMesh())
            {
                Mesh->SetSimulatePhysics(true); // W³¹cz symulacjê fizyki
                Mesh->SetCollisionProfileName(TEXT("Ragdoll")); // Ustaw profil kolizji
                UE_LOG(LogTemp, Log, TEXT("Physics simulation enabled for the player mesh."));
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to access player mesh."));
            }
        }
    }

    float HealthPercentage = (float)m_currentHealth / m_maxHealth;

    if (HealthBar)
    {
        HealthBar->SetPercent(HealthPercentage);
    }

    // Uzyskaj dostêp do postaci

};
// pod otrzymywanie obrazen
void UStatComponent::PlayMontage() {
   // UE_LOG(LogTemp, Warning, TEXT("INDEX %d"), AttackIndex);

           // AnimationsLock[] = true;
    
    if (GetOwner()->FindComponentByClass<USkeletalMeshComponent>()->GetAnimInstance())
    {
        UE_LOG(LogTemp, Error, TEXT("skeletam mesh istnieje!"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("GetOwner() returned nullptr!"));
    }

    if (UAnimInstance* AnimInstance = GetOwner()->FindComponentByClass<USkeletalMeshComponent>()->GetAnimInstance())
    {

        AnimInstance->Montage_Play(ReactDamageMontages[0]);
        UE_LOG(LogTemp, Error, TEXT("montage played"));
    }
    else {
        UE_LOG(LogTemp, Error, TEXT("montage played indcorrecctly"));
    }
                
           
      
}

void UStatComponent::GetDamaged(int DamageAmount)
{
    if (bIsDead) {
        return;
    }

    m_currentHealth -= DamageAmount;

    if (m_currentHealth <= 0 && !bIsDead)
    {
        m_currentHealth = 0;
        bIsDead = true;

        // Pobierz w³aœciciela tego komponentu
        AActor* OwnerActor = GetOwner();
        if (!OwnerActor)
        {
            UE_LOG(LogTemp, Error, TEXT("StatComponent does not have an owner!"));
            return;
        }

        // SprawdŸ, czy w³aœciciel jest graczem
        if (APlayerController* PlayerController = Cast<APlayerController>(OwnerActor->GetInstigatorController()))
        {
            // Wy³¹cz wejœcie dla gracza
            if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
            {
                Subsystem->ClearAllMappings();
                UE_LOG(LogTemp, Log, TEXT("Player input disabled using Enhanced Input."));
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to access Enhanced Input Subsystem."));
            }
        }

        // Obs³uga fizyki dla ka¿dego aktora z meshem
        if (USkeletalMeshComponent* Mesh = OwnerActor->FindComponentByClass<USkeletalMeshComponent>())
        {
            Mesh->SetSimulatePhysics(true); // W³¹cz symulacjê fizyki
            Mesh->SetCollisionProfileName(TEXT("Ragdoll")); // Ustaw profil kolizji
            UE_LOG(LogTemp, Log, TEXT("Physics simulation enabled for the actor mesh."));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to access actor mesh."));

        }
    }
    else if (m_currentHealth > 0 && !bIsDead) {
        UE_LOG(LogTemp, Error, TEXT("MONTAGE HIT"));
        PlayMontage();
        AActor* Owner = GetOwner();
        if (Owner)
        {
            // Ustaw now¹ lokalizacjê w³aœciciela
            
            Owner->SetActorLocation(NewLocation);
        }
    }

    float HealthPercentage = (float)m_currentHealth / m_maxHealth;

    if (HealthBar)
    {
        HealthBar->SetPercent(HealthPercentage);
    }

    // Uzyskaj dostêp do postaci

};

void UStatComponent::GetRegen()
{
    if (bIsDead) {
        return;
    }
    
    m_currentHealth += m_healthRegen;
    if (m_currentHealth > m_maxHealth)
    {
        m_currentHealth = m_maxHealth;
    }
    if (!bIsSprinting) {
        m_currentEnergy += m_energyRegen;
        if (m_currentEnergy > m_maxEnergy)
        {
            m_currentEnergy = m_maxEnergy;
        }
    }
    if (bIsSprinting) {
        m_currentEnergy -= 10;
        if (m_currentEnergy <= 0) {
            m_currentEnergy = 0; 
            ACharacter* CharacterOwner = Cast<ACharacter>(GetOwner()); // Pobieramy w³aœciciela komponentu (Actor)
            bIsSprinting = false;
            CharacterOwner->GetCharacterMovement()->MaxWalkSpeed = m_baseSpeed;
        }
    }

    float HealthPercentage = (float)m_currentHealth / m_maxHealth;
    float EnergyPercentage = (float)m_currentEnergy / m_maxEnergy;
    if (HealthBar)
    {
        HealthBar->SetPercent(HealthPercentage);
    }
    if (EnergyBar)
    {
        EnergyBar->SetPercent(EnergyPercentage);
    }
}

void UStatComponent::GetExp(int val)
{


    m_currentExp += val;
    if (m_currentExp > m_maxExp)
    {
        m_currentExp -= m_maxExp;
        m_lvl++;
        m_maxExp *= 2;
    }
    
    
    float ExpPercentage = (float)m_currentExp / m_maxExp;
    
    if (ExpBar)
    {
        ExpBar->SetPercent(ExpPercentage);
    }
    
}


// Gettery i settery dla Health
int UStatComponent::GetCurrentHealth() const { return m_currentHealth; }
void UStatComponent::SetCurrentHealth(int NewHealth) { m_currentHealth = NewHealth; }

int UStatComponent::GetMaxHealth() const { return m_maxHealth; }
void UStatComponent::SetMaxHealth(int NewMaxHealth) { m_maxHealth = NewMaxHealth; }

int UStatComponent::GetHealthRegen() const { return m_healthRegen; }
void UStatComponent::SetHealthRegen(int NewHealthRegen) { m_healthRegen = NewHealthRegen; }

// Gettery i settery dla Energy
int UStatComponent::GetCurrentEnergy() const { return m_currentEnergy; }
void UStatComponent::SetCurrentEnergy(int NewEnergy) { m_currentEnergy = NewEnergy; }

int UStatComponent::GetMaxEnergy() const { return m_maxEnergy; }
void UStatComponent::SetMaxEnergy(int NewMaxEnergy) { m_maxEnergy = NewMaxEnergy; }

int UStatComponent::GetEnergyRegen() const { return m_energyRegen; }
void UStatComponent::SetEnergyRegen(int NewEnergyRegen) { m_energyRegen = NewEnergyRegen; }

// Gettery i settery dla Armor
int UStatComponent::GetArmor() const { return m_armor; }
void UStatComponent::SetArmor(int NewArmor) { m_armor = NewArmor; }

// Gettery i settery dla Speed
int UStatComponent::GetSpeed() const { return m_speed; }
void UStatComponent::SetSpeed(int NewSpeed) { m_speed = NewSpeed; }

// Gettery i settery dla Base Stats
int UStatComponent::GetBaseMaxHealth() const { return m_baseMaxHealth; }
void UStatComponent::SetBaseMaxHealth(int NewBaseMaxHealth) { m_baseMaxHealth = NewBaseMaxHealth; }

int UStatComponent::GetBaseEnergy() const { return m_baseEnergy; }
void UStatComponent::SetBaseEnergy(int NewBaseEnergy) { m_baseEnergy = NewBaseEnergy; }

int UStatComponent::GetBaseArmor() const { return m_baseArmor; }
void UStatComponent::SetBaseArmor(int NewBaseArmor) { m_baseArmor = NewBaseArmor; }

int UStatComponent::GetBaseHpRegen() const { return m_baseHpRegen; }
void UStatComponent::SetBaseHpRegen(int NewBaseHpRegen) { m_baseHpRegen = NewBaseHpRegen; }

int UStatComponent::GetBaseSpeed() const { return m_baseSpeed; }
void UStatComponent::SetBaseSpeed(int NewBaseSpeed) { m_baseSpeed = NewBaseSpeed; }

// Gettery i settery dla Attributes
uint8 UStatComponent::GetStrength() const { return m_str; }
void UStatComponent::SetStrength(uint8 NewStrength) { m_str = NewStrength; }

uint8 UStatComponent::GetDexterity() const { return m_dex; }
void UStatComponent::SetDexterity(uint8 NewDexterity) { m_dex = NewDexterity; }

uint8 UStatComponent::GetWisdom() const { return m_wis; }
void UStatComponent::SetWisdom(uint8 NewWisdom) { m_wis = NewWisdom; }

uint8 UStatComponent::GetConstitution() const { return m_con; }
void UStatComponent::SetConstitution(uint8 NewConstitution) { m_con = NewConstitution; }

uint8 UStatComponent::GetLuck() const { return m_lck; }
void UStatComponent::SetLuck(uint8 NewLuck) { m_lck = NewLuck; }

// Gettery i settery dla Exp i Level
int UStatComponent::GetExp() const { return m_currentExp; }
void UStatComponent::SetExp(int NewExp) { m_currentExp = NewExp; }

int UStatComponent::GetMaxExp() const { return m_maxExp; }
void UStatComponent::SetMaxExp(int NewMaxExp) { m_maxExp = NewMaxExp; }

int UStatComponent::GetLvl() const { return m_lvl; }
void UStatComponent::SetLvl(int NewLvl) { m_lvl = NewLvl; }