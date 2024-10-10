// Fill out your copyright notice in the Description page of Project Settings.


#include "SimplePawn.h"

#include "AITestsCommon.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"


DEFINE_LOG_CATEGORY_STATIC(LogSimplePawn, All, All)

// Sets default values
ASimplePawn::ASimplePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	RootComponent = SceneComponent;	//SET the Scene Component as the  Root Component


		CapsuleComponent= CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapComponent"));
    	CapsuleComponent->SetCollisionProfileName(TEXT("Player"));
    	CapsuleComponent->SetGenerateOverlapEvents(true);
    	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    	RootComponent = CapsuleComponent;
	
	StaticMeshComponent= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SceneComponent);

	SpringArmComponent=CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringarmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent=CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);


	SpringArmComponent->bUsePawnControlRotation = true;
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this,	&ASimplePawn::OnOverlapBegin);
    SetActorEnableCollision(true);
}

// Called when the game starts or when spawned
void ASimplePawn::BeginPlay()
{
	Super::BeginPlay();
	
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this,&ASimplePawn::OnOverlapBegin);
   // CapsuleComponet->
}

// Called every frame
void ASimplePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//TODO: Implement the movement. Think about how the movement is done after you have written the implementation code. 
	//IF the Controller is NOT null
	if(!IsPlayerControlled())
	{
		return;
	}
if(Controller)
	{
		//DECLARE a FRotator Rotation and Initialize it to pitch=0, roll=0 and the Yaw to the Controllers Yaw Rotation
		FRotator Rotation = Controller->GetControlRotation();
		Rotation.Pitch = 0.0f;
	    Rotation.Roll = 0.0f;
		//DECLARE a FVector Direction and set it to zero vector
	FVector Direction = FVector::ZeroVector;
		//IF the MoveForwardAmount is not zero
	if(MoveForwardAmount!=0.0f)
		{
			//SET the Direction to this Actors Location + FRotationMatrix(??).GetUnitAxis(??) * MoveForwardAmount * Velocity * DeltaTime
		Direction += FRotationMatrix(Rotation).GetScaledAxis(EAxis::X)* MoveForwardAmount * Velocity * DeltaTime;

		}


		if(MoveRightAmount!=0.0f)
		{
			Direction += FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y)* MoveRightAmount  * Velocity * DeltaTime;

		}

	

	if(!Direction.IsZero())
	{
		FVector newlocation = GetActorLocation()+Direction;
		SetActorLocation(newlocation);
	}
		//ENDIF

	}
}

// Called to bind functionality to input
void ASimplePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	if(PlayerInputComponent)
	{
		// Bind axis input for moving forward and right
		PlayerInputComponent->BindAxis("MoveForward", this, &ASimplePawn::MoveForward);

		PlayerInputComponent->BindAxis("MoveRight", this, &ASimplePawn::MoveRight);


		// Bind axis input for looking around (pitch and yaw)
		PlayerInputComponent->BindAxis("LookUp", this, &APawn:: AddControllerPitchInput);
		PlayerInputComponent->BindAxis("LookRight", this, &APawn::AddControllerYawInput);
	}
	
}

void ASimplePawn::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
					UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
					bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && (OtherActor!=this))
	{
		UE_LOG(LogSimplePawn, Warning, TEXT("Overlapping with: %s"), *OtherActor->GetName());

		ASimplePawn* MyPawn = Cast<ASimplePawn>(OtherActor);
		if(MyPawn)
		{
			FString Message = FString("OnCollisionSphereBeginOverlap: ") + OtherActor->GetName();
			PrintMessageOnScreen(Message);
            APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
			if(PlayerController)
			{
				PlayerController->UnPossess();

				
				PlayerController->Possess(MyPawn);
			}
		}
	}		
	
}

void ASimplePawn::MoveForward(float Amount)
{

	MoveForwardAmount = Amount;
	
}



void ASimplePawn::MoveRight(float Amount)
{
	MoveRightAmount = Amount;

}



void ASimplePawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!NewController) 
		return;
	UE_LOG(LogSimplePawn, Warning, TEXT("%s PossessBy: %s"), *GetName(), *NewController->GetName());
}

void ASimplePawn::UnPossessed()
{
	Super::UnPossessed();
	UE_LOG(LogSimplePawn, Warning, TEXT("%s Un Prossessed"), *GetName());
}

void ASimplePawn::PrintMessageOnScreen(FString Message)
{
	//const FString Message = FString("Ending Overlap with: ") + OtherActor->GetName();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(2, 10.f, FColor::Red, Message);
	}
}