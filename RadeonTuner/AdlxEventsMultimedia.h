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

			//Get current and default settings
			MultimediaSettings multimediaSettings = MultimediaSettings_Generate_FromADL(adl_Gpu_AdapterIndex).value();

			//Convert settings to interface
			bool resetResult = MultimediaSettings_Convert_ToUI_Default(multimediaSettings);

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
					ShowNotification(L"Failed enabling Video Upscaling");
					AVDebugWriteLine(L"Failed enabling Video Upscaling");
				}
				else
				{
					ShowNotification(L"Failed disabling Video Upscaling");
					AVDebugWriteLine(L"Failed disabling Video Upscaling");
				}
			}
			else
			{
				if (newValue)
				{
					slider_Video_Sharpening().IsEnabled(true);
					ShowNotification(L"Video Upscaling enabled");
					AVDebugWriteLine(L"Video Upscaling enabled");
				}
				else
				{
					slider_Video_Sharpening().IsEnabled(false);
					ShowNotification(L"Video Upscaling disabled");
					AVDebugWriteLine(L"Video Upscaling disabled");
				}

				//Update current value
				multimediaSettingsCurrent.VideoUpscaling.Current = newValue;
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
				ShowNotification(L"Failed setting Video Sharpening");
				AVDebugWriteLine(L"Failed setting Video Sharpening");
			}
			else
			{
				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				textbox_VideoUpscale_Sharpening().Foreground(colorValid);
				ShowNotification(L"Video Sharpening set to " + number_to_wstring(newValue));
				AVDebugWriteLine(L"Video Sharpening set to " << newValue);

				//Update current value
				multimediaSettingsCurrent.VideoSharpening.Current = newValue;
			}
		}
		catch (...) {}
	}

	void MainPage::slider_Video_Brightness_ValueChanged(IInspectable const& sender, RangeBaseValueChangedEventArgs const& e)
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
					if (featureName == "Brightness")
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
				textbox_Video_Brightness().Foreground(colorInvalid);
				ShowNotification(L"Failed setting Video Brightness");
				AVDebugWriteLine(L"Failed setting Video Brightness");
			}
			else
			{
				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				textbox_Video_Brightness().Foreground(colorValid);
				ShowNotification(L"Video Brightness set to " + number_to_wstring(newValue));
				AVDebugWriteLine(L"Video Brightness set to " << newValue);

				//Update current value
				multimediaSettingsCurrent.VideoBrightness.Current = newValue;
			}
		}
		catch (...) {}
	}
}