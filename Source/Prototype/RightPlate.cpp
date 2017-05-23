// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "RightPlate.h"


// Sets default values
ARightPlate::ARightPlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> PlateAsset(TEXT("StaticMesh'/Game/Meshes/Mesh_RightPlate.Mesh_RightPlate'"));
	if (PlateAsset.Succeeded())
	{
		VisibleComponent->SetStaticMesh(PlateAsset.Object);
		VisibleComponent->SetSimulatePhysics(false);
	}
}

// Called when the game starts or when spawned
void ARightPlate::BeginPlay()
{
	Super::BeginPlay();
	Tags.Add(FName("RightPlate"));
}

// Called every frame
void ARightPlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

