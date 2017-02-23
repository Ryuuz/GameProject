// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "AIGhost.generated.h"

/**
Created by following Reuben Ward's tutorial at https://www.youtube.com/watch?v=3Z1A825gTA8
*/
UCLASS()
class PROTOTYPE_API AAIGhost : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIGhost();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* BehaviorTree;
	
	UPROPERTY(VisibleAnywhere)
	class UPawnSensingComponent* PawnSensingComp;

private:
	UFUNCTION()
	void OnPlayerCaught(APawn* pawn);
};
