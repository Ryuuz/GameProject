// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "MyCharacter.h"
#include "HerbConsumable.h"


AHerbConsumable::AHerbConsumable()
{
	Glow = CreateDefaultSubobject<UPointLightComponent>(TEXT("Glow"));
	Glow->SetupAttachment(RootComponent);

	//Set mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> HerbAsset(TEXT("StaticMesh'/Game/Meshes/lotus_2.lotus_2'"));
	if (HerbAsset.Succeeded())
	{
		VisibleComponent->SetStaticMesh(HerbAsset.Object);
	}

	//Herbs glow so the player can easily spot them
	Glow->SetCastShadows(false);
	Glow->SetIntensity(800.f);
	Glow->SetAttenuationRadius(100.f);
	Glow->SetLightColor(FLinearColor(0.97, 0.57, 0.229));
	Glow->SetRelativeLocation(FVector(0.f, 0.f, 20.f));
}


void AHerbConsumable::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(FName("HerbConsumable"));
}


void AHerbConsumable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AHerbConsumable::ConsumeObject(APawn * Player)
{
	Cast<AMyCharacter>(Player)->IncreaseHerb();
	Destroy();
}

