// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "SpaceShipPawn.h"
#include "Components/BoxComponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Can I just not do this and insead set the collider in the editor? Would be wayy nicer if I could.
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = Collider;
	Collider->InitBoxExtent(FVector(10,10,10));
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlap);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	//Mesh->SetRelativeScale3D(FVector(1,1,1));
	Mesh->SetRelativeLocation(FVector(0,0,20));

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation() + GetActorForwardVector() * MoveSpeed * DeltaTime;

	SetActorLocation(NewLocation);

	if (GetActorLocation().X > XKillPosiion)
	{
		DestroyEnemy();
	}

}

void AEnemy::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// if (OtherActor->IsA<ASpaceShipPawn>)
	// {
	// 	//This code could just be redundand tbh. DestroyEnemy could be called in the bullet class or some shit
	// 	//Cast<ASpaceShipPawn>(OtherActor)
	// }
}

void AEnemy::DestroyEnemy()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	this->Destroy();
}

