// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Lantern.generated.h"

UCLASS()
class PROTOTYPE_API ALantern : public AActor
{
	GENERATED_BODY()
	
public:	
	ALantern();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	void ToggleLantern();
	void RestoreOil(int32 Amount);

	FORCEINLINE bool LanternStatus() { return bLanternOn; }
	FORCEINLINE int32 OilStatus() { return OilLevel; }

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* LanternMesh;

	UPROPERTY(EditAnywhere)
	UPointLightComponent* LanternLight;

private:
	int32 OilLevel;
	bool bLanternOn;
	float DepleteTime = 2.f;
	float CurrentTime;
};
