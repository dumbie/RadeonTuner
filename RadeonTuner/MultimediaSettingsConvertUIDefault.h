#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::MultimediaSettings_Convert_ToUI_Default(MultimediaSettings multimediaSettings)
	{
		try
		{
			//Upscaling
			if (multimediaSettings.VideoUpscaling.Default.has_value())
			{
				toggleswitch_Video_Upscaling().IsOn(multimediaSettings.VideoUpscaling.Default.value());
				slider_Video_Sharpening().IsEnabled(multimediaSettings.VideoUpscaling.Default.value());
			}

			//Sharpening
			if (multimediaSettings.VideoSharpening.Default.has_value())
			{
				slider_Video_Sharpening().Value(multimediaSettings.VideoSharpening.Default.value());
			}

			//Brightness
			if (multimediaSettings.VideoBrightness.Default.has_value())
			{
				slider_Video_Brightness().Value(multimediaSettings.VideoBrightness.Default.value());
			}

			//Return result
			AVDebugWriteLine(L"Multimedia settings applied to interface.");
			return true;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine(L"Failed applying multimedia settings to interface.");
			return false;
		}
	}
}