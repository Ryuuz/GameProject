// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "RockProjectile.generated.h"

UCLASS()
class PROTOTYPE_API ARockProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARockProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void ThrowInDirection(const FVector& ThrowDirection);

	UPROPERTY(VisibleDefaultsonly)
	USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* VisibleComponent;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileComponent;
};
