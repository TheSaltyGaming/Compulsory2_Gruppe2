// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpaceShipPawn.generated.h"

class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class USoundBase;
class UInputMappingContext;

UCLASS()
class COMP2_SPACEINVADERS_API ASpaceShipPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpaceShipPawn();

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "SpaceShip")
	UStaticMeshComponent* ShipMesh;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="SpaceShip")
	USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="SpaceShip")
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="SpaceShip")
	USoundBase* ShootingSound;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="SpaceShip")
	USoundBase* ReloadingSound;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="SpaceShip")
	USoundBase* NoAmmoSound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
