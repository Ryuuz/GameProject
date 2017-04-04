// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "Rock.h"


ARock::ARock()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> RockAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
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
