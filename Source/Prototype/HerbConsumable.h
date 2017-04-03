// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Consumable.h"
#include "HerbConsumable.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API AHerbConsumable : public AConsumable
{
	GENERATED_BODY()
	
	AHerbConsumable();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
