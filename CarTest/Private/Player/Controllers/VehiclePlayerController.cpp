// Fill out your copyright notice in the Description page of Project Settings.

#include "VehiclePlayerController.h"
#include "CarTest.h"
#include "VehicleHUD.h"
#include "VehicleGameState.h"
#include "Engine/World.h"
#include "BuggyPawn.h"

AVehiclePlayerController::AVehiclePlayerController()
{
	
}

void AVehiclePlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AVehiclePlayerController, bHandbrakeOverride);
}

bool AVehiclePlayerController::IsHandbrakeForced() const
{
	return bHandbrakeOverride;
}

void AVehiclePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//UIÊäÈë
	FInputActionBinding& ToggleInGameMenuBinding = InputComponent->BindAction("InGameMenu", IE_Pressed, this,&AVehiclePlayerController::OnToggleInGameMenu);

	InputComponent->BindAction("BackOnTrack",IE_Pressed ,this , &AVehiclePlayerController::Suicide);

	ToggleInGameMenuBinding.bExecuteWhenPaused = true;
}

void AVehiclePlayerController::OnToggleInGameMenu()
{
	AVehicleHUD* GameHUD = Cast<AVehicleHUD>(MyHUD);
	if (GameHUD)
	{
		GameHUD->ToggleGameMenu();
	}
}

void AVehiclePlayerController::Suicide()
{
	if (IsInState(NAME_Playing))
	{
		ServerSuicide();
	}
}

bool AVehiclePlayerController::ServerSuicide_Validate()
{
	return true;
}

void AVehiclePlayerController::ServerSuicide_Implementation()
{
	AVehicleGameState* GameState = GetWorld()->GetGameState<AVehicleGameState>();
	if (((GameState != nullptr) && (GameState->IsRaceActive())) || (GetNetMode() == NM_Standalone))
	{
		ABuggyPawn* MyPawn = Cast<ABuggyPawn>(GetPawn());
		if (MyPawn)
		{
			MyPawn->Die();
		}
	}
}