// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ModuleInterface.h"

/**
 * ģ�����Ϊ����Ϸ�ļ��ؽ���
 */
class IVehicleGameLoadingScreenModule : public IModuleInterface
{
public:
	/** ������Ϸ���ؽ���(������) */
	virtual void StartInGameLoadingScreen() = 0;
};
