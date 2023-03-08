// Fill out your copyright notice in the Description page of Project Settings.


#include "NewGameMode.h"

#include "Kismet/GameplayStatics.h"

ANewGameMode::ANewGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ANewGameMode::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Red, FString::Printf(TEXT("Timer: /90")));
	SetCurrentGameState(EGameState::Running);
}

void ANewGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	timer = timer += DeltaSeconds;
	GEngine->AddOnScreenDebugMessage(2, 1.1f, FColor::Red, FString::Printf(TEXT("Timer: %f /90"), timer));

	if (timer >= 90)
	{
		UGameplayStatics::SetGamePaused(GetWorld(),true);
		GEngine->AddOnScreenDebugMessage(2, 333.1f, FColor::Green, FString::Printf(TEXT("CONGRATULATIONS. YOU WIN")));
		SetCurrentGameState(EGameState::GameOver);
	}
}

EGameState ANewGameMode::GetGameState() const
{
	return CurrentState;
}

void ANewGameMode::SetCurrentGameState(EGameState NewState)
{
	CurrentState = NewState;
}
