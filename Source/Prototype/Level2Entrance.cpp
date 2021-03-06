// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "Level2Entrance.h"


// Sets default values
ALevel2Entrance::ALevel2Entrance()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleComponent"));

	VisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALevel2Entrance::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(FName("Level2Entrance"));
}

// Called every frame
void ALevel2Entrance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

