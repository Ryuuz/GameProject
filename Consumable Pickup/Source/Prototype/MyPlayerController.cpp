// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "MyCharacter.h"
#include "MyPlayerController.h"

// Made using the post at https://www.reddit.com/r/unrealengine/comments/34c73q/help_with_creating_a_custom_playercontroller_or/ by user emp-
AMyPlayerController::AMyPlayerController(const class FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer)
{
	Health = 100;
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveX", this, &AMyPlayerController::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, &AMyPlayerController::Move_YAxis);
	InputComponent->BindAction("Jump", IE_Pressed, this, &AMyPlayerController::JumpUp);

	InputComponent->BindAction("Interact", IE_Pressed, this, &AMyPlayerController::Interacting);
	InputComponent->BindAction("Interact", IE_Released, this, &AMyPlayerController::StopInteracting);

}

void AMyPlayerController::Move_XAxis(float AxisValue)
{
	AMyCharacter* Player = Cast<AMyCharacter>(GetCharacter());

	if (Player)
	{
		Player->Move_XAxis(AxisValue);
	}
}


void AMyPlayerController::Move_YAxis(float AxisValue)
{
	AMyCharacter* Player = Cast<AMyCharacter>(GetCharacter());

	if (Player)
	{
		Player->Move_YAxis(AxisValue);
	}
}

void AMyPlayerController::JumpUp()
{
	AMyCharacter* Player = Cast<AMyCharacter>(GetCharacter());

	if (Player)
	{
		Player->JumpUp();
	}
}


void AMyPlayerController::Interacting()
{
	AMyCharacter* Player = Cast<AMyCharacter>(GetCharacter());

	if (Player)
	{
		Player->Interacting();
	}
}


void AMyPlayerController::StopInteracting()
{
	AMyCharacter* Player = Cast<AMyCharacter>(GetCharacter());

	if (Player)
	{
		Player->StopInteracting();
	}
}




void AMyPlayerController::TakeDamage(int32 Damage)
{
	Health -= Damage;

	if (Health <= 0)
	{
		Health = 0;
	}
}

