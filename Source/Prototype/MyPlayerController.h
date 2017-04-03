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
//	void TakeDamage(int32 Damage);
//	void RegainHealth(int32 Healing);

private:
	int32 Health;
	bool Lantern;
};
