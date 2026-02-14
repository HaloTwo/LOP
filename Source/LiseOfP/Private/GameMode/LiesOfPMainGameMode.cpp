// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/LiesOfPMainGameMode.h"


void ALiesOfPMainGameMode::BeginPlay()
{
	Super::BeginPlay();
}

void ALiesOfPMainGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALiesOfPMainGameMode::SetCurrentGameModeState(EGameModeState InState)
{
	CurrentGameModeState = InState;

	OnGameModeStateChanged.Broadcast(CurrentGameModeState);
}