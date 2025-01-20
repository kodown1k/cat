// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GrabberComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CATTEST_API UGrabberComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGrabberComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Grab();
	void Release();
	void Use();
	void Throw();

private:
	UPROPERTY()
	UInputComponent* m_InputComponent = nullptr;
	UPROPERTY()
	UPhysicsHandleComponent* m_physicsHandleComponent = nullptr;

	UPROPERTY(EditAnywhere)
	float GrabRange = 200.0f;
	UPROPERTY(EditAnywhere)
	float ThrowStrength = 100.0f;
};
