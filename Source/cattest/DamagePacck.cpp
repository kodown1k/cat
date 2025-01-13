// Fill out your copyright notice in the Description page of Project Settings.


#include "DamagePacck.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"

#include "StatComponent.h" // Zast¹p swoj¹ klas¹ komponentu zdrowia
// Sets default values
ADamagePacck::ADamagePacck()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
    CollisionSphere->InitSphereRadius(100.f); // Ustaw promieñ
    CollisionSphere->SetCollisionProfileName(TEXT("Trigger"));
    RootComponent = CollisionSphere;

    // Subskrybujemy zdarzenie kolizji
    CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ADamagePacck::OnOverlapBegin);
}


//void ADamagePacck::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
//    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
//
//    // Sprawdzamy, czy kolizja dotyczy gracza
//    AcattestCharacter* Player = Cast<AcattestCharacter>(OtherActor);
//    if (Player) {
//        // Pobieramy komponent zdrowia gracza
//        UStatComponent* HealthComponent = Player->FindComponentByClass<UStatComponent>();
//        if (HealthComponent) {
//            HealthComponent->GetDamaged2(50.f); // Leczymy gracza o 50 jednostek
//            Destroy(); // Usuwamy HealthPack po u¿yciu
//        }
//    }
//}

// zmiana na interfejs

void ADamagePacck::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
    UE_LOG(LogTemp, Warning, TEXT("OnOverlapBegin triggered!"));
    // Sprawdzamy, czy OtherActor implementuje interfejs IDamageableInterface
    UStatComponent* Damagable = OtherActor->FindComponentByClass<UStatComponent>();
    if (Damagable)
    {
        // Zadanie obra¿eñ przez komponent zdrowia
        Damagable->GetDamaged(50); // Zadaj 50 punktów obra¿eñ
        Destroy(); // Zniszczenie zdrowotnej paczki po u¿yciu
    }
}

// Called when the game starts or when spawned
void ADamagePacck::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADamagePacck::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

