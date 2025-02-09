// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AttackSystem/DamageInterface.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputModule.h"

#include "cattestCharacter.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/ProgressBar.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "StatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CATTEST_API UStatComponent : public UActorComponent, public IDamageInterface
{
	GENERATED_BODY()

    
public:	
	// Sets default values for this component's properties
	UStatComponent();

    

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int m_currentHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int m_maxHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int m_healthRegen;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int m_maxEnergy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int m_currentEnergy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int m_energyRegen;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int m_armor;

    

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int m_speed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int m_baseMaxHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int m_baseEnergy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int m_baseArmor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int m_baseHpRegen;

    //speed 

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int m_baseSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int m_sprintSpeed;


    // Nowe zmienne
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int m_currentExp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int m_maxExp;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int m_lvl;


    // Zmienna uint8 zamiast uint8_t
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    uint8 m_str;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    uint8 m_dex;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    uint8 m_wis;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    uint8 m_con;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    uint8 m_lck;

    AcattestCharacter* CattestCharacter;
   
    //AKCJE

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* SprintAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    TArray<UAnimMontage*> ReactDamageMontages;
    
    

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

    void PlayMontage();
    TArray<bool> AnimationsLock;
    

    FTimerHandle OneSecTimer;

	UPROPERTY(BlueprintReadWrite)
    UProgressBar* HealthBar;
	UPROPERTY()
    UProgressBar* EnergyBar;
	UPROPERTY()
    UProgressBar* ExpBar;

    bool bIsSprinting;
    bool bIsDead;

	void RefreshHealthBar() const;
    
    

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
    void GetHealed2(int val);
    void GetRegen();
    virtual void GetDamaged(int DamageAmount) override;
	UFUNCTION(BlueprintCallable)
    void AddDamaged(int val);
    void AffectRegeneration(int val);
    void AffectSpeed(int val);
    void GetExp(int val);

    void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);
    void Sprint(const FInputActionValue& Value);
    

     


     //gettery i settery
	UFUNCTION(BlueprintGetter)
     int GetCurrentHealth() const;
	UFUNCTION(BlueprintSetter)
     void SetCurrentHealth(int NewHealth);

     int GetMaxHealth() const;
     void SetMaxHealth(int NewMaxHealth);

     int GetHealthRegen() const;
     void SetHealthRegen(int NewHealthRegen);

     // Energy
     int GetCurrentEnergy() const;
     void SetCurrentEnergy(int NewEnergy);

     int GetMaxEnergy() const;
     void SetMaxEnergy(int NewMaxEnergy);

     int GetEnergyRegen() const;
     void SetEnergyRegen(int NewEnergyRegen);

     // Armor
     int GetArmor() const;
     void SetArmor(int NewArmor);

     // Speed
     int GetSpeed() const;
     void SetSpeed(int NewSpeed);

     // Base Stats
     int GetBaseMaxHealth() const;
     void SetBaseMaxHealth(int NewBaseMaxHealth);

     int GetBaseEnergy() const;
     void SetBaseEnergy(int NewBaseEnergy);

     int GetBaseArmor() const;
     void SetBaseArmor(int NewBaseArmor);

     int GetBaseHpRegen() const;
     void SetBaseHpRegen(int NewBaseHpRegen);

     int GetBaseSpeed() const;
     void SetBaseSpeed(int NewBaseSpeed);

     // Attributes
     uint8 GetStrength() const;
     void SetStrength(uint8 NewStrength);

     uint8 GetDexterity() const;
     void SetDexterity(uint8 NewDexterity);

     uint8 GetWisdom() const;
     void SetWisdom(uint8 NewWisdom);

     uint8 GetConstitution() const;
     void SetConstitution(uint8 NewConstitution);

     uint8 GetLuck() const;
     void SetLuck(uint8 NewLuck);

     // Exp and Level
     int GetExp() const;
     void SetExp(int NewExp);

     int GetMaxExp() const;
     void SetMaxExp(int NewMaxExp);

     int GetLvl() const;
     void SetLvl(int NewLvl);
};
