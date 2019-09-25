// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class CarTestLoadingScreen: ModuleRules
{
	public CarTestLoadingScreen(ReadOnlyTargetRules Target) : base(Target)
	{

        PrivatePCHHeaderFile = "Pulbic/VehicleGameLoadingScreen.h";

        PCHUsage = PCHUsageMode.UseSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });

		PrivateDependencyModuleNames.AddRange(new string[] {  "InputCore" ,"MoviePlayer"});

	}
}
