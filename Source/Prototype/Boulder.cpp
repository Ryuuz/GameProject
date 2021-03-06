// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "Boulder.h"


// Sets default values
ABoulder::ABoulder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	BoulderMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoulderMesh"));
	BoulderMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABoulder::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABoulder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

