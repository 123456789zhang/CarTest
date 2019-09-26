// Fill out your copyright notice in the Description page of Project Settings.

#include "VehicleGameLoadingScreen.h"
#include "MoviePlayer.h"
#include "Modules/ModuleManager.h"
#include "SlateBasics.h"
#include "SlateExtras.h"

struct FVehicleGameLoadingScreenBrush : public FSlateDynamicImageBrush, public FGCObject
{
	FVehicleGameLoadingScreenBrush(const FName InTextureName, const FVector2D& InImageSize)
		: FSlateDynamicImageBrush(InTextureName, InImageSize)
	{
		SetResourceObject(LoadObject<UObject>(nullptr, *InTextureName.ToString()));
	}

	virtual void AddReferencedObjects(FReferenceCollector& Collector)
	{
		FSlateBrush::AddReferencedObjects(Collector);
	}

};


class SVehicleLoadingScreen : public SCompoundWidget
{
public:

	SLATE_BEGIN_ARGS(SVehicleLoadingScreen){}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs)
	{
		static const FName LoadingScreenName(TEXT("/Game/UI/Menu/LoadingScreen.LoadingScreen"));
		LoadingScreenBrush = MakeShareable(new FVehicleGameLoadingScreenBrush(LoadingScreenName,FVector2D(1920,1080)));
	
		ChildSlot
			[
				SNew(SOverlay)
				+SOverlay::Slot()
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Fill)
				[
					SNew(SImage)
					.Image(LoadingScreenBrush.Get())
				]
				+SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				[
					SNew(SVerticalBox)
					+SVerticalBox::Slot()
					.VAlign(VAlign_Bottom)
					.HAlign(HAlign_Right)
					.Padding(FMargin(10.0f))
					[
						SNew(SThrobber)
						.Visibility(this,&SVehicleLoadingScreen::GetLoadIndicatorVisibility)
					]
				]
			];
	}

private:

	EVisibility GetLoadIndicatorVisibility() const
	{
		return GetMoviePlayer()->IsLoadingFinished() ? EVisibility::Collapsed : EVisibility::Visible;
	}

	/** ¼ÓÔØÆÁÄ»µÄÍ¼Æ¬»­Ë¢ */
	TSharedPtr< FVehicleGameLoadingScreenBrush> LoadingScreenBrush;
};


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
		LoadingScreen.WidgetLoadingScreen = SNew(SVehicleLoadingScreen);
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
	}
};

IMPLEMENT_GAME_MODULE(FVehicleGameLoadingScreenModule, CarTestLoadingScreen);