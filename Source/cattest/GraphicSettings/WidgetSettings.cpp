// Fill out your copyright notice in the Description page of Project Settings.
#include "WidgetSettings.h"
#include "frame_rate2.h"


namespace
{
	typedef int32(UGameUserSettings::* GetFunc)() const;
	typedef void(UGameUserSettings::* SetFunc)(int);
	struct FSelectionElement
	{
		USelectionBase* Widget;
		GetFunc GetFunc;
		SetFunc SetFunc;

	};

	constexpr EFrame_rate2 FramerateOption[] = {

		EFrame_rate2::FPS_30,
		EFrame_rate2::FPS_48,
		EFrame_rate2::FPS_60,
		EFrame_rate2::FPS_120,
		EFrame_rate2::FPS_Uncapped,


	};
	
}

void UWidgetSettings::NativeConstruct()
{
	GameUserSettings = UGameUserSettings::GetGameUserSettings();
	InitializeResolutionComboBox();
	InitializeVSync();
	InitializeFrameRate();

	const FSelectionElement SelectionElements[] = {
		{ShadingQualitySelection, &UGameUserSettings::GetShadingQuality, &UGameUserSettings::SetShadingQuality},
		{GlobalIlluminationSelection, &UGameUserSettings::GetGlobalIlluminationQuality, &UGameUserSettings::SetGlobalIlluminationQuality},
		{VisualEffectsQualitySelection, &UGameUserSettings::GetVisualEffectQuality, &UGameUserSettings::SetVisualEffectQuality},
		{ShadowQualitySelection, &UGameUserSettings::GetShadowQuality, &UGameUserSettings::SetShadowQuality},
		{PostProcessQualitySelection, &UGameUserSettings::GetPostProcessingQuality, &UGameUserSettings::SetPostProcessingQuality}	
	};

	for (const auto& [Widget, GetFunc, SetFunc]: SelectionElements)
	{
		 auto currentSelection = std::invoke(GetFunc, GameUserSettings);
		 Widget->SetCurrentSelection(currentSelection);
		 Widget->OnSelectionChange.BindLambda([this, SetFunc](int InSelection) 
			 {
				 std::invoke(SetFunc, GameUserSettings, InSelection);
				 GameUserSettings->ApplySettings(false);

			 });
		
	}


}

UWidget* UWidgetSettings::NativeGetDesiredFocusTarget() const
{
	return Super::NativeGetDesiredFocusTarget();


};

void UWidgetSettings::InitializeResolutionComboBox()
{
	Resolutions.Reset();

	UKismetSystemLibrary::GetSupportedFullscreenResolutions(Resolutions);

	ResolutionComboBox->ClearOptions();
	for (const auto& Resolution : Resolutions) {
		const auto ResolutionString = FString::Printf(TEXT("%dx%d"),Resolution.X,Resolution.Y);
		ResolutionComboBox->AddOption(ResolutionString);
	}
	//FIND CURRENT RESOLUTION
	const auto CurrentResolution = GameUserSettings->GetScreenResolution();
	const auto SelectedIndex = Resolutions.IndexOfByPredicate
	([&CurrentResolution](const FIntPoint& InResolution)
		{
			return InResolution == CurrentResolution;
		});

	check(SelectedIndex >= 0);
	ResolutionComboBox->SetSelectedIndex(SelectedIndex);

	//listen to changes

	ResolutionComboBox->OnSelectionChanged.Clear();
	ResolutionComboBox->OnSelectionChanged.AddDynamic(this, &UWidgetSettings::OnResolutionChanged);

}

void UWidgetSettings::InitializeVSync()
{
	VSyncCheckBox->SetIsChecked(GameUserSettings->IsVSyncEnabled());
	if (ResolutionComboBox->OnSelectionChanged.IsBound())
	{
		ResolutionComboBox->OnSelectionChanged.Clear();
	}
	VSyncCheckBox->OnCheckStateChanged.AddDynamic(this, &UWidgetSettings::OnVSyncChanged);
}



void UWidgetSettings::InitializeFrameRate()
{
	FramerateSelection->Clear();
	int FramerateOptionIndex = 0;

	

	const auto CurrentFramerate = GameUserSettings->GetFrameRateLimit();
	for (const auto& Framerate : FramerateOption) {
		FramerateSelection->AddOption({
			FText::FromString(FFramerateUtils2::EnumToString(Framerate))
			

		});

		if(CurrentFramerate == FFramerateUtils2::EnumToValue(Framerate))
		{
			FramerateSelection->SetCurrentSelection(FramerateOptionIndex);
		}
		FramerateOptionIndex++;


	}

	FramerateSelection->OnSelectionChange.BindLambda([this](const int InSelection)
	{
			GameUserSettings->SetFrameRateLimit(FFramerateUtils2::EnumToValue(FramerateOption[InSelection]));
	});
	
}

void UWidgetSettings::OnResolutionChanged(FString InSelectedItem, ESelectInfo::Type InSelectionType)
{
	const auto SelectedResolution = Resolutions[ResolutionComboBox->GetSelectedIndex()];
	GameUserSettings->SetScreenResolution(SelectedResolution);
	GameUserSettings->ApplySettings(false);
	
}

void UWidgetSettings::OnVSyncChanged(bool InIsCheck)
{
	GameUserSettings->SetVSyncEnabled(InIsCheck);
	GameUserSettings->ApplySettings(false);
}

