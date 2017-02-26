//Class for the player character

#pragma once

#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class PROTOTYPE_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);
	void Raycast();

	FORCEINLINE bool GetLanternStatus() const { return Lantern; }

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* PlayerMesh;
	
private:
	FVector CurrentVelocity;
	UCameraComponent* PlayerCamera;
	bool Lantern;
};
