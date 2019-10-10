// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/Controllers/VehiclePlayerController.h"
#include "VHPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CARTEST_API AVHPlayerController : public AVehiclePlayerController
{
	GENERATED_BODY()

public:

	AVHPlayerController();

	/**  */
	void VHOverlapUpdate(AActor* Actor);
	
};
