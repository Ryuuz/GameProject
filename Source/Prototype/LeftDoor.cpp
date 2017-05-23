// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "RightDoor.h"
#include "LeftDoor.h"


// Sets default values
ALeftDoor::ALeftDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	SetRootComponent(DoorMesh);

	//Set mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DoorAsset(TEXT("StaticMesh'/Game/Meshes/Mesh_LeftGate.Mesh_LeftGate'"));
	if (DoorAsset.Succeeded())
	{
		DoorMesh->SetStaticMesh(DoorAsset.Object);
	}

	Unlocked = false;
	Open = false;
}


// Called when the game starts or when spawned
void ALeftDoor::BeginPlay()
{
	Super::BeginPlay();
	
	OpenRotation = GetActorRotation();
	OpenRotation.Yaw -= 90.f;
}


// Called every frame
void ALeftDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//If the door is unlocked but not open yet
	if (!Open && Unlocked && Right)
	{
		//If the rigt door is unlocked as well
		if (Right->IsUnlocked())
		{
			//Open door
			SetActorRotation(FMath::Lerp(GetActorRotation(), OpenRotation, 0.01f));

			if (GetActorRotation() == OpenRotation)
			{
				Open = true;
			}
		}
	}
}


//Door is unlocked when the plate is attached
void ALeftDoor::AttachPlate(AActor * Plate)
{
	Plate->SetActorEnableCollision(false);
	Plate->AttachToComponent(DoorMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName(TEXT("LeftSlot")));

	Unlocked = true;
}

