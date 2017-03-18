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

	ChasingPlayer = false;
	Returning = false;
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

	//Checks if it has gotten too far from its spawn point
	DistanceFromStart();

	//Walk around if there's no player to chase
	if (!ChasingPlayer)
	{
		MoveForward();
	}
}


// Called to bind functionality to input
void AAIMushroom::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


//Checks distance from 'StartPosition'
void AAIMushroom::DistanceFromStart()
{
	//If distance is greater than 1000 units, return to 'StartPosition'
	if ((GetActorLocation() - StartPosition).Size() > 1000.f)
	{
		AAIShroomController* AIController = Cast<AAIShroomController>(GetController());

		if (AIController)
		{
			Returning = true;
			AIController->ReturnToStart(StartPosition);
		}
	}
	//If returning from having chased a player and is within 'AreaRadius', prepare to start walking around
	else if (Returning && (GetActorLocation() - StartPosition).Size() < AreaRadius)
	{
		ChasingPlayer = false;
		Returning = false;
	}
}

//Moves the AI forwards
void AAIMushroom::MoveForward()
{
	FVector Direction;
	FVector NextPos = GetActorLocation() + 1.f*GetVelocity();

	//If at the edge of the 'AreaRadius', turn around a random degree
	if ((FMath::Square(StartPosition.X - NextPos.X) + FMath::Square(StartPosition.Y - NextPos.Y)) >= FMath::Square(AreaRadius - GetCapsuleComponent()->GetUnscaledCapsuleRadius()))
	{
		float NewAngle = FMath::RandRange(90.f, 180.f);
		AddActorLocalRotation(FRotator(0.f, NewAngle, 0.f));
	}

	const FRotator Rotation = GetActorRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
	AddMovementInput(Direction, 1);
}


//When player enters the AI's sight
void AAIMushroom::OnPlayerSeen(APawn* pawn)
{
	AAIShroomController* AIController = Cast<AAIShroomController>(GetController());

	if (pawn->ActorHasTag("Player") && AIController)
	{
		ChasingPlayer = true;
		AIController->SetPlayerAsSeen(pawn);
	}
}

