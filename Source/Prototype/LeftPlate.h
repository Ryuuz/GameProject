// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickUp.h"
#include "LeftPlate.generated.h"

UCLASS()
class PROTOTYPE_API ALeftPlate : public APickUp
{
	GENERATED_BODY()
	
public:	
	ALeftPlate();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;	
};
