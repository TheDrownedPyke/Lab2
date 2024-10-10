// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "CustomMovementComponent.generated.h"

UCLASS()
class UELAB2_DERECK_ROCK_API UCustomMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/*The Pawns Movement Speed */
	UPROPERTY(EditAnywhere, Category = "Movement Properties")
	float Speed = 500;
};
