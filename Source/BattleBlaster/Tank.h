// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubSystems.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "Tank.generated.h"

class UCameraComponent;
class UInputMappingContext;
class UInputAction;
/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere,category="Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere,category="Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere,category="Input")
	UInputAction* TurnAction;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere)
	float Speed = 300.0f;

	UPROPERTY(EditAnywhere)
	float TurnRate = 50.0f;

	void MoveInput(const FInputActionValue& Value);
	void TurnInput(const FInputActionValue& Value);
};
