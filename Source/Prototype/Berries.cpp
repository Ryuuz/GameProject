// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "MyPlayerController.h"
#include "MyCharacter.h"
#include "Berries.h"


ABerries::ABerries()
{
	//Set mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BerryAsset(TEXT("StaticMesh'/Game/Meshes/Mesh_Berry.Mesh_Berry'"));
	if (BerryAsset.Succeeded())
	{
		VisibleComponent->SetStaticMesh(BerryAsset.Object);
	}
}


void ABerries::BeginPlay()
{
	Super::BeginPlay();
}


void ABerries::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ABerries::ConsumeObject(APawn * Player)
{
	AController* PlayerController = Cast<AMyCharacter>(Player)->GetController();
	Cast<AMyPlayerController>(PlayerController)->RegainHealth(20);
	Destroy();
}

