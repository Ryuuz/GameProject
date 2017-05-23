// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "MyCharacter.h"
#include "Lantern.h"
#include "LanternOil.h"


ALanternOil::ALanternOil()
{
	//Set mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> OilAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
	if (OilAsset.Succeeded())
	{
		VisibleComponent->SetStaticMesh(OilAsset.Object);
		VisibleComponent->SetWorldScale3D(FVector(0.2f, 0.2f, 0.4f));
	}
}


void ALanternOil::BeginPlay()
{
	Super::BeginPlay();
}


void ALanternOil::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ALanternOil::ConsumeObject(APawn * Player)
{
	if (Cast<AMyCharacter>(Player)->HoldingLantern())
	{
		AActor* Lantern = Cast<AMyCharacter>(Player)->GetLantern();
		Cast<ALantern>(Lantern)->RestoreOil(25);
		Destroy();
	}	
}
