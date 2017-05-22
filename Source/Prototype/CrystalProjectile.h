// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CrystalProjectile.generated.h"

UCLASS()
class PROTOTYPE_API ACrystalProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACrystalProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void ThrowInDirection(const FVector& ThrowDirection);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(VisibleDefaultsonly)
	USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* VisibleComponent;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileComponent;

private:
	bool bTouchedGround;
};
