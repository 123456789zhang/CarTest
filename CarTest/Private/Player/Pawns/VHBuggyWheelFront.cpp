// Fill out your copyright notice in the Description page of Project Settings.

#include "VHBuggyWheelFront.h"
#include "VHBuggyTireConfig.h"

UVHBuggyWheelFront::UVHBuggyWheelFront(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ShapeRadius = 52.0f;
	ShapeWidth = 23.0f;
	bAffectedByHandbrake = false;

	SteerAngle = 50.0f;
	TireConfig = NewObject<UVHBuggyTireConfig>();
	LatStiffMaxLoad = 5.0f;
	LatStiffValue = 1000.0f;
	LongStiffValue = 1000.0f;

	SuspensionMaxRaise = 20.0f;
	SuspensionMaxDrop = 40.0f;
	SuspensionNaturalFrequency = 10.0f;
	SuspensionDampingRatio = 1.1f;

	MaxBrakeTorque = 4000.0f;
	MaxHandBrakeTorque = 6000.0f;
}