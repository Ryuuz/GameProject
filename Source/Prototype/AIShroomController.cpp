// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "AIMushroom.h"
#include "AIShroomController.h"


AAIShroomController::AAIShroomController()
{

}


void AAIShroomController::SetPlayerAsSeen(APawn * Player)
{
	MoveToActor(Player, 0.5f);
}


void AAIShroomController::Possess(APawn * AIChar)
{
	Super::Possess(AIChar);

	AAIMushroom* AShroom = Cast<AAIMushroom>(AIChar);

	if (AShroom)
	{
		UE_LOG(LogTemp, Warning, TEXT("I'm possessed"));
	}
}

void AAIShroomController::ReturnToStart(FVector StartPosition)
{
	MoveToLocation(StartPosition);
}
