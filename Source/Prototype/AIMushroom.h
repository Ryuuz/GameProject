// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "AIMushroom.generated.h"

UCLASS()
class PROTOTYPE_API AAIMushroom : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIMushroom();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void DistanceFromStart();

	FORCEINLINE FVector GetStartPos() const { return StartPosition; }

	UPROPERTY(VisibleAnywhere)
	class UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ShroomMesh;
	
private:
	UFUNCTION()
	void OnPlayerSeen(APawn* pawn);

	FVector StartPosition;
};
