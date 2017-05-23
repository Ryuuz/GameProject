//Class for the player character

#pragma once

#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class PROTOTYPE_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyCharacter();
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
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
	void IncreaseHerb();
	FORCEINLINE bool HoldingLantern() { return bHaveLantern; }

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* PlayerMesh;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CollisionComponent;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class ARockProjectile> ThrowClass;
	
	UPROPERTY(EditAnywhere)
	UCameraComponent* PlayerCamera;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		float Herbs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		float Oil;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		float Max;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		float Interaction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		float EntrancePopUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
		float HasLantern;

private:
	FVector CurrentVelocity;
	
	class APickUp* HeldObject;
	class ALantern* TheLantern;
	
	bool bZoom;
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
