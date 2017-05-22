// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/PawnSensingComponent.h"
#include "AIShroomController.h"
#include "AIPatrolGhost.h"


// Sets default values
AAIPatrolGhost::AAIPatrolGhost()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PatrolMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AIMesh"));
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

	PatrolMesh->SetupAttachment(RootComponent);
	PawnSensingComp->SetPeripheralVisionAngle(90.f);

	//Set mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> AIAsset(TEXT("StaticMesh'/Game/Meshes/Ghost_small.Ghost_small'"));
	if (AIAsset.Succeeded())
	{
		PatrolMesh->SetStaticMesh(AIAsset.Object);
		PatrolMesh->SetRelativeLocation(FVector(0.f, 0.f, -20.f));
	}

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AAIPatrolGhost::OnHit);
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
	PawnSensingComp->SightRadius = 1000.f;
	AIControllerClass = AAIShroomController::StaticClass();

	bChasingPlayer = false;
	bReturning = false;
	bStunned = false;
}


// Called when the game starts or when spawned
void AAIPatrolGhost::BeginPlay()
{
	Super::BeginPlay();
	
	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AAIPatrolGhost::OnPlayerSeen);
	}

	StartPosition = GetActorLocation();
	PatrolRotation = GetActorRotation();
	Tags.Add(FName("Enemy"));
}


// Called every frame
void AAIPatrolGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	CurrentZ += DeltaHeight * 20.0f;
	RunningTime += DeltaTime;
	PatrolMesh->SetRelativeLocation(FVector(0.f, 0.f, CurrentZ));

	if (bStunned && (GetWorld()->GetTimeSeconds() - StunStart) >= TimeStunned)
	{
		bStunned = false;
	}
	
	if (!bStunned)
	{
		//Checks if it has gotten too far from its spawn point
		DistanceFromStart();

		//Walk around if there is no player to chase
		if (!bChasingPlayer)
		{
			MoveForward();
		}
	}
}


// Called to bind functionality to input
void AAIPatrolGhost::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void AAIPatrolGhost::DistanceFromStart()
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
	//If returning from having chased a player and is close enough to the 'StartPosition'
	else if (bReturning && (GetActorLocation() - StartPosition).Size() <= 100.f)
	{		
		SetActorRotation(PatrolRotation);

		bChasingPlayer = false;
		bReturning = false;
	}
}


void AAIPatrolGhost::MoveForward()
{
	FVector Direction;
	FVector NextPos = GetActorLocation() + 1.f*GetVelocity();

	//If at the edge of the 'AreaRadius', turn around a random degree
	if ((FMath::Square(StartPosition.X - NextPos.X) + FMath::Square(StartPosition.Y - NextPos.Y)) >= FMath::Square(PatrolDistance - GetCapsuleComponent()->GetUnscaledCapsuleRadius()))
	{
		AddActorLocalRotation(FRotator(0.f, 180.f, 0.f));
	}

	const FRotator Rotation = GetActorRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	AddMovementInput(Direction, 1);
}


void AAIPatrolGhost::Stun(float StunTime)
{
	bStunned = true;
	TimeStunned = StunTime;
	StunStart = GetWorld()->GetTimeSeconds();
}


void AAIPatrolGhost::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	if (!OtherActor->ActorHasTag("Player") && !bChasingPlayer)
	{
		AddActorLocalRotation(FRotator(0.f, 180.f, 0.f));

		const FRotator Rotation = GetActorRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, 1);
	}
}


void AAIPatrolGhost::OnPlayerSeen(APawn * pawn)
{
	//Won't chase player if stunned
	if (!bStunned)
	{
		AAIShroomController* AIController = Cast<AAIShroomController>(GetController());

		if (pawn->ActorHasTag("Player") && AIController)
		{
			bChasingPlayer = true;
			AIController->SetPlayerAsSeen(pawn, 2.f);
		}
	}
}

