// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "AIMushroom.h"
#include "AIShroomController.h"


AAIShroomController::AAIShroomController()
{

}


//If AI has seen the player, it starts chasing said player
void AAIShroomController::SetPlayerAsSeen(APawn * Player)
{
	MoveToActor(Player, 0.5f);
}


void AAIShroomController::Possess(APawn * AIChar)
{
	Super::Possess(AIChar);
}


//Moves the AI back to its spawn location
void AAIShroomController::ReturnToStart(FVector StartPosition)
{
	MoveToLocation(StartPosition);
}
