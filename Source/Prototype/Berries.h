// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Consumable.h"
#include "Berries.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API ABerries : public AConsumable
{
	GENERATED_BODY()
	
	ABerries();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void ConsumeObject(APawn* Player) override;	
};
