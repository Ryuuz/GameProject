// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/PawnSensingComponent.h"
#include "AIShroomController.h"
#include "AIMushroom.h"


// Sets default values
AAIMushroom::AAIMushroom()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShroomMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AIMesh"));
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	
	ShroomMesh->SetupAttachment(RootComponent);
	PawnSensingComp->SetPeripheralVisionAngle(90.f);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> AIAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (AIAsset.Succeeded())
	{
		ShroomMesh->SetStaticMesh(AIAsset.Object);
		ShroomMesh->SetWorldScale3D(FVector(0.8f, 0.8f, 0.8f));
	}
}


// Called when the game starts or when spawned
void AAIMushroom::BeginPlay()
{
	Super::BeginPlay();
	
	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AAIMushroom::OnPlayerSeen);
	}

	StartPosition = GetActorLocation();
	Tags.Add(FName("Enemy"));
}


// Called every frame
void AAIMushroom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DistanceFromStart();
}


// Called to bind functionality to input
void AAIMushroom::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}


void AAIMushroom::DistanceFromStart()
{
	if ((GetActorLocation() - StartPosition).Size() > 1000.f)
	{
		AAIShroomController* AIController = Cast<AAIShroomController>(GetController());

		if (AIController)
		{
			UE_LOG(LogTemp, Warning, TEXT("Too far from start"));
			AIController->ReturnToStart(StartPosition);
		}
	}
}


void AAIMushroom::OnPlayerSeen(APawn* pawn)
{
	AAIShroomController* AIController = Cast<AAIShroomController>(GetController());

	if (pawn->ActorHasTag("Player") && AIController)
	{
		AIController->SetPlayerAsSeen(pawn);
	}
}

