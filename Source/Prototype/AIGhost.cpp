// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "AIGhostController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "AIGhost.h"


// Sets default values
AAIGhost::AAIGhost()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->SetPeripheralVisionAngle(90.f);
}

// Called when the game starts or when spawned
void AAIGhost::BeginPlay()
{
	Super::BeginPlay();
	
	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AAIGhost::OnPlayerCaught);
	}
}

// Called every frame
void AAIGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIGhost::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAIGhost::OnPlayerCaught(APawn* pawn)
{
	AAIGhostController* AIController = Cast<AAIGhostController>(GetController());

	if (AIController)
	{
		AIController->SetPlayerCaught(pawn);
	}
}

