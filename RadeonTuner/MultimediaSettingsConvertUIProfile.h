#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::MultimediaSettings_Convert_ToUI_Profile(MultimediaSettings multimediaSettings, AdlSettingGet settingType)
	{
		try
		{
			//Upscaling
			if (multimediaSettings.VideoUpscaling.Get(settingType).has_value())
			{
				//Get setting
				int valueInt = multimediaSettings.VideoUpscaling.Get(settingType).value();

				//Set setting value
				toggleswitch_Video_Upscaling().IsOn(valueInt);

				//Enable or disable interface
				slider_Video_Sharpening().IsEnabled(valueInt);
			}

			//Sharpening
			if (multimediaSettings.VideoSharpening.Get(settingType).has_value())
			{
				//Set setting value
				slider_Video_Sharpening().Value(multimediaSettings.VideoSharpening.Get(settingType).value());
			}

			//Brightness
			if (multimediaSettings.VideoBrightness.Get(settingType).has_value())
			{
				//Set setting value
				slider_Video_Brightness().Value(multimediaSettings.VideoBrightness.Get(settingType).value());
			}

			//Return result
			AVDebugWriteLine(L"Multimedia settings applied to interface (Profile)");
			return true;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine(L"Failed applying multimedia settings to interface (Profile)");
			return false;
		}
	}
}