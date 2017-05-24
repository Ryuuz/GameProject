// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "Lantern.h"


// Sets default values
ALantern::ALantern()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LanternMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LanternMesh"));
	LanternLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("LanternLight"));

	SetRootComponent(LanternMesh);
	LanternLight->SetupAttachment(RootComponent);

	//Set Mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> LanternAsset(TEXT("StaticMesh'/Game/Meshes/Mesh_Lantern.Mesh_Lantern'"));
	if (LanternAsset.Succeeded())
	{
		LanternMesh->SetStaticMesh(LanternAsset.Object);
		LanternMesh->SetSimulatePhysics(false);
	}

	//Settings for the light
	LanternLight->SetRelativeLocation(FVector(0.f, 0.f, -30.f));
	LanternLight->SetCastShadows(false);
	LanternLight->SetIntensity(1000.f);
	LanternLight->SetLightColor(FLinearColor(0.97, 0.57, 0.229));
	LanternLight->SetAttenuationRadius(500.f);
	LanternLight->bVisible = false;

	OilLevel = 100;
	bLanternOn = false;
}


// Called when the game starts or when spawned
void ALantern::BeginPlay()
{
	Super::BeginPlay();
	Tags.Add(FName("Lantern"));
}


// Called every frame
void ALantern::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Oil is used up over time when the lantern is on
	if (bLanternOn && (GetWorld()->GetTimeSeconds() - CurrentTime) >= DepleteTime)
	{
		OilLevel--;
		CurrentTime = GetWorld()->GetTimeSeconds();
	}

	if (OilLevel <= 0 && bLanternOn)
	{
		bLanternOn = false;
		LanternLight->SetVisibility(false);
	}
}


void ALantern::ToggleLantern()
{
	//Can only use lantern if there is oil left
	if (OilLevel > 0)
	{
		bLanternOn = !bLanternOn;
		LanternLight->SetVisibility(bLanternOn);

		if (bLanternOn)
		{
			CurrentTime = GetWorld()->GetTimeSeconds();
		}
	}
}


void ALantern::RestoreOil(int32 Amount)
{
	OilLevel += Amount;
	if (OilLevel > 100)
	{
		OilLevel = 100;
	}
}

