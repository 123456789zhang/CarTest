// Fill out your copyright notice in the Description page of Project Settings.

#include "VehicleGameLoadingScreen.h"
#include "MoviePlayer.h"
#include "Modules/ModuleManager.h"

class FVehicleGameLoadingScreenModule : public IVehicleGameLoadingScreenModule
{
public:

	virtual void StartupModule() override
	{
		//
		if (IsMoviePlayerEnabled())
		{
			CreateScreen();
		}
	}

	virtual bool IsGameModule() const override
	{
		return true;
	}

	virtual void StartInGameLoadingScreen() override
	{
		CreateScreen();

		GetMoviePlayer()->PlayMovie();
	}

	virtual void CreateScreen()
	{
		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;
		LoadingScreen.WidgetLoadingScreen = NULL;
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}
};

IMPLEMENT_GAME_MODULE(FVehicleGameLoadingScreenModule, CarTestLoadingScreen);