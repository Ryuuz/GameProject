// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "AIMushroom.generated.h"

UCLASS()
class PROTOTYPE_API AAIMushroom : public ACharacter
{
	GENERATED_BODY()

public:
	AAIMushroom();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void DistanceFromStart();
	void MoveForward();
	void HeardSound(AActor* Origin);
	void Stun(float StunTime);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(VisibleAnywhere)
	class UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ShroomMesh;

	UPROPERTY(EditAnywhere)
	float AreaRadius = 600.f;

	UPROPERTY(EditAnywhere)
	float ChaseDistance = 1000.f;

	//Uncheck in editor to have the AI remain stationary
	UPROPERTY(EditAnywhere)
	bool bPatrolling = true;
	
private:
	UFUNCTION()
	void OnPlayerSeen(APawn* pawn);

	FVector StartPosition;
	FRotator StartRotation;
	bool bChasingPlayer;
	bool bReturning;
	bool bInvestigating;
	bool bStunned;

	float InvestigationStart;
	float InvestigationTime;
	float TimeStunned;
	float StunStart;
};
