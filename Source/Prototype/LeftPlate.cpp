// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "LeftPlate.h"


// Sets default values
ALeftPlate::ALeftPlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlateAsset(TEXT("StaticMesh'/Game/Meshes/Mesh_LeftPlate.Mesh_LeftPlate'"));
	if (PlateAsset.Succeeded())
	{
		VisibleComponent->SetStaticMesh(PlateAsset.Object);
		VisibleComponent->SetSimulatePhysics(false);
	}
}

// Called when the game starts or when spawned
void ALeftPlate::BeginPlay()
{
	Super::BeginPlay();
	Tags.Add(FName("LeftPlate"));
}

// Called every frame
void ALeftPlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

