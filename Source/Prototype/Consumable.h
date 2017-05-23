// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Consumable.generated.h"

UCLASS()
class PROTOTYPE_API AConsumable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConsumable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void ConsumeObject(APawn* Player);

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* VisibleComponent;
};
