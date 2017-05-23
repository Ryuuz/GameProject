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
	static ConstructorHelpers::FObjectFinder<UStaticMesh> LanternAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (LanternAsset.Succeeded())
	{
		LanternMesh->SetStaticMesh(LanternAsset.Object);
		LanternMesh->SetWorldScale3D(FVector(0.15f, 0.15f, 0.3f));
		LanternMesh->SetSimulatePhysics(false);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MatGlass(TEXT("Material'/Game/Material/M_Glass.M_Glass'"));
	if (MatGlass.Succeeded())
	{
		LanternMesh->SetMaterial(0, MatGlass.Object);
	}

	LanternLight->SetRelativeLocation(FVector(0.f, 0.f, 10.f));
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
	if (OilLevel > 0)
	{
		bLanternOn = !bLanternOn;
		LanternLight->SetVisibility(bLanternOn);

		if (bLanternOn)
		{
			CurrentTime = GetWorld()->GetTimeSeconds();
			UE_LOG(LogTemp, Warning, TEXT("Lantern on. Oil level is %d"), OilLevel);
		}
	}
}

void ALantern::RestoreOil(int32 Amount)
{
	OilLevel += Amount;
	OilLevel -= OilLevel % 100;

	UE_LOG(LogTemp, Warning, TEXT("Oil refilled to %d"), OilLevel);
}

