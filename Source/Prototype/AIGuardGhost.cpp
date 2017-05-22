// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/PawnSensingComponent.h"
#include "AIShroomController.h"
#include "DrawDebugHelpers.h"
#include "AIGuardGhost.h"


// Sets default values
AAIGuardGhost::AAIGuardGhost()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GuardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AIMesh"));

	GuardMesh->SetupAttachment(RootComponent);

	//Set mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> AIAsset(TEXT("StaticMesh'/Game/Meshes/Ghost_large.Ghost_large'"));
	if (AIAsset.Succeeded())
	{
		GuardMesh->SetStaticMesh(AIAsset.Object);
		GuardMesh->SetRelativeLocation(FVector(0.f, 0.f, -70.f));
	}

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AAIGuardGhost::OnHit);
	GetCharacterMovement()->MaxWalkSpeed = 150.f;
	AIControllerClass = AAIShroomController::StaticClass();

	bReturning = false;
	bInvestigating = false;
	bStunned = false;
}


// Called when the game starts or when spawned
void AAIGuardGhost::BeginPlay()
{
	Super::BeginPlay();

	StartPosition = GetActorLocation();
	GuardDirection = GetActorRotation();
	Tags.Add(FName("Enemy"));
}


// Called every frame
void AAIGuardGhost::Tick(float DeltaTime)
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
		//When done investigating object
		if (bInvestigating && (GetWorld()->GetTimeSeconds() - InvestigationStart) >= InvestigationTime)
		{
			bInvestigating = false;

			//Returning to start
			AAIShroomController* AIController = Cast<AAIShroomController>(GetController());

			if (AIController)
			{
				AIController->ReturnToStart(StartPosition);
				bReturning = true;
			}
		}

		//Rotate to face the intended direction when close enough to start position
		if (bReturning && (GetActorLocation() - StartPosition).Size() <= 100.f)
		{
			bReturning = false;
		}
		
		//Keep checking for crystals nearby while guarding
		if (!bInvestigating && !bReturning)
		{
			SphereTrace();

			if (GetActorRotation() != GuardDirection)
			{
				SetActorRotation(GuardDirection);
			}
		}
	}	
}


// Called to bind functionality to input
void AAIGuardGhost::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void AAIGuardGhost::Stun(float StunTime)
{
	bStunned = true;
	TimeStunned = StunTime;
	StunStart = GetWorld()->GetTimeSeconds();
}


void AAIGuardGhost::SphereTrace()
{
	float Height = 200.f;
	float Radius = 500.f;

	TArray<FHitResult> ActorsHit;
	FVector StartLoc = GetActorLocation();
	FVector EndLoc = GetActorLocation();
	EndLoc += GetActorForwardVector() * Height;

	ECollisionChannel CollideWith = ECollisionChannel::ECC_GameTraceChannel1;
	FCollisionShape CollisionShape;
	CollisionShape.ShapeType = ECollisionShape::Sphere;
	CollisionShape.SetSphere(Radius);
	FCollisionObjectQueryParams CollisionParam(ECollisionChannel::ECC_GameTraceChannel1);

	bool bHitObject = GetWorld()->SweepMultiByObjectType(ActorsHit, StartLoc, EndLoc, FQuat::FQuat(), CollisionParam, CollisionShape);

	if (bHitObject)
	{
		InvestigateObject(ActorsHit);
	}
}


void AAIGuardGhost::InvestigateObject(TArray<FHitResult> Objs)
{
	//Crystal has to be closer than 'AcceptableDistance' for AI to investigate it
	float Closest = AcceptableDistance;
	AActor* ToInvestigate;

	for (auto Crystal : Objs)
	{
		//If it has already investigated some crystals
		if (InvestigatedObjs.Num() > 0)
		{
			bool New = true;

			//Check to see if the current one is an uninvestigated one
			for (auto Seen : InvestigatedObjs)
			{
				if (Crystal.GetActor() == Seen)
				{
					New = false;
				}
			}

			//If it hasn't been investigated and is close enough
			if (New && (Crystal.GetActor()->GetActorLocation() - StartPosition).Size() < Closest)
			{
				Closest = GetDistanceTo(Crystal.GetActor());
				ToInvestigate = Crystal.GetActor();
			}
		}
		//Else if no crystal has been investigated yet and this one is close enough
		else if (GetDistanceTo(Crystal.GetActor()) < Closest)
		{
			Closest = GetDistanceTo(Crystal.GetActor());
			ToInvestigate = Crystal.GetActor();
		}
	}
	
	//If a crystal was found within the acceptable distance
	if (Closest != AcceptableDistance)
	{
		InvestigatedObjs.Add(ToInvestigate);

		AAIShroomController* AIController = Cast<AAIShroomController>(GetController());

		if (AIController)
		{
			bInvestigating = true;

			//Investigation time is 1 second for each 100 units, plus 5 seconds
			InvestigationTime = (Closest / 100.f) + 5.f;
			InvestigationStart = GetWorld()->GetTimeSeconds();

			AIController->MoveToActor(ToInvestigate);
		}
	}
}


void AAIGuardGhost::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
}

