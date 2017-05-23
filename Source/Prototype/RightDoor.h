// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "RightDoor.generated.h"

UCLASS()
class PROTOTYPE_API ARightDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARightDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void AttachPlate(AActor* Plate);
	FORCEINLINE bool IsUnlocked() { return Unlocked; }

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere)
	class ALeftDoor* Left;

private:
	bool Unlocked;
	bool Open;
	FRotator OpenRotation;
};
