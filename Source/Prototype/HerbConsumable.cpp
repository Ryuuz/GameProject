// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "HerbConsumable.h"


AHerbConsumable::AHerbConsumable()
{
	Glow = CreateDefaultSubobject<UPointLightComponent>(TEXT("Glow"));
	Glow->SetupAttachment(RootComponent);

	//Set mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> HerbAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
	if (HerbAsset.Succeeded())
	{
		VisibleComponent->SetStaticMesh(HerbAsset.Object);
		VisibleComponent->SetWorldScale3D(FVector(0.2f, 0.2f, 0.4f));
	}

	//Apply material
	static ConstructorHelpers::FObjectFinder<UMaterial> MatHerb(TEXT("Material'/Game/Material/M_Herbs.M_Herbs'"));
	if (MatHerb.Succeeded())
	{
		VisibleComponent->SetMaterial(0, MatHerb.Object);
	}

	Glow->SetCastShadows(false);
	Glow->SetIntensity(800.f);
	Glow->SetAttenuationRadius(100.f);
	Glow->SetLightColor(FLinearColor(0.97, 0.57, 0.229));
}


void AHerbConsumable::BeginPlay()
{
	Super::BeginPlay();
}


void AHerbConsumable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHerbConsumable::ConsumeObject(APawn * Player)
{
	UE_LOG(LogTemp, Warning, TEXT("Herb consumed"));
	Destroy();
}

