// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "RockProjectile.h"


// Sets default values
ARockProjectile::ARockProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleComponent"));
	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));

	CollisionComponent->InitSphereRadius(10.f);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> RockAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (RockAsset.Succeeded())
	{
		VisibleComponent->SetStaticMesh(RockAsset.Object);
		VisibleComponent->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
		VisibleComponent->SetSimulatePhysics(false);
	}

	RootComponent = CollisionComponent;
	VisibleComponent->SetupAttachment(RootComponent);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	ProjectileComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileComponent->InitialSpeed = 500.f;
	ProjectileComponent->MaxSpeed = 550.f;
	ProjectileComponent->bRotationFollowsVelocity = true;
	ProjectileComponent->bShouldBounce = true;
	ProjectileComponent->Bounciness = 0.3f;
}

// Called when the game starts or when spawned
void ARockProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	Tags.Add(FName("Projectile"));
}

// Called every frame
void ARockProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARockProjectile::ThrowInDirection(const FVector & ThrowDirection)
{
	ProjectileComponent->Velocity = ThrowDirection * ProjectileComponent->InitialSpeed;
}

