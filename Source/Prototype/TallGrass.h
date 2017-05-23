// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "TallGrass.generated.h"

UCLASS()
class PROTOTYPE_API ATallGrass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATallGrass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UShapeComponent* RootSphere = nullptr;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* VisibleComponent;
	

};
