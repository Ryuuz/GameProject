// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "AIPatrolGhost.generated.h"

UCLASS()
class PROTOTYPE_API AAIPatrolGhost : public ACharacter
{
	GENERATED_BODY()

public:
	AAIPatrolGhost();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void DistanceFromStart();
	void MoveForward();
	void Stun(float StunTime);
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(VisibleAnywhere)
	class UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PatrolMesh;

	UPROPERTY(EditAnywhere)
	float PatrolDistance = 600.f;

	UPROPERTY(EditAnywhere)
	float ChaseDistance = 1000.f;

private:
	UFUNCTION()
	void OnPlayerSeen(APawn* pawn);

	FVector StartPosition;
	FRotator PatrolRotation;
	bool bChasingPlayer;
	bool bReturning;
	bool bStunned;

	float TimeStunned;
	float StunStart;
	float CurrentZ;
	float RunningTime;
};
