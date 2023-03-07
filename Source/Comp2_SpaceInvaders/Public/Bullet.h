// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

class USphereComponent;

UCLASS()
class COMP2_SPACEINVADERS_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* Collision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* StaticMesh;

	/** Public Variables */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet Variables")
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet Variables")
	float LifeSpan;


	/** Public Functions */

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
					UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
					bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void BulletDestroy();


private:
	/** Private Variables */

	float TimeLived;

};
