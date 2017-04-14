// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "Hedge.h"


// Sets default values
AHedge::AHedge()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	HedgeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HedgeMesh"));
	HedgeMesh->SetupAttachment(RootComponent);

	//Set mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> HedgeAsset(TEXT("StaticMesh'/Game/Meshes/Mesh_Hedge.Mesh_Hedge'"));
	if (HedgeAsset.Succeeded())
	{
		HedgeMesh->SetStaticMesh(HedgeAsset.Object);
	}
}


// Called when the game starts or when spawned
void AHedge::BeginPlay()
{
	Super::BeginPlay();
	Tags.Add(FName("Tree"));
}


// Called every frame
void AHedge::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Make the actor visible if hidden
	if (bHidden)
	{
		SetActorHiddenInGame(false);
	}
}

