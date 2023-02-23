// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Comp2_SpaceInvadersGameModeBase.generated.h"

UENUM(BlueprintType)
enum class EGameState:uint8
{
	Running,
	GameOver,
	None
};

/**
 * 
 */
UCLASS()
class COMP2_SPACEINVADERS_API AComp2_SpaceInvadersGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	AComp2_SpaceInvadersGameModeBase();
	
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;
	
	EGameState GetGameState() const;

	void SetCurrentGameState(EGameState NewState);

	
private:
	EGameState CurrentState;
};
