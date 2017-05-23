// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickUp.h"
#include "Rock.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API ARock : public APickUp
{
	GENERATED_BODY()

	ARock();
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
