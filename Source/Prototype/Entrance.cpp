// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "Entrance.h"


// Sets default values
AEntrance::AEntrance()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleComponent"));

	VisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEntrance::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(FName("Entrance"));
}

// Called every frame
void AEntrance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

