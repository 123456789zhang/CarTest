// Fill out your copyright notice in the Description page of Project Settings.

#include "VehiclePlayerController.h"
#include "CarTest.h"

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
