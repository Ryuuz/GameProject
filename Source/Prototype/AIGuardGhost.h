// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "AIGuardGhost.generated.h"

UCLASS()
class PROTOTYPE_API AAIGuardGhost : public ACharacter
{
	GENERATED_BODY()

public:
	AAIGuardGhost();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Stun(float StunTime);
	void SphereTrace();
	void InvestigateObject(TArray<FHitResult> Objs);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* GuardMesh;

	UPROPERTY(EditAnywhere)
	float AcceptableDistance = 600.f;

private:
	FVector StartPosition;
	FRotator GuardDirection;
	TArray<AActor*> InvestigatedObjs;

	bool bReturning;
	bool bInvestigating;
	bool bStunned;

	float InvestigationStart;
	float InvestigationTime;
	float TimeStunned;
	float StunStart;
};
