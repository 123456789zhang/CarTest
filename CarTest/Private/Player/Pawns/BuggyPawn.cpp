// Fill out your copyright notice in the Description page of Project Settings.

#include "BuggyPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/AudioComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Sound/SoundCue.h"
#include "Components/InputComponent.h"
#include "VehiclePlayerController.h"
#include "WheeledVehicleMovementComponent.h"

ABuggyPawn::ABuggyPawn()
{
	/** 摄像机的设置
	 *	我们想要在汽车的位置和相机之间保持一个恒定的距离。
	 *	要保持滚动和节距不变
	 *	要稍微插一点偏航
	 *	我们想让汽车在屏幕空间的宽度和高度几乎保持不变(例如，如果你在汽车周围画一个盒子，它的中心将是接近恒定的，它的尺寸只会在急转弯或下降时变化
	 */

	//创建一个spring arm组件
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetOffset = FVector(0.0f, 0.0f, 400.0f);
	SpringArm->SetRelativeRotation(FRotator(0.0f));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 675.0f;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraRotationLagSpeed = 7.f;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;

	//创建摄像机的组件
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
	Camera->FieldOfView = 90.0f;

	EngineAC = CreateDefaultSubobject<UAudioComponent>(TEXT("EngineAudio"));
	EngineAC->SetupAttachment(GetMesh());

	//刹车音频组件 
	SkidAC = CreateDefaultSubobject<UAudioComponent>(TEXT("SkidAudio"));
	SkidAC->bAutoActivate = false; //我们不想马上开始打滑
	SkidAC->SetupAttachment(GetMesh());

	//函数的初始化
	SkidThresholdVelocity = 30;
	SkidFadeoutTime = 0.1f;
	LongSlipSkidThreshold = 0.3f;
	LateralSlipSkidThreshold = 0.3f;
	SkidDurationRequiredForStopSound = 1.5f;

	SpringCompressionLandingThreshold = 250000.f;
	bTiresTouchingGround = false;

	ImpactEffectNormalForceThreshold = 100000.f;
}

void ABuggyPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (EngineAC)
	{
		EngineAC->SetSound(EngineSound);
		EngineAC->Play();
	}

	if (SkidAC)
	{
		SkidAC->SetSound(SkidSound);
		SkidAC->Stop();
	}
}

void ABuggyPawn::SetupPlayerInputComponent(UInputComponent * InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("MoveForward", this, &ABuggyPawn::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ABuggyPawn::MoveRight);
}

void ABuggyPawn::MoveForward(float Val)
{
	AVehiclePlayerController* MyPC = Cast<AVehiclePlayerController>(GetController());
	UWheeledVehicleMovementComponent* VehicleMovementComp = GetVehicleMovementComponent();
	if (VehicleMovementComp == nullptr || (MyPC && MyPC->IsHandbrakeForced()))
	{
		return;
	}

	VehicleMovementComp->SetThrottleInput(Val);
}

void ABuggyPawn::MoveRight(float Val)
{
	AVehiclePlayerController* MyPC = Cast<AVehiclePlayerController>(GetController());
	UWheeledVehicleMovementComponent* VehicleMovementComp = GetVehicleMovementComponent();
	if (VehicleMovementComp == nullptr || (MyPC && MyPC->IsHandbrakeForced()))
	{
		return;
	}

	VehicleMovementComp->SetSteeringInput(Val);
}
