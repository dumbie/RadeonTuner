#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::button_Multimedia_Reset_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Reset Multimedia settings
			bool resetResult = AdlxValuesResetMultimedia();

			//Check result
			if (resetResult)
			{
				//Show notification
				ShowNotification(L"Multimedia settings reset");
				AVDebugWriteLine(L"Multimedia settings reset");
			}
			else
			{
				//Show notification
				ShowNotification(L"Multimedia settings not reset");
				AVDebugWriteLine(L"Multimedia settings not reset");
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_Video_Upscaling_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			auto newSender = sender.as<ToggleSwitch>();
			bool newValue = newSender.IsOn();
			bool newFailed = true;

			//Get all multimedia setting values
			int adlFeatureCount = 0;
			auto adlFeatureValues = AVFin<ADLFeatureValues*>(AVFinMethod::FreeMarshal);
			adl_Res0 = _ADL2_MMD_FeatureValues_Get(adl_Context, adl_Gpu_AdapterIndex, &adlFeatureValues.Get(), &adlFeatureCount);

			//Load all multimedia setting values
			for (int index = 0; index < adlFeatureCount; index++)
			{
				try
				{
					//Get feature name
					std::string featureName = std::string(adlFeatureValues.Get()[index].Name.FeatureName);

					//Check feature name
					if (featureName == "VideoUpScale")
					{
						adlFeatureValues.Get()[index].bCurrent = newValue;
						break;
					}
				}
				catch (...) {}
			}

			//Set all multimedia setting values
			adl_Res0 = _ADL2_MMD_FeatureValues_Set(adl_Context, adl_Gpu_AdapterIndex, adlFeatureValues.Get(), adlFeatureCount, 0);

			//Set result
			newFailed = adl_Res0 != ADL_OK;

			//Show result
			if (newFailed)
			{
				disable_saving = true;
				newSender.IsOn(!newValue);
				disable_saving = false;
				if (newValue)
				{
					ShowNotification(L"Failed enabling Video Upscale");
					AVDebugWriteLine(L"Failed enabling Video Upscale");
				}
				else
				{
					ShowNotification(L"Failed disabling Video Upscale");
					AVDebugWriteLine(L"Failed disabling Video Upscale");
				}
			}
			else
			{
				if (newValue)
				{
					slider_Video_Sharpening().IsEnabled(true);
					ShowNotification(L"Video Upscale enabled");
					AVDebugWriteLine(L"Video Upscale enabled");
				}
				else
				{
					slider_Video_Sharpening().IsEnabled(false);
					ShowNotification(L"Video Upscale disabled");
					AVDebugWriteLine(L"Video Upscale disabled");
				}
			}
		}
		catch (...) {}
	}

	void MainPage::slider_Video_Sharpening_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			int newValue = (int)e.NewValue();
			bool newFailed = true;

			//Get all multimedia setting values
			int adlFeatureCount = 0;
			auto adlFeatureValues = AVFin<ADLFeatureValues*>(AVFinMethod::FreeMarshal);
			adl_Res0 = _ADL2_MMD_FeatureValues_Get(adl_Context, adl_Gpu_AdapterIndex, &adlFeatureValues.Get(), &adlFeatureCount);

			//Load all multimedia setting values
			for (int index = 0; index < adlFeatureCount; index++)
			{
				try
				{
					//Get feature name
					std::string featureName = std::string(adlFeatureValues.Get()[index].Name.FeatureName);

					//Check feature name
					if (featureName == "Sharpness")
					{
						adlFeatureValues.Get()[index].fCurrent = newValue;
						break;
					}
				}
				catch (...) {}
			}

			//Set all multimedia setting values
			adl_Res0 = _ADL2_MMD_FeatureValues_Set(adl_Context, adl_Gpu_AdapterIndex, adlFeatureValues.Get(), adlFeatureCount, 0);

			//Set result
			newFailed = adl_Res0 != ADL_OK;

			//Show result
			if (newFailed)
			{
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				textbox_VideoUpscale_Sharpening().Foreground(colorInvalid);
				ShowNotification(L"Failed setting Video sharpening");
				AVDebugWriteLine(L"Failed setting Video sharpening");
			}
			else
			{
				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				textbox_VideoUpscale_Sharpening().Foreground(colorValid);
				ShowNotification(L"Video sharpening set to " + number_to_wstring(newValue));
				AVDebugWriteLine(L"Video sharpening set to " << newValue);
			}
		}
		catch (...) {}
	}
}