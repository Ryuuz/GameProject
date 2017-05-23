// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Crystal.generated.h"

UCLASS()
class PROTOTYPE_API ACrystal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACrystal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* CrystalMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* HerbMesh;

	UPROPERTY(EditAnywhere)
	UPointLightComponent* Glow;

private:
	int32 HitPoints;
};
