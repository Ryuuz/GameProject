// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "MyPlayerController.h"
#include "MyCharacter.h"


// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));

	CollisionComponent->InitSphereRadius(40.f);
	PlayerCamera->SetRelativeLocation(FVector(-320.f, 350.f, 380.f));
	PlayerCamera->SetWorldRotation(FRotator(-40.1f, -45.1f, 0.f));

	PlayerMesh->SetupAttachment(RootComponent);
	CollisionComponent->SetupAttachment(RootComponent);
	PlayerCamera->SetupAttachment(RootComponent);

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacter::OnOverlapBegin);	

	Lantern = true;
	Jumping = false;
	JumpTime = 0.8f;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	Tags.Add(FName("Player"));
}

// Called every frame
void AMyCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	//Move character
	if (!CurrentVelocity.IsZero())
	{
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}

	if (Jumping)
	{
		CurrentVelocity.Z = FMath::Clamp(1.f, 0.f, 1.f) * 200.f;
		
		if (CurrentVelocity.Z > 200.f)
		{
			CurrentVelocity.Z = 200.f;
		}

		float NewZ = GetActorLocation().Z + (CurrentVelocity.Z * DeltaTime);
		FVector NewLocation = GetActorLocation();
		NewLocation.Z = NewZ;
		SetActorLocation(NewLocation);

		if ((GetWorld()->GetTimeSeconds() - Jumped) > JumpTime)
		{
			Jumping = false;
		}
	}
	else if(!Jumping && CurrentVelocity.Z != 0)
	{
		CurrentVelocity.Z = FMath::Clamp(-1.f, -1.f, 0.f) * 300.f;
		
		if (CurrentVelocity.Z < -300.f)
		{
			CurrentVelocity.Z = -300.f;
		}

		float NewZ = GetActorLocation().Z + (CurrentVelocity.Z * DeltaTime);
		FVector NewLocation = GetActorLocation();
		NewLocation.Z = NewZ;
		SetActorLocation(NewLocation);
	}

	Raycast();
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void AMyCharacter::Move_XAxis(float AxisValue)
{
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.f, 1.f) * 200.f;
}


void AMyCharacter::Move_YAxis(float AxisValue)
{
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.f, 1.f) * 200.f;
}


void AMyCharacter::JumpUp()
{
	if (!Jumping)
	{
		Jumped = GetWorld()->GetTimeSeconds();
		Jumping = true;
	}
}


//Casts a ray and sees if it hits a tree
//Created by following the tutorial made by Reuben Ward at https://www.youtube.com/watch?v=YrlagR_Hb2Q&list=PL3gCaTLUSAUvi_XbOXOZic20quqAWuY-q&index=5
void AMyCharacter::Raycast()
{
	FHitResult* ObjectHit = new FHitResult();
	FVector StartTrace = PlayerCamera->GetComponentLocation();
	FVector EndTrace = GetActorLocation();
	FCollisionQueryParams* CQP = new FCollisionQueryParams();

	if (GetWorld()->LineTraceSingleByChannel(*ObjectHit, StartTrace, EndTrace, ECC_Visibility, *CQP))
	{
		if (ObjectHit->GetActor()->ActorHasTag("Tree"))
		{
			ObjectHit->GetActor()->SetActorHiddenInGame(true);
		}
	}
}

void AMyCharacter::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->ActorHasTag("Enemy"))
	{
		OtherActor->Destroy();
		Cast<AMyPlayerController>(GetController())->TakeDamage(10);
	}
}
