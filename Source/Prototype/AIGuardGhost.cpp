// Fill out your copyright notice in the Description page of Project Settings.

#include "Prototype.h"
#include "AIGuardGhost.h"


// Sets default values
AAIGuardGhost::AAIGuardGhost()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAIGuardGhost::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAIGuardGhost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIGuardGhost::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

