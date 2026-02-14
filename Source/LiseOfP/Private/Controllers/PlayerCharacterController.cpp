// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/PlayerCharacterController.h"
#include "LOP_FunctionLibrary.h"

APlayerCharacterController::APlayerCharacterController()
{
	PlayerTeamID = static_cast<uint8>(EGameTeam::Player);
}

FGenericTeamId APlayerCharacterController::GetGenericTeamId() const
{
	return PlayerTeamID;
}