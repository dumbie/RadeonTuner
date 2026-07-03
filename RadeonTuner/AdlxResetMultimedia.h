#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::AdlxValuesResetMultimedia()
	{
		try
		{
			//Get current and default settings
			MultimediaSettings multimediaSettings = MultimediaSettings_Generate_FromADL(adl_Gpu_AdapterIndex).value();

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

			//Return result
			return true;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("Failed resetting multimedia settings.");
			return false;
		}
	}
}