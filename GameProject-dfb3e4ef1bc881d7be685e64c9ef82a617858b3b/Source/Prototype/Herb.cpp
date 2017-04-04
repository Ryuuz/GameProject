// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "Herb.h"


// Sets default values
AHerb::AHerb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	HerbMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TreeMesh"));
	HerbMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> HerbAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
	if (HerbAsset.Succeeded())
	{
		HerbMesh->SetStaticMesh(HerbAsset.Object);
		HerbMesh->SetWorldScale3D(FVector(0.2f, 0.2f, 0.4f));
	}

	HerbMesh->OnComponentBeginOverlap.AddDynamic(this, &AHerb::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AHerb::BeginPlay()
{
	Super::BeginPlay();
	Tags.Add(FName("Herb"));
}

// Called every frame
void AHerb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHerb::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		Destroy();
	}
}

