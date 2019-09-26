// Fill out your copyright notice in the Description page of Project Settings.

#include "VehicleGameMode.h"
#include "Engine/Engine.h"
#include "VehicleGameState.h"
#include "Engine/GameViewportClient.h"


AVehicleGameMode::AVehicleGameMode()
{
	RaceStartTime = 0.0f;
	RaceFinishTime = 0.0f;
	bLockingActive = false;

	GameStateClass = AVehicleGameState::StaticClass();
	if ((GEngine != nullptr) && (GEngine->GameViewport != nullptr))
	{
		GEngine->GameViewport->SetSuppressTransitionMessage(true);
	}

	PrimaryActorTick.bCanEverTick = true;
}

void AVehicleGameMode::Tick(float DeltaSeconds)
{
	AVehicleGameState* VehicleGameState = GetGameState<AVehicleGameState>();
	if (VehicleGameState != nullptr)
	{
		const float CurrentTime = IsRaceActive() ? GetWorld()->GetTimeSeconds() : RaceFinishTime;
		VehicleGameState->TotalTime = CurrentTime - RaceStartTime;
	}

}

bool AVehicleGameMode::IsRaceActive() const
{
	AVehicleGameState* VehicleGameState = GetGameState<AVehicleGameState>();
	bool bIsActive = false;
	if (VehicleGameState != nullptr)
	{
		bIsActive = VehicleGameState->bIsRaceActive;
	}
	return bIsActive;
}
