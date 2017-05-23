// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickUp.h"
#include "CrystalPiece.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API ACrystalPiece : public APickUp
{
	GENERATED_BODY()
	
	ACrystalPiece();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;	
};
