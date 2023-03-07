// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnManager.h"

#include "EnemyCharacter.h"

// Sets default values
ASpawnManager::ASpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("SPAWNMANAGER BeginPlay"));
	spawnTimer = SpawnDelay;
	
}

// Called every frame
void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	spawnTimer -= DeltaTime;
	if (spawnTimer <= 0)
	{
		spawnTimer = SpawnDelay;
		SpawnEnemy();
	}

}

void ASpawnManager::SpawnEnemy()
{
	spawnRandomLoc = FMath::RandRange(lowerSpawn, upperSpawn);
	AEnemyCharacter *NewEnemy = GetWorld()->SpawnActor<AEnemyCharacter>(EnemyClass, FVector(0, spawnRandomLoc, -272), FRotator(0, 0, 0));
	
}

