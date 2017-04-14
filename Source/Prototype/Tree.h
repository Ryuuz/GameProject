//A tree

#pragma once

#include "GameFramework/Actor.h"
#include "Tree.generated.h"

UCLASS()
class PROTOTYPE_API ATree : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATree();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	private:
	UStaticMeshComponent* TreeMesh;	
};
