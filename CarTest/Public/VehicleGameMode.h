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

	virtual void Tick(float DeltaSeconds) override;

	/** 检查游戏是否是活跃的 */
	bool IsRaceActive() const;

protected:

	/** 比赛开始时间戳 */
	float RaceStartTime;

	/** 比赛结束时间戳 */
	float RaceFinishTime;

	/** 玩家锁定是否激活? */
	bool bLockingActive;
	
};
