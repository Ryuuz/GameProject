// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "AIGhostController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"
#include "MyCharacter.h"
#include "AIGhost.h"


// Sets default values
AAIGhost::AAIGhost()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AIMesh"));
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	
	PawnSensingComp->SetPeripheralVisionAngle(90.f);
	AIMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> AIAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (AIAsset.Succeeded())
	{
		AIMesh->SetStaticMesh(AIAsset.Object);
		AIMesh->SetWorldScale3D(FVector(0.8f, 0.8f, 0.8f));
	}

	CurrentZ = 0;
}

// Called when the game starts or when spawned
void AAIGhost::BeginPlay()
{
	Super::BeginPlay();
	
	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AAIGhost::OnPlayerCaught);
	}

	StartPosition = GetActorLocation();
	Tags.Add(FName("Enemy"));
}

// Called every frame
void AAIGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	CurrentZ += DeltaHeight * 20.0f;
	RunningTime += DeltaTime;
	AIMesh->SetRelativeLocation(FVector(0.f, 0.f, CurrentZ));
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
		if (pawn->ActorHasTag("Player"))
		{
			AIController->SetPlayerCaught(pawn, Cast<AMyCharacter>(pawn)->GetLanternStatus());
		}		
	}
}

