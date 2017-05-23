// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "Consumable.h"


// Sets default values
AConsumable::AConsumable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleComponent"));

	VisibleComponent->SetupAttachment(RootComponent);
}


// Called when the game starts or when spawned
void AConsumable::BeginPlay()
{
	Super::BeginPlay();
	
	Tags.Add(FName("Consumable"));
}


// Called every frame
void AConsumable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AConsumable::ConsumeObject(APawn* Player)
{
}

