// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "VehiclePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CARTEST_API AVehiclePlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AVehiclePlayerController();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	bool IsHandbrakeForced() const;

protected:

	/* ������ã���ɲ������ǿ�� */
	UPROPERTY(transient, replicated)
	bool bHandbrakeOverride;
	
};