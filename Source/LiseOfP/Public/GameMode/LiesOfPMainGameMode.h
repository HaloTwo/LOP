// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMode/LiesOfPGameMode.h"
#include "LiesOfPMainGameMode.generated.h"

UENUM(BlueprintType)
enum class EGameModeState : uint8
{
	InProgress,
	StateClear,
	PlayerDied
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameModeStateChangedDelegate, EGameModeState, CurrentState);

/**
 * 
 */
UCLASS()
class LISEOFP_API ALiesOfPMainGameMode : public ALiesOfPGameMode
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	void SetCurrentGameModeState(EGameModeState InState);

	UPROPERTY()
	EGameModeState CurrentGameModeState;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnGameModeStateChangedDelegate OnGameModeStateChanged;

};
