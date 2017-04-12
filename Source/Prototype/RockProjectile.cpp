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

	static ConstructorHelpers::FObjectFinder<UStaticMesh> RockAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (RockAsset.Succeeded())
	{
		VisibleComponent->SetStaticMesh(RockAsset.Object);
		VisibleComponent->SetWorldScale3D(FVector(0.2f, 0.2f, 0.2f));
		VisibleComponent->SetSimulatePhysics(false);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MatRock(TEXT("Material'/Game/Material/M_Stone.M_Stone'"));
	if (MatRock.Succeeded())
	{
		VisibleComponent->SetMaterial(0, MatRock.Object);
	}

	RootComponent = CollisionComponent;
	VisibleComponent->SetupAttachment(RootComponent);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);

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

void ARockProjectile::ThrowInDirection(const FVector & ThrowDirection)
{
	ProjectileComponent->Velocity = ThrowDirection * ProjectileComponent->InitialSpeed;
}

void ARockProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	bool bMadeSound = false;

	//Test if GetClass is needed. Can use IsA? Are all actors children of landscape?
	if (OtherActor->GetClass()->IsChildOf(ALandscape::StaticClass()) && !bTouchedGround)
	{
		bTouchedGround = true;
		bMadeSound = true;
	}
	else if (OtherActor->ActorHasTag("Tree") && !bTouchedGround)
	{
		bMadeSound = true;	
	}
	
	//Gets all enemies in a radius of 'Radius'. Made following http://orfeasel.com/tracing-multiple-objects/
	if (bMadeSound)
	{
		float Height = 200.f;
		float Radius = 500.f;

		UE_LOG(LogTemp, Warning, TEXT("BOOM"));

		TArray<FHitResult> ActorsHit;
		FVector StartLoc = GetActorLocation();
		FVector EndLoc = GetActorLocation();
		EndLoc.Z += Height;

		ECollisionChannel CollideWith = ECollisionChannel::ECC_Pawn;
		FCollisionShape CollisionShape;
		CollisionShape.ShapeType = ECollisionShape::Sphere;
		CollisionShape.SetSphere(Radius);
		FCollisionObjectQueryParams Rawr(ECollisionChannel::ECC_Pawn);

		bool bHitEnemy = GetWorld()->SweepMultiByObjectType(ActorsHit, StartLoc, EndLoc, FQuat::FQuat(), Rawr, CollisionShape);

		if (bHitEnemy)
		{
			for (auto Enemy : ActorsHit)
			{
				if (Enemy.GetActor()->ActorHasTag("Enemy"))
				{
					UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *Enemy.Actor->GetName());
					Cast<AAIMushroom>(Enemy.GetActor())->HeardSound(this);
				}				
			}
		}
	}
}

