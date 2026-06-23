#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesLoadMultimedia()
	{
		try
		{
			//Fix find way to check if setting is supported and disable interface. (ADL2_MMD_Features_Caps)
			//Fix add SteadyVideo FluidMotion Color Brightness support

			//Set interface limits
			slider_Video_Sharpening().Minimum(1);
			slider_Video_Sharpening().Maximum(100);
			slider_Video_Sharpening().StepFrequency(1);
			slider_Video_Sharpening().SmallChange(1);

			//Get all multimedia setting values
			int adlFeatureCount = 0;
			ADLFeatureValues* adlFeatureValues{};
			adl_Res0 = _ADL2_MMD_FeatureValues_Get(adl_Context, adl_Gpu_AdapterIndex, &adlFeatureValues, &adlFeatureCount);
			AVDebugWriteLine(L"Multimedia values count: " << adlFeatureCount);

			//Load all multimedia setting values
			for (int index = 0; index < adlFeatureCount; index++)
			{
				try
				{
					//Get feature name
					std::string featureName = std::string(adlFeatureValues[index].Name.FeatureName);

					//Check feature name
					if (featureName == "VideoUpScale")
					{
						toggleswitch_Video_Sharpening().IsOn(adlFeatureValues[index].bCurrent);
						slider_Video_Sharpening().IsEnabled(adlFeatureValues[index].bCurrent);
					}
					else if (featureName == "Sharpness")
					{
						slider_Video_Sharpening().Value(adlFeatureValues[index].fCurrent);
					}

					////Debug features
					//AVDebugWriteLine(featureName.c_str());
					//AVDebugWriteLine(adlFeatureValues[index].bCurrent);
					//AVDebugWriteLine(adlFeatureValues[index].fCurrent);
					//AVDebugWriteLine(adlFeatureValues[index].iCurrent);
				}
				catch (...) {}
			}

			//Set result
			AVDebugWriteLine("ADLX loaded multimedia values.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADLX failed loading multimedia values.");
		}
	}
}