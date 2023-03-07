// Copyright Epic Games, Inc. All Rights Reserved.


#include "Comp2_SpaceInvadersGameModeBase.h"

AComp2_SpaceInvadersGameModeBase::AComp2_SpaceInvadersGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AComp2_SpaceInvadersGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SetCurrentGameState(EGameState::Running);
}

void AComp2_SpaceInvadersGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	timer = timer += DeltaSeconds;

	
}

EGameState AComp2_SpaceInvadersGameModeBase::GetGameState() const
{
	return CurrentState;
}

void AComp2_SpaceInvadersGameModeBase::SetCurrentGameState(EGameState NewState)
{
	CurrentState = NewState;
}
