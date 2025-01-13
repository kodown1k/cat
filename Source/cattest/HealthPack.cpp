// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPack.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "cattestCharacter.h" // Zast¹p swoj¹ klas¹ gracza
#include "StatComponent.h" // Zast¹p swoj¹ klas¹ komponentu zdrowia


AHealthPack::AHealthPack() {
    // Tworzymy komponent kolizji
    PrimaryActorTick.bCanEverTick = true;
    CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
    CollisionSphere->InitSphereRadius(100.f); // Ustaw promieñ
    CollisionSphere->SetCollisionProfileName(TEXT("Trigger"));
    RootComponent = CollisionSphere;

    // Subskrybujemy zdarzenie kolizji
    CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AHealthPack::OnOverlapBegin);
}

void AHealthPack::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

    // Sprawdzamy, czy kolizja dotyczy gracza
    AcattestCharacter* Player = Cast<AcattestCharacter>(OtherActor);
    if (Player) {
        // Pobieramy komponent zdrowia gracza
        UStatComponent* HealthComponent = Player->FindComponentByClass<UStatComponent>();
        if (HealthComponent) {
            HealthComponent->GetHealed2(50.f); // Leczymy gracza o 50 jednostek
            Destroy(); // Usuwamy HealthPack po u¿yciu
        }
    }
}


// Sets default values


// Called when the game starts or when spawned
void AHealthPack::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHealthPack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

