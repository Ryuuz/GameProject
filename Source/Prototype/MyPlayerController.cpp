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
	InputComponent->BindAction("Jump", IE_Released, this, &AMyPlayerController::StopJump);
	InputComponent->BindAction("Interact", IE_Pressed, this, &AMyPlayerController::Interacting);
	InputComponent->BindAction("Interact", IE_Released, this, &AMyPlayerController::StopInteracting);
	InputComponent->BindAction("Throw", IE_Pressed, this, &AMyPlayerController::ThrowObject);
	InputComponent->BindAction("Hit", IE_Pressed, this, &AMyPlayerController::SwingStick);
	InputComponent->BindAction("Lantern", IE_Pressed, this, &AMyPlayerController::ToggleLantern);

	InputComponent->BindAction("RotationUp", IE_Pressed, this, &AMyPlayerController::StartRotationUp);
	InputComponent->BindAction("RotationUp", IE_Released, this, &AMyPlayerController::StopRotationUp);

	InputComponent->BindAction("RotationDown", IE_Pressed, this, &AMyPlayerController::StartRotationDown);
	InputComponent->BindAction("RotationDown", IE_Released, this, &AMyPlayerController::StopRotationDown);

	InputComponent->BindAction("RotationRight", IE_Pressed, this, &AMyPlayerController::StartRotationRight);
	InputComponent->BindAction("RotationRight", IE_Released, this, &AMyPlayerController::StopRotationRight);

	InputComponent->BindAction("RotationLeft", IE_Pressed, this, &AMyPlayerController::StartRotationLeft);
	InputComponent->BindAction("RotationLeft", IE_Released, this, &AMyPlayerController::StopRotationLeft);

	InputComponent->BindAction("Exit", IE_Pressed, this, &AMyPlayerController::QuitGame);
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


void AMyPlayerController::StopJump()
{
	AMyCharacter* Player = Cast<AMyCharacter>(GetCharacter());

	if (Player)
	{
		Player->StopJump();
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


void AMyPlayerController::ThrowObject()
{
	AMyCharacter* Player = Cast<AMyCharacter>(GetCharacter());

	if (Player)
	{
		Player->ThrowItem();
	}
}


void AMyPlayerController::SwingStick()
{
	AMyCharacter* Player = Cast<AMyCharacter>(GetCharacter());

	if (Player)
	{
		Player->SwingStick();
	}
}


void AMyPlayerController::ToggleLantern()
{
	AMyCharacter* Player = Cast<AMyCharacter>(GetCharacter());

	if (Player)
	{
		Player->UseLantern();
	}
}


void AMyPlayerController::StartRotationUp()
{
	AMyCharacter* Player = Cast<AMyCharacter>(GetCharacter());

	if (Player)
	{
		Player->StartRotationUp();
	}
}


void AMyPlayerController::StopRotationUp()
{
	AMyCharacter* Player = Cast<AMyCharacter>(GetCharacter());

	if (Player)
	{
		Player->StopRotationUp();
	}
}


void AMyPlayerController::StartRotationDown()
{
	AMyCharacter* Player = Cast<AMyCharacter>(GetCharacter());

	if (Player)
	{
		Player->StartRotationDown();
	}
}


void AMyPlayerController::StopRotationDown()
{
	AMyCharacter* Player = Cast<AMyCharacter>(GetCharacter());

	if (Player)
	{
		Player->StopRotationDown();
	}
}


void AMyPlayerController::StartRotationRight()
{
	AMyCharacter* Player = Cast<AMyCharacter>(GetCharacter());

	if (Player)
	{
		Player->StartRotationRight();
	}
}


void AMyPlayerController::StopRotationRight()
{
	AMyCharacter* Player = Cast<AMyCharacter>(GetCharacter());

	if (Player)
	{
		Player->StopRotationRight();
	}
}


void AMyPlayerController::StartRotationLeft()
{
	AMyCharacter* Player = Cast<AMyCharacter>(GetCharacter());

	if (Player)
	{
		Player->StartRotationLeft();
	}
}


void AMyPlayerController::StopRotationLeft()
{
	AMyCharacter* Player = Cast<AMyCharacter>(GetCharacter());

	if (Player)
	{
		Player->StopRotationLeft();
	}
}


void AMyPlayerController::QuitGame()
{
	FGenericPlatformMisc::RequestExit(false);
}


void AMyPlayerController::LoseHealth(int32 Damage)
{
	Health -= Damage;

	if (Health <= 0)
	{
		Health = 0;
	}
}


void AMyPlayerController::RegainHealth(int32 Healing)
{
	Health += Healing;
	
	if (Health > 100)
	{
		Health = 100;
	}
}
