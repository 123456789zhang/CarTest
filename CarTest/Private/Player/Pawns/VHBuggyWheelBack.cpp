// Fill out your copyright notice in the Description page of Project Settings.

#include "VHBuggyWheelBack.h"
#include "VHBuggyTireConfig.h"

UVHBuggyWheelBack::UVHBuggyWheelBack()
{
	ShapeRadius = 52.0f;
	ShapeWidth = 30.0f;
	bAffectedByHandbrake = true;

	SteerAngle = 0.0f;
	TireConfig = NewObject<UVHBuggyTireConfig>();
	LatStiffMaxLoad = 4.0f;
	LatStiffValue = 200.0f;
	LongStiffValue = 1000.0f;

	SuspensionMaxRaise = 20.0f;
	SuspensionMaxDrop = 40.0f;
	SuspensionNaturalFrequency = 10.0f;
	SuspensionDampingRatio = 1.1f;

	MaxBrakeTorque = 4000.0f;
	MaxHandBrakeTorque = 6000.0f;
}