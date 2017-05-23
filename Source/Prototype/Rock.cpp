// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "Rock.h"


ARock::ARock()
{
	//Set Mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> RockAsset(TEXT("StaticMesh'/Game/Meshes/Mesh.Mesh'"));
	if (RockAsset.Succeeded())
	{
		VisibleComponent->SetStaticMesh(RockAsset.Object);
		VisibleComponent->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
		VisibleComponent->SetSimulatePhysics(false);
	}
}


void ARock::BeginPlay()
{
	Super::BeginPlay();
}


void ARock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
