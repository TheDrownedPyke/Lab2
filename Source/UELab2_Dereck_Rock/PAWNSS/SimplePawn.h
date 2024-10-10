// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"

#include "SimplePawn.generated.h"

class UCameraComponent;
class USpringArmComponent;


UCLASS()
class UELAB2_DERECK_ROCK_API ASimplePawn : public APawn
{
	GENERATED_BODY()


public:
	// Sets default values for this pawn's properties
	ASimplePawn();
	
	/*The Pawns SceneComponent. This will be set as the Root Component*/
	UPROPERTY(EditAnywhere, Category="My Pawn")
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, Category="My Pawn")
	UCapsuleComponent* CapsuleComponent ;
	
	/*The Pawns SceneComponent. This will be set as the Root Component*/
	UPROPERTY(EditAnywhere, Category = "My Pawn")
	USceneComponent* MeshSceneComponent;

	/*The pawns StaticMeshComponent, this will the Pawns visual*/
	UPROPERTY(EditAnywhere, Category = "My Pawn")
	UStaticMeshComponent* StaticMeshComponent;

	/*The pawns SpringArmComponent, this is the camera boom and will be attached to the RootComponent*/
	UPROPERTY(EditAnywhere, Category = "My Pawn")
	USpringArmComponent* SpringArmComponent;

	/*The pawns CameraComponent, this will be attached to the SpringArmComponent*/
	UPROPERTY(EditAnywhere, Category = "My Pawn")
	UCameraComponent* CameraComponent;
	
	/*The pawns velocity modifier*/
	UPROPERTY(EditAnywhere, Category = "My Pawn")
	float Velocity = 300.0f;

	//Possess virtual function
	/*Called when this pawn is posessed by a Player Controller*/
	virtual void PossessedBy(AController* NewController) override;
	/*Called when this pawn is un-posessed by a Player Controller*/
	virtual void UnPossessed() override;

protected:
	// Called when the game starts or when spawned
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
    					UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
    					bool bFromSweep, const FHitResult& SweepResult);
  //  UFUNCTION()
    //void OnActorOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);
    
    //UFUNCTION()
    //void OnCollisionSphereHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

    //UFUNCTION()
	//void OnHitActor(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit );
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*Called to bind functionality to input*/
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	/*The Pawns Move Forward Amount per frame*/
	float MoveForwardAmount = 10;

	/*The Pawns Move Right Amount per frame*/
	float MoveRightAmount = 10;
	


	/*The Callback function for the MoveForward Input Axis Event*/
	virtual void MoveForward(float Amount);
	

	/*The Callback function for the MoveRight Input Axis Event*/
	virtual void MoveRight(float Amount);
	
	void PrintMessageOnScreen(FString Message);


};
