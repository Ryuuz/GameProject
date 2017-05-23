// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "HerbConsumable.h"
#include "Crystal.h"


// Sets default values
ACrystal::ACrystal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CrystalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CrystalMesh"));
	HerbMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HerbMesh"));
	Glow = CreateDefaultSubobject<UPointLightComponent>(TEXT("Glow"));

	SetRootComponent(CrystalMesh);
	HerbMesh->SetupAttachment(RootComponent);
	Glow->SetupAttachment(RootComponent);

	//Set mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CrystalAsset(TEXT("StaticMesh'/Game/Meshes/Mesh_LargeCrystal.Mesh_LargeCrystal'"));
	if (CrystalAsset.Succeeded())
	{
		CrystalMesh->SetStaticMesh(CrystalAsset.Object);
	}

	//Set mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> HerbAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
	if (HerbAsset.Succeeded())
	{
		HerbMesh->SetStaticMesh(HerbAsset.Object);
		HerbMesh->SetWorldScale3D(FVector(0.2f, 0.2f, 0.4f));
		HerbMesh->SetRelativeLocation(FVector(0.f, 0.f, 20.f));
	}

	//Apply material
	static ConstructorHelpers::FObjectFinder<UMaterial> MatHerb(TEXT("Material'/Game/Material/M_Herbs.M_Herbs'"));
	if (MatHerb.Succeeded())
	{
		HerbMesh->SetMaterial(0, MatHerb.Object);
	}

	Glow->SetCastShadows(false);
	Glow->SetIntensity(800.f);
	Glow->SetAttenuationRadius(100.f);
	Glow->SetLightColor(FLinearColor(0.97, 0.57, 0.229));
	Glow->SetRelativeLocation(FVector(0.f, 0.f, 5.f));

	CrystalMesh->OnComponentHit.AddDynamic(this, &ACrystal::OnHit);
	HitPoints = 100;
}


// Called when the game starts or when spawned
void ACrystal::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void ACrystal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ACrystal::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	if(OtherActor->ActorHasTag("Projectile"))
	{
		HitPoints -= 20;
		UE_LOG(LogTemp, Warning, TEXT("Hit"));

		if (HitPoints <= 0)
		{
			FVector HerbPos = GetActorLocation();
			HerbPos.Z += 20.f;
			FRotator HerbRot = GetActorRotation();

			UWorld* World = GetWorld();
			if (World)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.Instigator = Instigator;

				World->SpawnActor<AHerbConsumable>(AHerbConsumable::StaticClass(), HerbPos, HerbRot, SpawnParams);

				Destroy();
			}
		}
	}	
}

