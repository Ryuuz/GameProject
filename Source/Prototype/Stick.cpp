// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "Stick.h"


AStick::AStick()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StickAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
	if (StickAsset.Succeeded())
	{
		VisibleComponent->SetStaticMesh(StickAsset.Object);
		VisibleComponent->SetWorldScale3D(FVector(0.1f, 0.1f, 0.8f));
		VisibleComponent->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
		VisibleComponent->SetRelativeLocation(FVector(40.f, 0.f, 0.f));
		VisibleComponent->SetSimulatePhysics(false);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MatStick(TEXT("Material'/Game/Material/M_Trunk.M_Trunk'"));
	if (MatStick.Succeeded())
	{
		VisibleComponent->SetMaterial(0, MatStick.Object);
	}
}

void AStick::BeginPlay()
{
	Super::BeginPlay();
}

void AStick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

