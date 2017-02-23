// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTSelectPoint.generated.h"

/**
 Created by following Reuben Ward's tutorial at https://www.youtube.com/watch?v=3Z1A825gTA8
 */
UCLASS()
class PROTOTYPE_API UBTSelectPoint : public UBTTaskNode
{
	GENERATED_BODY()

		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	
};
