// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "AIGhostController.generated.h"

/**
  Created by following Reuben Ward's tutorial at https://www.youtube.com/watch?v=3Z1A825gTA8 
 */
UCLASS()
class PROTOTYPE_API AAIGhostController : public AAIController
{
	GENERATED_BODY()		

public:
	int32 CurrentPatrolPoint = 0;
	
	UPROPERTY(EditDefaultsOnly)
	FName LocationToGoKey;

	UPROPERTY(EditDefaultsOnly)
	FName PlayerKey;

	UPROPERTY(EditDefaultsOnly)
	FName LanternKey;

	UPROPERTY(EditDefaultsOnly)
	FName ReturnKey;

	AAIGhostController();
	void SetPlayerCaught(APawn* pawn, bool Light);
	virtual void Possess(APawn* pawn) override;

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
	FORCEINLINE TArray<AActor*> GetPatrolPoints() const { return PatrolPoints; }

private:
	class UBehaviorTreeComponent* BehaviorComp;
	class UBlackboardComponent* BlackboardComp;

	TArray<AActor*> PatrolPoints;
};
