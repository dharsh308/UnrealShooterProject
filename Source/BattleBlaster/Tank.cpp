// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubSystems.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"

ATank::ATank() {
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm Comp"));
	SpringArmComp->SetupAttachment(CapsuleComp);
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Comp"));
	CameraComp->SetupAttachment(SpringArmComp);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	//Mapping context function
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) {
		if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer()) {
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer)) {
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (APlayerController* Player = Cast<APlayerController>(GetController())) {
		FHitResult HitResult;
		Player->GetHitResultUnderCursor(ECC_Visibility,false,HitResult);
		FVector Point=HitResult.ImpactPoint;
		RotateTurret(Point);
		//DrawDebugSphere(GetWorld(), Point, 5.0f, 10, FColor::Red);
	}
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATank::MoveInput);
	
		Input->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ATank::TurnInput);
	}
}

void ATank::MoveInput(const FInputActionValue& Value)
{
	float InputValue = Value.Get<float>();

	float DelTime=GetWorld()->GetDeltaSeconds();
	FVector DeltaLocation = FVector(0.0f, 0.0f, 0.0f);
	DeltaLocation.X = Speed * InputValue*DelTime;

	//using local actor so as to keep x direction forward instead of global coordinates
	AddActorLocalOffset(DeltaLocation,true);
}

void ATank::TurnInput(const FInputActionValue& Value) {
	float InputValue = Value.Get<float>();
	float DelTime = GetWorld()->GetDeltaSeconds();

	FRotator DeltaRotation = FRotator(0.0f, 0.0f, 0.0f);
	DeltaRotation.Yaw = TurnRate * InputValue * DelTime;

	AddActorLocalRotation(DeltaRotation, true);
}
