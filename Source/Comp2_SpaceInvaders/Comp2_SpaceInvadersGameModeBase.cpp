// Copyright Epic Games, Inc. All Rights Reserved.


#include "Comp2_SpaceInvadersGameModeBase.h"

AComp2_SpaceInvadersGameModeBase::AComp2_SpaceInvadersGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AComp2_SpaceInvadersGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Red, FString::Printf(TEXT("Timer: /90")));
	//SetCurrentGameState(EGameState::Running);
}

void AComp2_SpaceInvadersGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	timer = timer += DeltaSeconds;
	GEngine->AddOnScreenDebugMessage(2, 1.1f, FColor::Red, FString::Printf(TEXT("Timer: %f /90"), timer));

	
}

// EGameState AComp2_SpaceInvadersGameModeBase::GetGameState() const
// {
// 	return CurrentState;
// }
//
// void AComp2_SpaceInvadersGameModeBase::SetCurrentGameState(EGameState NewState)
// {
// 	CurrentState = NewState;
// }
