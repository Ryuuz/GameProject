// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "AIGhostController.h"
#include "AIGhost.h"
#include "AIGhostTargetPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"


AAIGhostController::AAIGhostController()
{
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));

	LocationToGoKey = "LocationToGo";
	PlayerKey = "Target";

	CurrentPatrolPoint = 0;
}


void AAIGhostController::SetPlayerCaught(APawn* pawn)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(PlayerKey, pawn);
		UE_LOG(LogTemp, Warning, TEXT("Boo!"));
	}
}


void AAIGhostController::Possess(APawn* pawn)
{
	Super::Possess(pawn);

	AAIGhost* Ghost = Cast<AAIGhost>(pawn);

	if (Ghost)
	{
		//Initialise blackboard
		if (Ghost->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*(Ghost->BehaviorTree->BlackboardAsset));
		}

		//Get all patrol points and start up the tree
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIGhostTargetPoint::StaticClass(), PatrolPoints);
		BehaviorComp->StartTree(*Ghost->BehaviorTree);
	}
}


