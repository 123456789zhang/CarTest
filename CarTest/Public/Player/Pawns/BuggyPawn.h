﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehicle.h"
#include "BuggyPawn.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UAudioComponent;
class USoundCue;
/**
 * 
 */
UCLASS()
class CARTEST_API ABuggyPawn : public AWheeledVehicle
{
	GENERATED_BODY()

public:

	ABuggyPawn();

	//开始Actor的方法覆盖
	virtual void PostInitializeComponents() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	//结束Actor的方法覆盖

	//开始Pawn的方法覆盖
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	//结束Pawn的方法覆盖

	/** 杀掉玩家.[服务端/仅授权] */
	virtual void Die();

	/** 如果该玩家在当前状态下死亡，则返回True */
	virtual bool CanDie() const;

	/** 在死亡事件[服务端/客户端] */
	virtual void OnDeath();

protected:

	/* 车的方向移动 */
	virtual void MoveForward(float Val);
	void MoveRight(float Val);

	virtual void OnHandbrakePressed();
	virtual void OnHandbrakeReleased();

	/** 播放爆炸粒子和音频 */
	void PlayDestructionFX();

public:

	/** 判断玩家是否处于死亡状态 */
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = Health,ReplicatedUsing = OnRep_Dying)
	uint32 bIsDying : 1;

	/** 在客户端复制死亡 */
	UFUNCTION()
	void OnRep_Dying();

protected:

	/* 在着陆时播放声音所需的弹簧压缩量 */
	UPROPERTY(Category = Effects, EditDefaultsOnly)
		float SpringCompressionLandingThreshold;

	/* 轮胎是否正在接触地面 */
	bool bTiresTouchingGround;

	/* 如果速度低于这个速度，就不能产生打滑效果 */
	UPROPERTY(Category = Effects, EditDefaultsOnly)
		float SkidThresholdVelocity;

	/* 打滑渐变时间 */
	UPROPERTY(Category = Effects, EditDefaultsOnly)
		float SkidFadeoutTime;

	/* 如果轮胎纵向滑移绝对值大于此值，则会产生打滑效果。 */
	UPROPERTY(Category = Effects, EditDefaultsOnly, meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"))
		float LongSlipSkidThreshold;

	/* 如果轮胎横向滑移的绝对值大于此值，则会产生打滑效果。 */
	UPROPERTY(Category = Effects, EditDefaultsOnly, meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0"))
		float LateralSlipSkidThreshold;

	/* 如果skidding小于此值，则不会播放SkidSoundStop */
	UPROPERTY(Category = Effects, EditDefaultsOnly)
		float SkidDurationRequiredForStopSound;

	/* 必须施加在底盘上的最小法向力，以产生撞击效果 */
	UPROPERTY(EditAnywhere, Category = Effects)
		float ImpactEffectNormalForceThreshold;

	/** 角色爆炸特效 */
	UPROPERTY(Category = Effects,EditDefaultsOnly)
	UParticleSystem* DeathFX;

	/** 角色爆炸音乐 */
	UPROPERTY(Category = Effects, EditDefaultsOnly)
	USoundCue* DeathSound;

protected:

	/* 刹车的循环音乐 */
	UPROPERTY(Category = Effects, EditDefaultsOnly)
		USoundCue* SkidSound;

	/* enigne音乐 */
	UPROPERTY(Category = Effects, EditDefaultsOnly)
		USoundCue* EngineSound;

private:

	/* 弹簧臂，将抵消相机 */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* SpringArm;

	/* 相机组件，这将是我们的观点 */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* Camera;

	/* engine声音的音频组件 */
	UPROPERTY(Category = Effects, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UAudioComponent* EngineAC;

	/* 刹车声音的音频组件 */
	UPROPERTY()
		UAudioComponent* SkidAC;

public:

	class USpringArmComponent* GetSpringArm() const { return SpringArm; }

	class UCameraComponent* GetCamera() const { return Camera; }

	class UAudioComponent* GetEngineAC() const { return EngineAC; }
	
};
