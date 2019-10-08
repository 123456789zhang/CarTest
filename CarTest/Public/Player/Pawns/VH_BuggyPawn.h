// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/Pawns/BuggyPawn.h"
#include "VH_BuggyPawn.generated.h"

class UBoxComponent;
/**
 * 
 */
UCLASS()
class CARTEST_API AVH_BuggyPawn : public ABuggyPawn
{
	GENERATED_BODY()

public:

	AVH_BuggyPawn();

protected:

	UPROPERTY(Category = Effects, EditDefaultsOnly)
		USoundCue* TireSound;

private:

	UPROPERTY(Category = Default, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* Box;

	UPROPERTY(Category = Default, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UAudioComponent* TireRolling;
	
};
