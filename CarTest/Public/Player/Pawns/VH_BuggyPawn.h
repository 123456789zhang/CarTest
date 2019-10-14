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

	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void EngineSoundStart(int32 EntryPoint);

	UFUNCTION()
	void EnableCarInput(int32 EntryPoint);

protected:

	virtual void MoveForward(float Val) override;

	virtual void OnHandbrakePressed() override;
	virtual void OnHandbrakeReleased() override;

	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	void ChangeBrakesSettings(float val);

	void DoOnce(int8 val);

public:

	UPROPERTY(Category = Default, BlueprintReadWrite)
		UMaterialInstanceDynamic* DMI;

	/** 刹车键是否按住 */
	UPROPERTY(Category = Default, BlueprintReadWrite)
		bool bHandBrakePressed;

	/**  */
	UPROPERTY(Category = Default, BlueprintReadWrite)
		bool bStuck;

private:

	UPROPERTY(Category = Default, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* Box;

	UPROPERTY(Category = Default, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UAudioComponent* TireRolling;

	UPROPERTY()
	bool bVariable;
	
};
