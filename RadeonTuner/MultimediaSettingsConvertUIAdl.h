#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::MultimediaSettings_Convert_ToUI_Adl(MultimediaSettings multimediaSettings, AdlSettingGet settingType)
	{
		try
		{
			//Video Upscaling
			if (multimediaSettings.VideoUpscaling.Support && multimediaSettings.VideoUpscaling.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = multimediaSettings.VideoUpscaling.Get(settingType, true).value();

				//Set setting value
				toggleswitch_Video_Upscaling().IsOn(valueInt);

				//Set hint value
				std::wstring valueHint = valueInt ? L"Enabled" : L"Disabled";
				textblock_Video_Upscaling_Value().Text(valueHint);

				//Enable or disable interface
				toggleswitch_Video_Upscaling().IsEnabled(true);
				slider_Video_Sharpening().IsEnabled(valueInt);
			}
			else
			{
				//Set hint value
				textblock_Video_Upscaling_Value().Text(L"");

				//Enable or disable interface
				toggleswitch_Video_Upscaling().IsEnabled(false);
			}

			//Video Sharpening
			if (multimediaSettings.VideoSharpening.Support && multimediaSettings.VideoSharpening.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = multimediaSettings.VideoSharpening.Get(settingType, true).value();

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
			if (multimediaSettings.VideoBrightness.Support && multimediaSettings.VideoBrightness.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = multimediaSettings.VideoBrightness.Get(settingType, true).value();

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

				//Enable or disable interface
				slider_Video_Brightness().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_Video_Brightness_Value().Text(L"");

				//Enable or disable interface
				slider_Video_Brightness().IsEnabled(false);
			}

			//Top buttons
			//button_AppSelect_Multimedia().IsEnabled(true);
			button_Multimedia_Apply().IsEnabled(true);
			button_Multimedia_Reset().IsEnabled(true);

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