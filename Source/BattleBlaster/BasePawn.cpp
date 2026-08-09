// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	SetRootComponent(CapsuleComp);
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Component"));
	BaseMesh->SetupAttachment(CapsuleComp);
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Component"));
	TurretMesh->SetupAttachment(BaseMesh);

}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector RotVector = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator RotationVector = FRotator(0.0f, RotVector.Rotation().Yaw, 0.0f);

	FRotator InterpRotator = FMath::RInterpTo(
		TurretMesh->GetComponentRotation(),
		RotationVector,
		GetWorld()->GetDeltaSeconds(),
		10.0f
	);
	TurretMesh->SetWorldRotation(InterpRotator);
}




