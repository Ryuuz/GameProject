// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Lantern.generated.h"

UCLASS()
class PROTOTYPE_API ALantern : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALantern();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void ToggleLantern();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* LanternMesh;

	UPROPERTY(EditAnywhere)
	UPointLightComponent* LanternLight;

private:
	int32 OilLevel;
	bool bLanternOn;
};
