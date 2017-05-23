// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "MyPlayerController.h"
#include "PickUp.h"
#include "Rock.h"
#include "RockProjectile.h"
#include "Stick.h"
#include "AIMushroom.h"
#include "CrystalPiece.h"
#include "CrystalProjectile.h"
#include "Lantern.h"
#include "Consumable.h"
#include "RightPlate.h"
#include "LeftPlate.h"
#include "RightDoor.h"
#include "LeftDoor.h"
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

	//Set mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlayerAsset(TEXT("StaticMesh'/Game/Meshes/CharMesh.CharMesh'"));
	if (PlayerAsset.Succeeded())
	{
		PlayerMesh->SetStaticMesh(PlayerAsset.Object);
		PlayerMesh->SetRelativeLocation(FVector(0.f, 0.f, -50.f));
	}

	CollisionComponent->SetRelativeLocation(FVector(0.f, 0.f, 5.f));
	PlayerCamera->SetRelativeLocation(FVector(-450.f, 440.f, 525.f));
	PlayerCamera->SetWorldRotation(FRotator(-40.f, -45.1f, 0.f));

	PlayerMesh->SetupAttachment(RootComponent);
	CollisionComponent->SetupAttachment(RootComponent);
	PlayerCamera->SetupAttachment(RootComponent);

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacter::OnOverlapBegin);

	GetCharacterMovement()->MaxWalkSpeed = 250.f;
	bUseControllerRotationYaw = false;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	AutoReceiveInput = EAutoReceiveInput::Player0;
	AIControllerClass = AMyPlayerController::StaticClass();

	bAttemptInteract = false;
	bHoldingItem = false;
	bHaveLantern = false;
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
	//----Consider using sphere trace instead
	TArray<AActor*> Overlapping;
	CollisionComponent->GetOverlappingActors(Overlapping);

	//Check if there's an object to interact with, and pick it up if player isn't holding anything from before
	for (auto Obj : Overlapping)
	{
		if (bAttemptInteract == false)
		{
			if ((Obj->ActorHasTag("PickUp") && !bHoldingItem))
			{
				Obj->SetActorEnableCollision(false);
				Obj->AttachToComponent(PlayerMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName(TEXT("RightHand")));
				bAttemptInteract = true;
				bHoldingItem = true;
				HeldObject = Cast<APickUp>(Obj);
			}
			else if (Obj->ActorHasTag("Consumable"))
			{
				Cast<AConsumable>(Obj)->ConsumeObject(this);
			}
			else if (Obj->ActorHasTag("Lantern") && !bHaveLantern)
			{
				Obj->SetActorEnableCollision(false);
				Obj->AttachToComponent(PlayerMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName(TEXT("LeftHand")));
				bAttemptInteract = true;
				bHaveLantern = true;
				TheLantern = Cast<ALantern>(Obj);
			}
			else if (Obj->ActorHasTag("Projectile") && !bHoldingItem)
			{
				//Creates a 'PickUp' item with the same location and rotation that the player can hold
				FVector ItemPos = Obj->GetActorLocation();
				FRotator ItemRot = Obj->GetActorRotation();
				

				UWorld* World = GetWorld();
				if (World)
				{
					FActorSpawnParameters SpawnParams;
					SpawnParams.Owner = this;
					SpawnParams.Instigator = Instigator;

					APickUp* Rock;

					if (Obj->IsA(ARockProjectile::StaticClass()))
					{
						Rock = World->SpawnActor<ARock>(ARock::StaticClass(), ItemPos, ItemRot, SpawnParams);
					}
					else
					{
						Rock = World->SpawnActor<ACrystalPiece>(ACrystalPiece::StaticClass(), ItemPos, ItemRot, SpawnParams);
					}
					
					Obj->Destroy();

					//Attach item to player
					if (Rock)
					{
						Rock->SetActorEnableCollision(false);
						Rock->AttachToComponent(PlayerMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName(TEXT("RightHand")));
						bAttemptInteract = true;
						bHoldingItem = true;
						HeldObject = Cast<APickUp>(Rock);
					}
				}
			}
			else if (bHoldingItem && (HeldObject->IsA(ALeftPlate::StaticClass()) || HeldObject->IsA(ARightPlate::StaticClass())))
			{
				for (auto Gate : Overlapping)
				{
					if (Gate->IsA(ALeftDoor::StaticClass()) && HeldObject->IsA(ALeftPlate::StaticClass()))
					{
						HeldObject->DetachRootComponentFromParent();
						Cast<ALeftDoor>(Gate)->AttachPlate(HeldObject);

						HeldObject = nullptr;
						bHoldingItem = false;
					}
					else if (Gate->IsA(ARightDoor::StaticClass()) && HeldObject->IsA(ARightPlate::StaticClass()))
					{
						HeldObject->DetachRootComponentFromParent();
						Cast<ARightDoor>(Gate)->AttachPlate(HeldObject);

						HeldObject = nullptr;
						bHoldingItem = false;
					}
				}
			}
		}
	}
}


