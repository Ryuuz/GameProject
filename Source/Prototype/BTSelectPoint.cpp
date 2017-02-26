// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "BTSelectPoint.h"
#include "AIGhostTargetPoint.h"
#include "AIGhostController.h"
#include "AIGhost.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTSelectPoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AAIGhostController* AICon = Cast<AAIGhostController>(OwnerComp.GetAIOwner());

	if (AICon)
	{
		UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();
		AAIGhostTargetPoint* CurrentPoint = Cast<AAIGhostTargetPoint>(BlackboardComp->GetValueAsObject("LocationToGo"));
		TArray<AActor*> AvailablePoints = AICon->GetPatrolPoints();
		AAIGhostTargetPoint* NextPoint = nullptr;

		if (AICon->CurrentPatrolPoint != AvailablePoints.Num() - 1)
		{
			NextPoint = Cast<AAIGhostTargetPoint>(AvailablePoints[++AICon->CurrentPatrolPoint]);
		}
		else
		{
			NextPoint = Cast<AAIGhostTargetPoint>(AvailablePoints[0]);
			AICon->CurrentPatrolPoint = 0;
		}

		if (AICon->GetCharacter()->GetDistanceTo(NextPoint) <= 1000.f)
		{
			BlackboardComp->SetValueAsObject("LocationToGo", NextPoint);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
