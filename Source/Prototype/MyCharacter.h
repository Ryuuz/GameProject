//Class for the player character

#pragma once

#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class PROTOTYPE_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);
	void JumpUp();
	void StopJump();
	void Interacting();
	void StopInteracting();
	void ThrowItem();
	void SwingStick();
	void UseLantern();
	
	void Raycast();

	void StartRotationUp();
	void StopRotationUp();

	void StartRotationDown();
	void StopRotationDown();

	void StartRotationRight();
	void StopRotationRight();

	void StartRotationLeft();
	void StopRotationLeft();

	AActor* GetLantern();
	bool GetLanternStatus();
	FORCEINLINE bool HoldingLantern() { return bHaveLantern; }

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* PlayerMesh;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CollisionComponent;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ARockProjectile> ThrowClass;
	
	UPROPERTY(EditAnywhere)
	UCameraComponent* PlayerCamera;

private:
	FVector CurrentVelocity;
	
	class APickUp* HeldObject;
	class ALantern* TheLantern;
	
	bool bAttemptInteract;
	bool bHoldingItem;
	bool bHaveLantern;
	
	float AverageRot;
	float CurrentRot;
	
	int upRot;
	int downRot;
	int leftRot;
	int rightRot;
};
