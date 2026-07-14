#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::MultimediaSettings_Convert_ToUI_ADL(MultimediaSettings multimediaSettings)
	{
		try
		{
			//Video Upscaling
			if (multimediaSettings.VideoUpscaling.Support.has_value() && multimediaSettings.VideoUpscaling.Support.value())
			{
				//Set setting
				if (multimediaSettings.VideoUpscaling.Current.has_value())
				{
					toggleswitch_Video_Upscaling().IsOn(multimediaSettings.VideoUpscaling.Current.value());
					slider_Video_Sharpening().IsEnabled(multimediaSettings.VideoUpscaling.Current.value());
				}
				else if (multimediaSettings.VideoUpscaling.Default.has_value())
				{
					toggleswitch_Video_Upscaling().IsOn(multimediaSettings.VideoUpscaling.Default.value());
					slider_Video_Sharpening().IsEnabled(multimediaSettings.VideoUpscaling.Default.value());
				}

				//Enable or disable interface
				toggleswitch_Video_Upscaling().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				toggleswitch_Video_Upscaling().IsEnabled(false);
				slider_Video_Sharpening().IsEnabled(false);
			}

			//Video Sharpening
			if (multimediaSettings.VideoSharpening.Support.has_value() && multimediaSettings.VideoSharpening.Support.value())
			{
				//Set setting
				if (multimediaSettings.VideoSharpening.Current.has_value())
				{
					slider_Video_Sharpening().Value(multimediaSettings.VideoSharpening.Current.value());
				}
				else if (multimediaSettings.VideoSharpening.Default.has_value())
				{
					slider_Video_Sharpening().Value(multimediaSettings.VideoSharpening.Default.value());
				}

				//Set interface
				if (multimediaSettings.VideoSharpening.Minimum.has_value())
				{
					slider_Video_Sharpening().Minimum(multimediaSettings.VideoSharpening.Minimum.value());
					slider_Video_Sharpening().Maximum(multimediaSettings.VideoSharpening.Maximum.value());
					slider_Video_Sharpening().StepFrequency(multimediaSettings.VideoSharpening.Step.value());
					slider_Video_Sharpening().SmallChange(multimediaSettings.VideoSharpening.Step.value());
				}
			}
			else
			{
				//Enable or disable interface
				slider_Video_Sharpening().IsEnabled(false);
			}

			//Video Brightness
			if (multimediaSettings.VideoBrightness.Support.has_value() && multimediaSettings.VideoBrightness.Support.value())
			{
				//Set setting
				if (multimediaSettings.VideoBrightness.Current.has_value())
				{
					slider_Video_Brightness().Value(multimediaSettings.VideoBrightness.Current.value());
				}
				else if (multimediaSettings.VideoBrightness.Default.has_value())
				{
					slider_Video_Brightness().Value(multimediaSettings.VideoBrightness.Default.value());
				}

				//Set interface
				if (multimediaSettings.VideoBrightness.Minimum.has_value())
				{
					slider_Video_Brightness().Minimum(multimediaSettings.VideoBrightness.Minimum.value());
					slider_Video_Brightness().Maximum(multimediaSettings.VideoBrightness.Maximum.value());
					slider_Video_Brightness().StepFrequency(multimediaSettings.VideoBrightness.Step.value());
					slider_Video_Brightness().SmallChange(multimediaSettings.VideoBrightness.Step.value());
				}
			}
			else
			{
				//Enable or disable interface
				slider_Video_Brightness().IsEnabled(false);
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