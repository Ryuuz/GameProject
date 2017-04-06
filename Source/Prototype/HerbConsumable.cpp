// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "HerbConsumable.h"


AHerbConsumable::AHerbConsumable()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> HerbAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
	if (HerbAsset.Succeeded())
	{
		VisibleComponent->SetStaticMesh(HerbAsset.Object);
		VisibleComponent->SetWorldScale3D(FVector(0.2f, 0.2f, 0.4f));
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MatHerb(TEXT("Material'/Game/Material/M_Herbs.M_Herbs'"));
	if (MatHerb.Succeeded())
	{
		VisibleComponent->SetMaterial(0, MatHerb.Object);
	}
}

void AHerbConsumable::BeginPlay()
{
	Super::BeginPlay();
}

void AHerbConsumable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

