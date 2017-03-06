// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "MyPlayerController.h"
#include "PrototypeGameModeBase.h"


APrototypeGameModeBase::APrototypeGameModeBase(const class FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer)
{
	PlayerControllerClass = AMyPlayerController::StaticClass();
}


