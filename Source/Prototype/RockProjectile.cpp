// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "Landscape.h"
#include "AIMushroom.h"
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

	//Set mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> RockAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (RockAsset.Succeeded())
	{
		VisibleComponent->SetStaticMesh(RockAsset.Object);
		VisibleComponent->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
	}

	//Apply material
	static ConstructorHelpers::FObjectFinder<UMaterial> MatRock(TEXT("Material'/Game/Material/M_Stone.M_Stone'"));
	if (MatRock.Succeeded())
	{
		VisibleComponent->SetMaterial(0, MatRock.Object);
	}

	RootComponent = CollisionComponent;
	VisibleComponent->SetupAttachment(RootComponent);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

	//Values for the projectile component
	ProjectileComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileComponent->InitialSpeed = 900.f;
	ProjectileComponent->MaxSpeed = 950.f;
	ProjectileComponent->bRotationFollowsVelocity = true;
	ProjectileComponent->bShouldBounce = true;
	ProjectileComponent->Bounciness = 0.3f;

	CollisionComponent->OnComponentHit.AddDynamic(this, &ARockProjectile::OnHit);
	bTouchedGround = false;
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


//The direction to throw the rock in
void ARockProjectile::ThrowInDirection(const FVector & ThrowDirection)
{
	ProjectileComponent->Velocity = ThrowDirection * ProjectileComponent->InitialSpeed;
}


void ARockProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	bool bMadeSound = false;

	//Make sound if rock touched the ground. Will not make any more sounds after this
	if (OtherActor->GetClass()->IsChildOf(ALandscape::StaticClass()) && !bTouchedGround)
	{
		bTouchedGround = true;
		bMadeSound = true;
	}
	//Make sound if rock hit a tree
	else if (OtherActor->ActorHasTag("Tree") && !bTouchedGround)
	{
		bMadeSound = true;	
	}
	else if (OtherActor->ActorHasTag("Enemy") && !bTouchedGround)
	{
		Cast<AAIMushroom>(OtherActor)->Stun(2.f);
	}
	
	//Gets all enemies in a radius of 'Radius'. Made following http://orfeasel.com/tracing-multiple-objects/
	if (bMadeSound)
	{
		float Height = 200.f;
		float Radius = 500.f;

		TArray<FHitResult> ActorsHit;
		FVector StartLoc = GetActorLocation();
		FVector EndLoc = GetActorLocation();
		EndLoc.Z += Height;

		ECollisionChannel CollideWith = ECollisionChannel::ECC_Pawn;
		FCollisionShape CollisionShape;
		CollisionShape.ShapeType = ECollisionShape::Sphere;
		CollisionShape.SetSphere(Radius);
		FCollisionObjectQueryParams CollisionParam(ECollisionChannel::ECC_Pawn);

		bool bHitEnemy = GetWorld()->SweepMultiByObjectType(ActorsHit, StartLoc, EndLoc, FQuat::FQuat(), CollisionParam, CollisionShape);

		//Of something was hit, check if it was an enemy and call the 'HeardSound' function if it was
		if (bHitEnemy)
		{
			for (auto Enemy : ActorsHit)
			{
				if (Enemy.GetActor()->ActorHasTag("Enemy"))
				{
					Cast<AAIMushroom>(Enemy.GetActor())->HeardSound(this);
				}				
			}
		}
	}
}

