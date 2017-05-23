// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPE_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMyPlayerController(const class FObjectInitializer & ObjectInitializer);
	virtual void SetupInputComponent() override;
	
	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);
	void JumpUp();
	void StopJump();
	void Interacting();
	void StopInteracting();
	void ThrowObject();
	void SwingStick();
	void ToggleLantern();
	void LoseHealth(int32 Damage);
	void RegainHealth(int32 Healing);

	FORCEINLINE int32 GetHealth() { return Health; }

	void StartRotationUp();
	void StopRotationUp();
	void StartRotationDown();
	void StopRotationDown();
	void StartRotationRight();
	void StopRotationRight();
	void StartRotationLeft();
	void StopRotationLeft();

private:
	int32 Health;
};
