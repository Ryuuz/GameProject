// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "AIGhostController.h"
#include "AIGhost.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BTReturn.h"

EBTNodeResult::Type UBTReturn::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AAIGhostController* AICon = Cast<AAIGhostController>(OwnerComp.GetAIOwner());

	if (AICon)
	{
		UBlackboardComponent* BlackboardComp = AICon->GetBlackboardComp();

		if (((AICon->GetCharacter()->GetActorLocation() - Cast<AAIGhost>(AICon->GetCharacter())->GetStartPos()).Size()) > 1200.f)
		{
			AICon->MoveToLocation(Cast<AAIGhost>(AICon->GetCharacter())->GetStartPos());
			BlackboardComp->ClearValue(AICon->PlayerKey);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
