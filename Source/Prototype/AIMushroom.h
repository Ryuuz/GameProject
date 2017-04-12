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

	UPROPERTY(VisibleAnywhere)
	class UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ShroomMesh;

	UPROPERTY(EditAnywhere)
	float AreaRadius = 600.f;

	UPROPERTY(EditAnywhere)
	float ChaseDistance = 1000.f;

	UPROPERTY(EditAnywhere)
	bool bPatrolling = true;
	
private:
	UFUNCTION()
	void OnPlayerSeen(APawn* pawn);

	FVector StartPosition;
	bool bChasingPlayer;
	bool bReturning;
	bool bInvestigating;

	float InvestigationStart;
	float InvestigationTime;
};
