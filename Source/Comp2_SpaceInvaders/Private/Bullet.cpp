// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

#include "EnemyCharacter.h"
#include "Components/SphereComponent.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	SetRootComponent(Collision);
	Collision->InitSphereRadius(13.f);
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlap);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());
	StaticMesh->SetRelativeScale3D(FVector(0.15f, 0.15f, 0.15f));

	MovementSpeed = 2000.f;
	TimeLived = 0.f;
	LifeSpan = 10.f;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	NewLocation += GetActorForwardVector() * MovementSpeed * DeltaTime;
	SetActorLocation(NewLocation);


	TimeLived += DeltaTime;
	if (TimeLived > LifeSpan)
	{
		BulletDestroy();
	}
}

void ABullet::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Bullet hit something"));
		if (OtherActor->IsA<AEnemyCharacter>())
    	{
			BulletDestroy();
    	}
}

void ABullet::BulletDestroy()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	this->Destroy();
}

