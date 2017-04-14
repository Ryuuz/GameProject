// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "Landscape.h"
#include "Stick.h"


AStick::AStick()
{
	PrimaryActorTick.bCanEverTick = true;

	//Set mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StickAsset(TEXT("StaticMesh'/Game/Meshes/Mesh_Stick.Mesh_Stick'"));
	if (StickAsset.Succeeded())
	{
		VisibleComponent->SetStaticMesh(StickAsset.Object);
		VisibleComponent->SetWorldScale3D(FVector(1.f, 1.8f, 1.8f));	
	}
	
	//Physics and collision
	VisibleComponent->SetSimulatePhysics(true);
	VisibleComponent->SetNotifyRigidBodyCollision(true);

	VisibleComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	VisibleComponent->OnComponentHit.AddDynamic(this, &AStick::OnHit);
	bTouchedGround = false;
	bHitting = false;
}


void AStick::BeginPlay()
{
	Super::BeginPlay();
}


void AStick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AStick::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	//Turns of physics when hitting ground so that player can pick it up
	if (OtherActor->GetClass()->IsChildOf(ALandscape::StaticClass()) && !bTouchedGround)
	{
		TogglePhysics(false);
	}
}


//Turns physics on or off
void AStick::TogglePhysics(bool bHasPhysics)
{
	bTouchedGround = !bHasPhysics;
	VisibleComponent->SetSimulatePhysics(bHasPhysics);
}

