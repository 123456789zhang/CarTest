// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "VehicleGameState.generated.h"

/**
 * 
 */
UCLASS()
class CARTEST_API AVehicleGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	AVehicleGameState();

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category = Game)
		bool IsRaceActive() const;

	UFUNCTION(BlueprintCallable,Category = Game)
		float GetTotalTime();
public:

	/** 定时器暂停吗? */
	UPROPERTY(Transient, Replicated)
		bool bIsRaceActive;

	/** 总比赛时间 */
	UPROPERTY(Transient,Replicated)
		float TotalTime;
	
};
