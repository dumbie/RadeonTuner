#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::MultimediaSettings_Convert_ToUI_Current(MultimediaSettings multimediaSettings)
	{
		try
		{
			//Upscaling
			if (multimediaSettings.VideoUpscaling.Current.has_value())
			{
				toggleswitch_Video_Upscaling().IsOn(multimediaSettings.VideoUpscaling.Current.value());
				slider_Video_Sharpening().IsEnabled(multimediaSettings.VideoUpscaling.Current.value());
			}

			//Sharpening
			if (multimediaSettings.VideoSharpening.Current.has_value())
			{
				slider_Video_Sharpening().Value(multimediaSettings.VideoSharpening.Current.value());
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