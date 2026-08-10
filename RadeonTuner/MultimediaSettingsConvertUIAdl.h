#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::MultimediaSettings_Convert_ToUI_Adl(MultimediaSettings multimediaSettings)
	{
		try
		{
			//Video Upscaling
			if (multimediaSettings.VideoUpscaling.Support.has_value() && multimediaSettings.VideoUpscaling.Support.value())
			{
				//Get setting
				int valueInt = 0;
				if (multimediaSettings.VideoUpscaling.Current.has_value())
				{
					valueInt = multimediaSettings.VideoUpscaling.Current.value();
				}
				else if (multimediaSettings.VideoUpscaling.Default.has_value())
				{
					valueInt = multimediaSettings.VideoUpscaling.Default.value();
				}

				//Set setting value
				toggleswitch_Video_Upscaling().IsOn(valueInt);
				slider_Video_Sharpening().IsEnabled(valueInt);

				//Set hint value
				std::wstring valueHint = valueInt ? L"Enabled" : L"Disabled";
				textblock_Video_Upscaling_Value().Text(valueHint);

				//Enable or disable interface
				toggleswitch_Video_Upscaling().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_Video_Upscaling_Value().Text(L"");

				//Enable or disable interface
				toggleswitch_Video_Upscaling().IsEnabled(false);
				slider_Video_Sharpening().IsEnabled(false);
			}

			//Video Sharpening
			if (multimediaSettings.VideoSharpening.Support.has_value() && multimediaSettings.VideoSharpening.Support.value())
			{
				//Get setting
				int valueInt = 0;
				if (multimediaSettings.VideoSharpening.Current.has_value())
				{
					valueInt = multimediaSettings.VideoSharpening.Current.value();
				}
				else if (multimediaSettings.VideoSharpening.Default.has_value())
				{
					valueInt = multimediaSettings.VideoSharpening.Default.value();
				}

				//Set setting value
				slider_Video_Sharpening().Value(valueInt);

				//Set hint value
				std::wstring valueHint = number_to_wstring(valueInt) + L"%";
				textblock_Video_Sharpening_Value().Text(valueHint);

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
				//Set hint value
				textblock_Video_Sharpening_Value().Text(L"");

				//Enable or disable interface
				slider_Video_Sharpening().IsEnabled(false);
			}

			//Video Brightness
			if (multimediaSettings.VideoBrightness.Support.has_value() && multimediaSettings.VideoBrightness.Support.value())
			{
				//Get setting
				int valueInt = 0;
				if (multimediaSettings.VideoBrightness.Current.has_value())
				{
					valueInt = multimediaSettings.VideoBrightness.Current.value();
				}
				else if (multimediaSettings.VideoBrightness.Default.has_value())
				{
					valueInt = multimediaSettings.VideoBrightness.Default.value();
				}

				//Set setting value
				slider_Video_Brightness().Value(valueInt);

				//Set hint value
				std::wstring valueHint = number_to_wstring(valueInt) + L"%";
				textblock_Video_Brightness_Value().Text(valueHint);

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
				//Set hint value
				textblock_Video_Brightness_Value().Text(L"");

				//Enable or disable interface
				slider_Video_Brightness().IsEnabled(false);
			}

			//Return result
			AVDebugWriteLine(L"Multimedia settings applied to interface (ADL)");
			return true;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine(L"Failed applying multimedia settings to interface (ADL)");
			return false;
		}
	}
}