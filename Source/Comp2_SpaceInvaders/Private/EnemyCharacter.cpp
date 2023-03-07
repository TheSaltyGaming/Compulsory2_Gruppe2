// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"

#include "SpaceShipPawn.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	// Mesh->SetupAttachment(RootComponent);
	// //Mesh->SetRelativeScale3D(FVector(1,1,1));
	// Mesh->SetRelativeLocation(FVector(0,0,20));
	

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::OnOverlap);
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyCharacter::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap"));
	if (OtherActor->IsA<ASpaceShipPawn>())
	{
		DestroyEnemy();
	}
}

void AEnemyCharacter::DestroyEnemy()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	this->Destroy();
}

