// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "LanternConsumable.h"


// Sets default values
ALanternConsumable::ALanternConsumable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleComponent"));

	VisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ALanternConsumable::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(FName("LanternConsumable"));
}

// Called every frame
void ALanternConsumable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

