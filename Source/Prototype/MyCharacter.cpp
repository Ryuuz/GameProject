// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "MyCharacter.h"


// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));

	PlayerCamera->SetRelativeLocation(FVector(-320.f, 350.f, 380.f));
	PlayerCamera->SetWorldRotation(FRotator(-40.1f, -45.1f, 0.f));

	PlayerMesh->SetupAttachment(RootComponent);
	PlayerCamera->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (!CurrentVelocity.IsZero())
	{
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}

	Raycast();
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveX", this, &AMyCharacter::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, &AMyCharacter::Move_YAxis);
}


void AMyCharacter::Move_XAxis(float AxisValue)
{
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.f, 1.f) * 100.f;
}


void AMyCharacter::Move_YAxis(float AxisValue)
{
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.f, 1.f) * 100.f;
}


void AMyCharacter::Raycast()
{
	FHitResult* ObjectHit = new FHitResult();
	FVector StartTrace = PlayerCamera->GetComponentLocation();
	FVector EndTrace = GetActorLocation();
	FCollisionQueryParams* CQP = new FCollisionQueryParams();

	if (GetWorld()->LineTraceSingleByChannel(*ObjectHit, StartTrace, EndTrace, ECC_Visibility, *CQP))
	{
		if (ObjectHit->GetActor()->GetName() != GetName())
		{
			ObjectHit->GetActor()->SetActorHiddenInGame(true);
			//UE_LOG(LogTemp, Warning, TEXT("Got Actor: %s"), *ObjectHit->GetActor()->GetName());
		}
	}
}