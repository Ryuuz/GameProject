// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "TallGrass.h"
#include "MyCharacter.h"


// Sets default values
ATallGrass::ATallGrass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleComponent"));

	VisibleComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ATallGrass::BeginPlay()
{
	Super::BeginPlay();
	

	Tags.Add(FName("TallGrass"));
}

// Called every frame
void ATallGrass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
