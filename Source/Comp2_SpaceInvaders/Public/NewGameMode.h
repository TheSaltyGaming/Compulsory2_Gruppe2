// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NewGameMode.generated.h"

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
class COMP2_SPACEINVADERS_API ANewGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:

	ANewGameMode();
	
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;
	
	EGameState GetGameState() const;

	void SetCurrentGameState(EGameState NewState);

	float timer;

	
private:
	EGameState CurrentState;
	
};
