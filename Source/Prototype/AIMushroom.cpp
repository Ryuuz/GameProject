// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/PawnSensingComponent.h"
#include "AIShroomController.h"
#include "AIMushroom.h"

//Several functions could be moved to the controller for the other AIs, but meh

// Sets default values
AAIMushroom::AAIMushroom()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShroomMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AIMesh"));
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	
	ShroomMesh->SetupAttachment(RootComponent);
	PawnSensingComp->SetPeripheralVisionAngle(90.f);

	//Set mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> AIAsset(TEXT("StaticMesh'/Game/Meshes/Mushroom.Mushroom'"));
	if (AIAsset.Succeeded())
	{
		ShroomMesh->SetStaticMesh(AIAsset.Object);
		ShroomMesh->SetWorldScale3D(FVector(1.f, 1.f, 1.f));
		ShroomMesh->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	}

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AAIMushroom::OnHit);
	GetCharacterMovement()->MaxWalkSpeed = 100.f;
	PawnSensingComp->SightRadius = 500.f;
	AIControllerClass = AAIShroomController::StaticClass();

	bChasingPlayer = false;
	bReturning = false;
	bInvestigating = false;
	bStunned = false;
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
	StartRotation = GetActorRotation();
	Tags.Add(FName("Enemy"));	
}


// Called every frame
void AAIMushroom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Remove stun after set time
	if (bStunned && (GetWorld()->GetTimeSeconds() - StunStart) >= TimeStunned)
	{
		bStunned = false;
	}

	//Only move if not stunned
	if (!bStunned)
	{
		//When done investigating sound
		if (bInvestigating && (GetWorld()->GetTimeSeconds() - InvestigationStart) >= InvestigationTime)
		{
			bInvestigating = false;

			//Return to original position if not patrolling
			if (!bPatrolling)
			{
				AAIShroomController* AIController = Cast<AAIShroomController>(GetController());

				if (AIController)
				{
					AIController->ReturnToStart(StartPosition);
				}
			}
		}

		if (!bPatrolling && !bInvestigating && !bChasingPlayer && !bReturning)
		{
			if (GetActorRotation() != StartRotation)
			{
				SetActorRotation(StartRotation);
			}

		}

		//Checks if it has gotten too far from its spawn point
		DistanceFromStart();

		//Walk around if there is no player to chase
		if (bPatrolling && !bChasingPlayer && !bInvestigating)
		{
			MoveForward();
		}
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
	//If distance is greater than 'ChaseDistance' units, return to 'StartPosition'
	if ((GetActorLocation() - StartPosition).Size() > ChaseDistance)
	{
		AAIShroomController* AIController = Cast<AAIShroomController>(GetController());

		if (AIController)
		{
			bReturning = true;
			AIController->ReturnToStart(StartPosition);
		}
	}
	//If returning from having chased a player and is within 'AreaRadius', prepare to start walking around
	else if (bReturning && (GetActorLocation() - StartPosition).Size() < AreaRadius)
	{
		bChasingPlayer = false;
		bReturning = false;
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


//Goes to investigate sound
void AAIMushroom::HeardSound(AActor* Origin)
{
	//Only moves if not stunned
	if (!bStunned)
	{
		AAIShroomController* AIController = Cast<AAIShroomController>(GetController());

		if (AIController)
		{
			bInvestigating = true;
			float Dist = GetDistanceTo(Origin);

			//Investigation time is 1 second for each 100 units, plus 5 seconds
			InvestigationTime = (Dist / 100.f) + 5.f;
			InvestigationStart = GetWorld()->GetTimeSeconds();

			AIController->MoveToActor(Origin);
		}
	}
}


//Stuns the AI for 'StunTime' seconds
void AAIMushroom::Stun(float StunTime)
{
	bStunned = true;
	TimeStunned = StunTime;
	StunStart = GetWorld()->GetTimeSeconds();
}


void AAIMushroom::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//Turns around if it hits an actor other than player
	if (!OtherActor->ActorHasTag("Player") && !bChasingPlayer && !bInvestigating)
	{
		float NewAngle = FMath::RandRange(90.f, 180.f);
		AddActorLocalRotation(FRotator(0.f, NewAngle, 0.f));

		const FRotator Rotation = GetActorRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, 1);
	}

	//Stun if it hits player?
}


//When player enters the AI's sight
void AAIMushroom::OnPlayerSeen(APawn* pawn)
{
	//Won't chase player if stunned
	if (!bStunned)
	{
		AAIShroomController* AIController = Cast<AAIShroomController>(GetController());

		if (pawn->ActorHasTag("Player") && AIController)
		{
			bChasingPlayer = true;
			AIController->SetPlayerAsSeen(pawn, 0.5f);
		}
	}
}

