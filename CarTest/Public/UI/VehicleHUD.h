// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "VehicleHUD.generated.h"

/**
 * 
 */
UCLASS()
class CARTEST_API AVehicleHUD : public AHUD
{
	GENERATED_BODY()

public:
	
	AVehicleHUD();

	/** 显示/隐藏在游戏菜单 */
	void ToggleGameMenu();
};
