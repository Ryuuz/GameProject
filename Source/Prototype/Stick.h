// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickUp.h"
#include "Stick.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API AStick : public APickUp
{
	GENERATED_BODY()
	
	AStick();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	
};
