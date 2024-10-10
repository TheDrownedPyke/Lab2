// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"

#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UELab2_Dereck_Rock/PAWNSS/SimplePawn.h"
//#include "PAWNSS/SimplePawn.h"

 DEFINE_LOG_CATEGORY_STATIC(LogMyPlayerController, All, All)

void AMyPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    //TODO: Bind the button press action to switch pawns. Can the pawns input bindings be moved here?
    if (InputComponent)
    {
        //BIND Action "ChangePawn", On the key Event Pressed to this objects ChangePawn() Function
	//Input
        InputComponent->BindAction("SwitchPawns", IE_Pressed, this, &AMyPlayerController::ChangePawn);
    }
}

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASimplePawn::StaticClass(),Pawns);
 	UE_LOG(LogMyPlayerController, Warning, TEXT("Number of pawns: %d"),Pawns.Num());
    //TODO: Get all actors of type ASimplePawn that are in the level
    //GET all actors of type ASimplePawn in the level (Look up the function UGameplayStatics::GetAllActorsOfClass(const UObject* WorldContextObject, TSubclassOf<AActor> ActorClass, TArray<AActor*>& OutActors)). You can pass ASimplePawn::StaticClass() into the TSubclassOf<AActor> ActorClass argument
    //What header file is involved in using this static helper function
	
}

void AMyPlayerController::ChangePawn()
{
	if(Pawns.Num()<1)
	{
		UE_LOG(LogMyPlayerController, Warning, TEXT("No pawns"));
		return;
	}
 	
	AActor* Currentactor = Pawns[CurrentPawnIndex];
 	CurrentPawnIndex=(CurrentPawnIndex+1)%Pawns.Num();
	APawn* CurrentPawn=Cast<APawn>(Currentactor);

 	if(!CurrentPawn)
	{
		UE_LOG(LogMyPlayerController, Warning, TEXT("Pawn is not avalib"));
		return;
	}
 	Possess(CurrentPawn);
}
