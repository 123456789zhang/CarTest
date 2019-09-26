// Fill out your copyright notice in the Description page of Project Settings.

#include "VehicleGameState.h"
#include "CarTest.h"

AVehicleGameState::AVehicleGameState()
{
	TotalTime = 0;
	bIsRaceActive = false;
}

void AVehicleGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AVehicleGameState,bIsRaceActive);
	DOREPLIFETIME(AVehicleGameState, TotalTime);
}

bool AVehicleGameState::IsRaceActive() const
{
	return bIsRaceActive;
}

float AVehicleGameState::GetTotalTime()
{
	return TotalTime;
}
