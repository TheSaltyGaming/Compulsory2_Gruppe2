// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnManager.generated.h"

UCLASS()
class COMP2_SPACEINVADERS_API ASpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	void SpawnEnemy(); //TODO: Add Enemy here

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	float lowerSpawn = 0; //Lower bound for random spawn location (can be changed in blueprint)
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Enemy")
	float upperSpawn = 800; //Upper bound for random spawn location (can be changed in blueprint)
	


private:
	UPROPERTY(EditAnywhere , Category = "Enemy")
	float spawnTimer = 2.0f; //Counts down to 0 before being set back to spawnDelay
	
	UPROPERTY(EditAnywhere, Category = "Enemy")
	TSubclassOf<class AEnemyCharacter> EnemyClass;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	float SpawnDelay = 3.0f; //spawn delay in seconds

	UPROPERTY()
	float spawnRandomLoc = 0; //Random location for enemy to spawn
	

};
