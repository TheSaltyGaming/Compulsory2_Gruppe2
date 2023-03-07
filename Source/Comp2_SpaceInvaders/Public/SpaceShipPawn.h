// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpaceShipPawn.generated.h"

class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class USoundBase;
class ABullet;
class UBoxComponent;
struct FInputActionValue;

UCLASS()
class COMP2_SPACEINVADERS_API ASpaceShipPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpaceShipPawn();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	/* Components */
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "SpaceShip")
	UStaticMeshComponent* ShipMesh;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "SpaceShip")
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "SpaceShip")
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spaceship")
	UBoxComponent* Collider {nullptr};
	
	/** Blueprints: we set these in our blueprint */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	TSubclassOf<ABullet> BP_Bullet;

	/* Sound effects */
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "SpaceShip")
	USoundBase* ShootingSound;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "SpaceShip")
	USoundBase* ReloadingSound;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "SpaceShip")
	USoundBase* NoAmmoSound;

	/* Public Variables */

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "SpaceShip")
	int Ammo;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "SpaceShip")
	int MaxAmmo;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "SpaceShip")
	float MovementSpeed;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "SpaceShip")
	int Health;

	/* Public Functions */
	void Damage();

	
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	
private:

	/* Private Variables */

	float XInput;
	float YInput;
	float Yaw;
	float Pitch;

	/* Private Functions */

	void VerticalMovement(const FInputActionValue& input);
	void HorizontalMovement(const FInputActionValue& input);
	void LookAround(const FInputActionValue& input);
	void LookUp(const FInputActionValue& input);

	void Shoot(const FInputActionValue& input);
	void Reload(const FInputActionValue& input);

public:



	//Sets up bindings to the IMC for enhanced inputs

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
	class UInputMappingContext* IMC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
	class UInputAction* IA_Forwardbackward;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
	class UInputAction* IA_LeftRight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
	class UInputAction* IA_LookAround;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
	class UInputAction* IA_LookUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
	class UInputAction* IA_Shoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
	class UInputAction* IA_Reload;

};
