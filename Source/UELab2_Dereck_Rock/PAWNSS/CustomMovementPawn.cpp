// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomMovementPawn.h"

#include "CustomMovementPawn.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "UELab2_Dereck_Rock/MovementComponent/CustomMovementComponent.h"
// Sets default values
ACustomMovementPawn::ACustomMovementPawn()
{
	RootComponent=CreateDefaultSubobject<UCapsuleComponent>(TEXT("Root"));
	//TODO: Add the Simple Movement Component to this Pawn
	//CREATE the SimpleMovementComponent
	SimpleMovementComponent=CreateDefaultSubobject<UCustomMovementComponent>(TEXT("SimpleMovementComponent"));
	//SimpleMovementComponent=RootComponent;
	if(SimpleMovementComponent)
	{
		SimpleMovementComponent->UpdatedComponent=RootComponent;
	}
	//ASSIGN the RootComponent to the SimpleMovementComponent->UpdatedComponent variable
}

void ACustomMovementPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACustomMovementPawn::MoveForward(float Amount)
{
	if (!Controller)
		return;
		
	/*
	if (FMath::IsNearlyZero(Amount))
	{
		SimpleMovementComponent->AddInputVector(FVector::ZeroVector);
		return;
	}
	*/
	FRotator Rotation=Controller->GetControlRotation();

	FRotator YawRotation(0.0f,Rotation.Yaw,0.0f);

	FVector Direction=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
	if(SimpleMovementComponent)
	{
		SimpleMovementComponent->AddInputVector(Direction*Amount);
	}

}



void ACustomMovementPawn::MoveRight(float Amount)
{
	if (!Controller)
		return;
	/*
	if (FMath::IsNearlyZero(Amount))
	{
		SimpleMovementComponent->AddInputVector(FVector::ZeroVector);
		return;
	}
	*/
	FRotator Rotation=Controller->GetControlRotation();

	FRotator YawRotation(0.0f,Rotation.Yaw,0.0f);

	FVector Direction=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	if(SimpleMovementComponent)
	{
		SimpleMovementComponent->AddInputVector(Direction*Amount);
	}

}





