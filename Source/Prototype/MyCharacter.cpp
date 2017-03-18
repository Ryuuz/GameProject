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

	/*FHitResult Hit;
	bool HitResult = false;

	HitResult = GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_WorldStatic), true, Hit);

	if (HitResult)
	{
		FVector CursorFV = Hit.ImpactNormal;
		FRotator CursorR = CursorFV.Rotation();


		FVector CursorLocation = Hit.Location;
//		UE_LOG(LogTemp, Warning, TEXT("Cursor location %s!"), *CursorLocation.ToString());
		FVector TempLocation = FVector(CursorLocation.X, CursorLocation.Y, 30.f);
		//        if (CursorMesh)
		//            CursorMesh->SetWorldLocation(TempLocation);
		//        else
		//            UE_LOG(LogTemp, Warning, TEXT("Cursor Mesh not found"));

		FVector NewDirection = TempLocation - GetActorLocation();
		NewDirection.Z = 0.f;
		NewDirection.Normalize();
		PlayerMesh->SetWorldRotation(NewDirection.Rotation());
	}*/

	Raycast();
}


// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


//https://wiki.unrealengine.com/First_Person_Shooter_C%2B%2B_Tutorial for movement
void AMyCharacter::Move_XAxis(float AxisValue)
{
	if (Controller != NULL && AxisValue != 0.f)
	{
		FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, AxisValue);
	}
}


void AMyCharacter::Move_YAxis(float AxisValue)
{
	if (Controller != NULL && AxisValue != 0.f)
	{
		FRotator Rotation = Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, AxisValue);
	}
}


void AMyCharacter::JumpUp()
{
	ACharacter::Jump();
}

void AMyCharacter::StopJump()
{
	ACharacter::StopJumping();
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
		//Cast<AMyPlayerController>(GetController())->TakeDamage(10);
	}
}
