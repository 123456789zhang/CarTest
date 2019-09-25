// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "VehicleGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CARTEST_API AVehicleGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AVehicleGameMode();

	virtual void BeginPlay() override;

	
};
