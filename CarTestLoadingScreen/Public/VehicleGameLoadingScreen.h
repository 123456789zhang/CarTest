// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ModuleInterface.h"

/**
 * 模块界面为本游戏的加载界面
 */
class IVehicleGameLoadingScreenModule : public IModuleInterface
{
public:
	/** 启动游戏加载界面(非启动) */
	virtual void StartInGameLoadingScreen() = 0;
};