void AMyCharacter::StopInteracting()
{
	bAttemptInteract = false;
}


void AMyCharacter::ThrowItem()
{
	//Throws the held rock by creating a projectile version of it
	if (bHoldingItem && HeldObject->IsA(ARock::StaticClass()))
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
		bHoldingItem = false;
	}
	else if (bHoldingItem && HeldObject->IsA(ACrystalPiece::StaticClass()))
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

			ACrystalProjectile* Projectile = World->SpawnActor<ACrystalProjectile>(ACrystalProjectile::StaticClass(), ItemPos, ItemRot, SpawnParams);

			if (Projectile)
			{
				FVector LaunchDirection = ItemRot.Vector();
				Projectile->ThrowInDirection(LaunchDirection);
			}
		}

		HeldObject = nullptr;
		bHoldingItem = false;
	}
	//Drops the held stick
	else if (bHoldingItem && HeldObject->IsA(AStick::StaticClass()))
	{
		HeldObject->DetachRootComponentFromParent();
		HeldObject->SetActorEnableCollision(true);
		Cast<AStick>(HeldObject)->TogglePhysics(true);

		HeldObject = nullptr;
		bHoldingItem = false;
	}
}


void AMyCharacter::SwingStick()
{
	if (bHoldingItem && HeldObject->IsA(AStick::StaticClass()))
	{
		FVector Origin;
		FVector Bounds;
		FVector EndPoint;
		
		//Sphere trace to see if any enemies are hit
		HeldObject->GetActorBounds(false, Origin, Bounds);
		EndPoint = GetActorForwardVector()*Bounds.Y;
		
		TArray<FHitResult> ActorsHit;
		FVector StartLoc = Origin;
		FVector EndLoc = Origin+EndPoint;
		float Radius = Bounds.Y;

		ECollisionChannel CollideWith = ECollisionChannel::ECC_Pawn;
		FCollisionShape CollisionShape;
		CollisionShape.ShapeType = ECollisionShape::Sphere;
		CollisionShape.SetSphere(Radius);
		FCollisionObjectQueryParams CollisionParam(ECollisionChannel::ECC_Pawn);

		bool bHitEnemy = GetWorld()->SweepMultiByObjectType(ActorsHit, StartLoc, EndLoc, FQuat::FQuat(), CollisionParam, CollisionShape);

		//Checks if it object is enemy, and stuns it if it is
		if (bHitEnemy)
		{
			for (auto Enemy : ActorsHit)
			{
				if (Enemy.GetActor()->ActorHasTag("Enemy"))
				{
					Cast<AAIMushroom>(Enemy.GetActor())->Stun(5.f);
				}
			}
		}
	}
}


void AMyCharacter::UseLantern()
{
	if (bHaveLantern)
	{
		TheLantern->ToggleLantern();
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

AActor * AMyCharacter::GetLantern()
{
	return TheLantern;
}

bool AMyCharacter::GetLanternStatus()
{
	return TheLantern->LanternStatus();
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


//-----Consider using OnHit on capsule component (see AI Muyshroom)
void AMyCharacter::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->ActorHasTag("Enemy"))
	{
		//Cast<AMyPlayerController>(GetController())->TakeDamage(10);
	}
}
