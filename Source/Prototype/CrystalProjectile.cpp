// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "AIGuardGhost.h"
#include "AIPatrolGhost.h"
#include "Landscape.h"
#include "CrystalProjectile.h"


// Sets default values
ACrystalProjectile::ACrystalProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleComponent"));
	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));

	CollisionComponent->InitSphereRadius(10.f);

	//Set mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CrystalAsset(TEXT("StaticMesh'/Game/Meshes/Mesh_TinyCrystal.Mesh_TinyCrystal'"));
	if (CrystalAsset.Succeeded())
	{
		VisibleComponent->SetStaticMesh(CrystalAsset.Object);
	}

	RootComponent = CollisionComponent;
	VisibleComponent->SetupAttachment(RootComponent);
	CollisionComponent->SetCollisionObjectType(ECC_GameTraceChannel1);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	//Values for the projectile component
	ProjectileComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileComponent->InitialSpeed = 900.f;
	ProjectileComponent->MaxSpeed = 950.f;
	ProjectileComponent->bRotationFollowsVelocity = true;
	ProjectileComponent->bShouldBounce = true;
	ProjectileComponent->Bounciness = 0.3f;

	CollisionComponent->OnComponentHit.AddDynamic(this, &ACrystalProjectile::OnHit);
	bTouchedGround = false;
}


// Called when the game starts or when spawned
void ACrystalProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	Tags.Add(FName("Projectile"));
}


// Called every frame
void ACrystalProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ACrystalProjectile::ThrowInDirection(const FVector & ThrowDirection)
{
	ProjectileComponent->Velocity = ThrowDirection * ProjectileComponent->InitialSpeed;
}


void ACrystalProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	if (OtherActor->GetClass()->IsChildOf(ALandscape::StaticClass()) && !bTouchedGround)
	{
		bTouchedGround = true;
	}
	else if (OtherActor->ActorHasTag("Enemy") && !bTouchedGround)
	{
		(OtherActor->IsA(AAIPatrolGhost::StaticClass())) ? Cast<AAIPatrolGhost>(OtherActor)->Stun(2.f) : Cast<AAIGuardGhost>(OtherActor)->Stun(2.f);
	}
}

