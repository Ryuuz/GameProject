// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Consumable.h"
#include "LanternOil.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API ALanternOil : public AConsumable
{
	GENERATED_BODY()
	
	ALanternOil();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void ConsumeObject(APawn* Player) override;	
};
