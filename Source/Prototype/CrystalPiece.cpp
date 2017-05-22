// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "CrystalPiece.h"


ACrystalPiece::ACrystalPiece()
{
	//Set Mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CrystalAsset(TEXT("StaticMesh'/Game/Meshes/Mesh_TinyCrystal.Mesh_TinyCrystal'"));
	if (CrystalAsset.Succeeded())
	{
		VisibleComponent->SetStaticMesh(CrystalAsset.Object);
		VisibleComponent->SetSimulatePhysics(false);
	}
}


void ACrystalPiece::BeginPlay()
{
	Super::BeginPlay();
}


void ACrystalPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
