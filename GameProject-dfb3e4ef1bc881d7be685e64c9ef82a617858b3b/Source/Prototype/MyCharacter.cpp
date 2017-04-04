// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "MyPlayerController.h"
#include "PickUp.h"
#include "RockProjectile.h"
#include "MyCharacter.h"


// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComp"));
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));

	CollisionComponent->InitCapsuleSize(45.f, 70.f);
	GetCapsuleComponent()->InitCapsuleSize(30.f, 60.f);

	CollisionComponent->SetRelativeLocation(FVector(0.f, 0.f, 5.f));
	PlayerCamera->SetRelativeLocation(FVector(-320.f, 350.f, 380.f));
	PlayerCamera->SetWorldRotation(FRotator(-40.f, -45.1f, 0.f));

	PlayerMesh->SetupAttachment(RootComponent);
	CollisionComponent->SetupAttachment(RootComponent);
	PlayerCamera->SetupAttachment(RootComponent);

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacter::OnOverlapBegin);

	AttemptInteract = false;
	HoldingItem = false;
	HeldObject = nullptr;
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

	Raycast();


	//handles rotation of character
	
	//if (upRot == 1 || downRot == 1 || leftRot == 1 || rightRot == 1) {
		AverageRot = CurrentRot / (upRot + downRot + leftRot + rightRot);


		if (upRot == 1 && rightRot == 1 && downRot == 0 && leftRot == 0) {
			AverageRot = 0;
		}
		if (upRot == 1 && rightRot == 1 && downRot == 0 && leftRot == 1) {
			AverageRot = -45;
		}

		FRotator RotationSet = FRotator(0, AverageRot, 0);
		PlayerMesh->SetWorldRotation(RotationSet);

	//}
	
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


void AMyCharacter::Interacting()
{
	//Get all actors within player's collision component
	TArray<AActor*> Overlapping;
	GetOverlappingActors(Overlapping);

	//Check if there's a PickUp object, and pick it up if there is
	for (auto Obj : Overlapping)
	{
		if (AttemptInteract == false)
		{
			if ((Obj->ActorHasTag("PickUp") && HoldingItem == false))
			{
				Obj->SetActorEnableCollision(false);
				Obj->AttachToComponent(PlayerMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName(TEXT("RightHand")));
				AttemptInteract = true;
				HoldingItem = true;
				HeldObject = Cast<APickUp>(Obj);
			}
			else if (Obj->ActorHasTag("Consumable"))
			{
				Obj->Destroy();
			}
		}
	}
}


void AMyCharacter::StopInteracting()
{
	AttemptInteract = false;
}

void AMyCharacter::ThrowItem()
{
	if (HoldingItem)
	{
		FVector ItemPos = HeldObject->GetActorLocation();
		FRotator ItemRot = HeldObject->GetActorRotation();
		ItemRot.Pitch += 20.f;
		HeldObject->Destroy();

		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			ARockProjectile* Projectile = World->SpawnActor<ARockProjectile>(ARockProjectile::StaticClass(), ItemPos, ItemRot, SpawnParams);

			if (Projectile)
			{
				FVector LaunchDirection = ItemRot.Vector();
				Projectile->ThrowInDirection(LaunchDirection);
			}
		}

		HeldObject = nullptr;
		HoldingItem = false;
	}
}




//SETS ROTATION VALUES ON KEY DOWN AND REMOVES THEM ON KEY UP
void AMyCharacter::StartRotationUp()
{
	upRot = 1;
	CurrentRot -= 45;
}
void AMyCharacter::StopRotationUp()
{
	upRot = 0;
	CurrentRot += 45;
}


void AMyCharacter::StartRotationDown()
{
	downRot = 1;
	CurrentRot -= 225;
}
void AMyCharacter::StopRotationDown()
{
	downRot = 0;
	CurrentRot += 225;
}


void AMyCharacter::StartRotationLeft()
{
	leftRot = 1;
	CurrentRot -= 135;
}
void AMyCharacter::StopRotationLeft()
{
	leftRot = 0;
	CurrentRot += 135;
}


void AMyCharacter::StartRotationRight()
{
	rightRot = 1;
	CurrentRot -= 315;
}
void AMyCharacter::StopRotationRight()
{
	rightRot = 0;
	CurrentRot += 315;
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
