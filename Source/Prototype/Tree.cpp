// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "Tree.h"


// Sets default values
ATree::ATree()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	TreeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TreeMesh"));
	TreeMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> TreeAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
	if (TreeAsset.Succeeded())
	{
		TreeMesh->SetStaticMesh(TreeAsset.Object);
		TreeMesh->SetWorldScale3D(FVector(0.5f, 0.5f, 4.f));
	}

}

// Called when the game starts or when spawned
void ATree::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bHidden)
	{
		SetActorHiddenInGame(false);
	}
}

