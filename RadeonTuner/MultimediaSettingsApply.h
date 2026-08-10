#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::AdlMultimediaSettingsApply(int gpuAdapterIndex, MultimediaSettings targetSettings, AdlSettingGet settingGet)
	{
		try
		{
			//Get all multimedia setting values
			int adlFeatureCount = 0;
			auto adlFeatureValues = AVFin<ADLFeatureValues*>(AVFinMethod::FreeMarshal);
			adl_Res0 = _ADL2_MMD_FeatureValues_Get(adl_Context, gpuAdapterIndex, &adlFeatureValues.Get(), &adlFeatureCount);

			//Load all multimedia setting values
			for (int index = 0; index < adlFeatureCount; index++)
			{
				try
				{
					//Get feature name
					std::string featureName = std::string(adlFeatureValues.Get()[index].Name.FeatureName);

					//Video Upscaling
					if (targetSettings.VideoUpscaling.Get(settingGet).has_value())
					{
						//Get value
						auto newValue = targetSettings.VideoUpscaling.Get(settingGet).value();

						//Set setting
						if (featureName == "VideoUpScale")
						{
							adlFeatureValues.Get()[index].bCurrent = newValue;
						}
					}

					//Video Sharpening
					if (targetSettings.VideoSharpening.Get(settingGet).has_value())
					{
						//Get value
						auto newValue = targetSettings.VideoSharpening.Get(settingGet).value();

						//Set setting
						if (featureName == "Sharpness")
						{
							adlFeatureValues.Get()[index].fCurrent = newValue;
						}
					}

					//Video Brightness
					if (targetSettings.VideoBrightness.Get(settingGet).has_value())
					{
						//Get value
						auto newValue = targetSettings.VideoBrightness.Get(settingGet).value();

						//Set setting
						if (featureName == "Brightness")
						{
							adlFeatureValues.Get()[index].fCurrent = newValue;
						}
					}
				}
				catch (...) {}
			}

			//Set all multimedia setting values
			adl_Res0 = _ADL2_MMD_FeatureValues_Set(adl_Context, gpuAdapterIndex, adlFeatureValues.Get(), adlFeatureCount, 0);

			//Return result
			return adl_Res0 == ADL_OK;
		}
		catch (...)
		{
			//Return result
			return false;
		}
	}
}