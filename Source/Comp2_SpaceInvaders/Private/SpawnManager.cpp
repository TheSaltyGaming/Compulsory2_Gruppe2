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
	timer += DeltaTime;
	if (spawnTimer <= 0)
	{
		spawnTimer = SpawnDelay;
		SpawnEnemy();
	}
	if (timer >= 7 && SpawnDelay > 0.4)
	{
		timer = 0;
		SpawnDelay -= 0.3;
		difficulty++;
	}

}

void ASpawnManager::SpawnEnemy()
{
	spawnRandomLoc = FMath::RandRange(lowerSpawn, upperSpawn);
	int randomNum = FMath::RandRange(0, 3);
	if (randomNum == 0)
	{
		AEnemyCharacter *NewEnemy = GetWorld()->SpawnActor<AEnemyCharacter>(EnemyClass, FVector(522, 1875+spawnRandomLoc, -142), FRotator(0, 0, 0));

	}
	if (randomNum == 1)
	{
		AEnemyCharacter *NewEnemy = GetWorld()->SpawnActor<AEnemyCharacter>(EnemyClass, FVector(1922, -1694+spawnRandomLoc, 141), FRotator(0, 0, 0));
	}
	if (randomNum == 2)
	{
		AEnemyCharacter *NewEnemy = GetWorld()->SpawnActor<AEnemyCharacter>(EnemyClass, FVector(-1937, -2424+spawnRandomLoc, 141), FRotator(0, 0, 0));
	}
	if (randomNum == 3)
	{
		AEnemyCharacter *NewEnemy = GetWorld()->SpawnActor<AEnemyCharacter>(EnemyClass, FVector(-1937, 2735+spawnRandomLoc, 141), FRotator(0, 0, 0));
	}
	
}

