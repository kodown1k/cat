// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabberComponent.h"

#include "EnhancedInputComponent.h"

// Sets default values for this component's properties
UGrabberComponent::UGrabberComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabberComponent::BeginPlay()
{
	Super::BeginPlay();

	m_InputComponent = GetOwner()->GetComponentByClass<UInputComponent>();

	if (m_InputComponent)
	{
		m_InputComponent->BindAction("Use", IE_Pressed, this, &UGrabberComponent::Use);
		m_InputComponent->BindAction("Throw", IE_Pressed, this, &UGrabberComponent::Throw);
	}
	m_physicsHandleComponent = GetOwner()->GetComponentByClass<UPhysicsHandleComponent>();
}

void UGrabberComponent::Grab()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::MakeRandomColor(), "tes");

	FHitResult HitResult;
	FVector Start;
	FRotator CameraRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Start, CameraRotation);
	FVector End = Start + CameraRotation.Vector() * GrabRange;

	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility);

	// DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 5, 0, 4);
	if (HitResult.GetActor())
	{
		UE_LOG(LogTemp, Warning, TEXT("Grabber Found: %s"), *HitResult.GetActor()->GetName());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::MakeRandomColor(), *HitResult.GetActor()->GetName());

		m_physicsHandleComponent->GrabComponentAtLocationWithRotation(HitResult.GetComponent(), FName(), HitResult.GetComponent()->GetComponentLocation(),
		                                                              HitResult.GetComponent()->GetComponentRotation());
	}
}

void UGrabberComponent::Release()
{
	if (m_physicsHandleComponent)
	{
		m_physicsHandleComponent->ReleaseComponent();
	}
}

void UGrabberComponent::Use()
{
	if (m_physicsHandleComponent && m_physicsHandleComponent->GetGrabbedComponent())
	{
		Release();
	}
	else
	{
		Grab();
	}
}

void UGrabberComponent::Throw()
{
	if (m_physicsHandleComponent && m_physicsHandleComponent->GetGrabbedComponent())
	{
		UPrimitiveComponent* Component = m_physicsHandleComponent->GetGrabbedComponent();
		m_physicsHandleComponent->ReleaseComponent();


		FVector Start;
		FRotator CameraRotation;
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Start, CameraRotation);
		Component->AddImpulse(CameraRotation.Vector() * ThrowStrength, FName(), true);
	}
}

// Called every frame
void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_physicsHandleComponent && m_physicsHandleComponent->GetGrabbedComponent())
	{
		FVector Start;
		FRotator CameraRotation;
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Start, CameraRotation);
		FVector End = Start + CameraRotation.Vector() * GrabRange;

		m_physicsHandleComponent->SetTargetLocationAndRotation(End, CameraRotation);
	}
}
