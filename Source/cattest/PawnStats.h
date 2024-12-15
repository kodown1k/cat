// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ProgressBar.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "cattestCharacter.h"

#include "PawnStats.generated.h"

#define GENERATE_GETTER_SETTER(type, name) \
    UFUNCTION(BlueprintCallable, Category = "Stats") \
    type Get##name() const { return name; } \
    UFUNCTION(BlueprintCallable, Category = "Stats") \
    void Set##name(type value) { name = value; }

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CATTEST_API UPawnStats : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UPawnStats();

    // Zmienna i jej getter/setter
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int m_currentHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int m_maxHealth;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int m_energy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int m_armor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int m_hpRegen;

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

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int m_baseSpeed;

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

    void GetHealed2(int val);
    
    void GetDamaged2(int val);
    void AffectRegeneration(int val);
    void AffectSpeed(int val);

   
    

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

    bool m_deathStatus; // bedziemy sprawdzac po otrzymaniu dmg czy zycie nie spadlo ponizej 0;
    bool zatrzask;
    bool buff1;
    bool debuff1;

public:
    // Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(EditAnywhere, meta = (BindWidget));
    class UProgressBar* HealthBar;

    UPROPERTY(EditAnywhere, meta = (BindWidget));
    class UProgressBar* EnergyBar;
    UPROPERTY(EditAnywhere, meta = (BindWidget));
    UUserWidget* MyWidget;
    

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> WidgetBlueprintClass;

};

