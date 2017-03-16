// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "AIShroomController.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API AAIShroomController : public AAIController
{
	GENERATED_BODY()

public:
	AAIShroomController();
	void SetPlayerAsSeen(APawn* Player);
	virtual void Possess(APawn* AIChar) override;
	void ReturnToStart(FVector StartPosition);
};
