// Fill out your copyright notice in the Description page of Project Settings.

#include "VH_BuggyPawn.h"
#include "Engine/SkeletalMesh.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "WheeledVehicleMovementComponent.h"
#include "WheeledVehicleMovementComponent4W.h"
#include "VHBuggyWheelFront.h"
#include "Components/AudioComponent.h"

AVH_BuggyPawn::AVH_BuggyPawn()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> StaticCarMesh(TEXT("/Game/Vehicles/Mesh/SK_Buggy_Vehicle"));

	if (StaticCarMesh.Object != NULL)
	{
		GetMesh()->SetSkeletalMesh(StaticCarMesh.Object);
	}

	GetMesh()->SetCollisionProfileName(TEXT("Vehicle"));

	GetSpringArm()->TargetArmLength = 875.0f;
	GetSpringArm()->TargetOffset = FVector(0.0f, 0.0f, 375.0f);

	GetSpringArm()->ProbeSize = 40.0f;

	GetCamera()->FieldOfView = 110.0f;
	GetCamera()->SetConstraintAspectRatio(false);

	TireRolling = CreateDefaultSubobject<UAudioComponent>(TEXT("TireRolling"));
	TireRolling->bAutoActivate = false;
	TireRolling->SetupAttachment(GetMesh());

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetRelativeLocation(FVector(60.0f, 0.0f, 190.0f));
	Box->SetBoxExtent(FVector(25.0f));
	Box->BodyInstance.bEnableGravity = false;
	Box->BodyInstance.SetMassOverride(0.001f);
	Box->SetCollisionProfileName(FName(TEXT("Vehicle")));
	Box->SetupAttachment(RootComponent);

	auto VehicleMovement4W = Cast<UWheeledVehicleMovementComponent4W>(GetVehicleMovementComponent());

	if (VehicleMovement4W)
	{
		VehicleMovement4W->EngineSetup.TorqueCurve.EditorCurveData.Keys = TArray<FRichCurveKey>();
		VehicleMovement4W->EngineSetup.TorqueCurve.EditorCurveData.Keys.AddUninitialized(3);

		FRichCurveKey::StaticStruct()->InitializeStruct(VehicleMovement4W->EngineSetup.TorqueCurve.EditorCurveData.Keys.GetData(), 3);

		auto& KeyOne = VehicleMovement4W->EngineSetup.TorqueCurve.EditorCurveData.Keys[0];
		KeyOne.Value = 840.0f;
		KeyOne.Time = 50.823479f;

		auto& KeyTwo = VehicleMovement4W->EngineSetup.TorqueCurve.EditorCurveData.Keys[1];
		KeyTwo.Value = 1500.0f;
		KeyTwo.Time = 1890.0f;

		auto& KeyThree = VehicleMovement4W->EngineSetup.TorqueCurve.EditorCurveData.Keys[2];
		KeyThree.Value = 840.0f;
		KeyThree.Time = 5746.0f;
	
		VehicleMovement4W->EngineSetup.MaxRPM = 10000.0;
		VehicleMovement4W->DifferentialSetup.FrontRearSplit = 0.75f;
		VehicleMovement4W->TransmissionSetup.GearSwitchTime = 0.25f;

		VehicleMovement4W->SteeringCurve.EditorCurveData.Keys = TArray<FRichCurveKey>();
		VehicleMovement4W->SteeringCurve.EditorCurveData.Keys.AddUninitialized(4);
		FRichCurveKey::StaticStruct()->InitializeStruct(VehicleMovement4W->SteeringCurve.EditorCurveData.Keys.GetData(), 4);

		auto& SteeringKeyOne = VehicleMovement4W->SteeringCurve.EditorCurveData.Keys[0];
		SteeringKeyOne.Time = 0.0f;
		SteeringKeyOne.Value = 1.0f;

		auto& SteeringKeyTwo = VehicleMovement4W->SteeringCurve.EditorCurveData.Keys[1];
		SteeringKeyTwo.Time = 68.770935f;
		SteeringKeyTwo.Value = 0.726755;

		auto& SteeringKeyThree = VehicleMovement4W->SteeringCurve.EditorCurveData.Keys[2];
		SteeringKeyThree.Time = 109.683395f;
		SteeringKeyThree.Value = 0.490028f;

		auto& SteeringKeyFour = VehicleMovement4W->SteeringCurve.EditorCurveData.Keys[3];
		SteeringKeyFour.Time = 150.454041f;
		SteeringKeyFour.Value = 0.25081f;

		VehicleMovement4W->bDeprecatedSpringOffsetMode = true;
		VehicleMovement4W->Mass = 2500.0f;

		VehicleMovement4W->WheelSetups = TArray<FWheelSetup>();
		VehicleMovement4W->WheelSetups.AddUninitialized(4);
		FWheelSetup::StaticStruct()->InitializeStruct(VehicleMovement4W->WheelSetups.GetData(), 4);

		auto& WheelOne = VehicleMovement4W->WheelSetups[0];
		WheelOne.BoneName = FName(TEXT("F_L_wheelJNT"));
		WheelOne.WheelClass = UVHBuggyWheelFront::StaticClass();
		WheelOne.AdditionalOffset = FVector(0.0f, 45.0f, 0.0f);

		auto& WheelTwo = VehicleMovement4W->WheelSetups[1];
		WheelTwo.BoneName = FName(TEXT("F_R_wheelJNT"));
		WheelTwo.WheelClass = UVHBuggyWheelFront::StaticClass();
		WheelTwo.AdditionalOffset = FVector(0.0f, -45.0f, 0.0f);

		auto& WheelThree = VehicleMovement4W->WheelSetups[2];
		WheelThree.BoneName = FName(TEXT("B_L_wheelJNT"));
		WheelThree.WheelClass = UVHBuggyWheelFront::StaticClass();
		WheelThree.AdditionalOffset = FVector(0.0f, 45.0f, 0.0f);

		auto& WheelFour = VehicleMovement4W->WheelSetups[3];
		WheelFour.BoneName = FName(TEXT("B_R_wheelJNT"));
		WheelFour.WheelClass = UVHBuggyWheelFront::StaticClass();
		WheelFour.AdditionalOffset = FVector(0.0f, -45.0f, 0.0f);

		VehicleMovement4W->DragCoefficient = 0.0f;
	}


}
