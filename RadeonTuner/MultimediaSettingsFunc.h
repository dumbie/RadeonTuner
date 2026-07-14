#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::Adl_Multimedia_Set_Mode(int gpuAdapterIndex)
	{
		try
		{
			//Note: when multimedia mode / preset / video profile is not set to custom, brightness does not work.

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

					//Check feature name
					if (featureName == "Preset")
					{
						adlFeatureValues.Get()[index].EnumStates = 128; //Custom
						break;
					}
				}
				catch (...) {}
			}

			//Set all multimedia setting values
			adl_Res0 = _ADL2_MMD_FeatureValues_Set(adl_Context, gpuAdapterIndex, adlFeatureValues.Get(), adlFeatureCount, 0);

			//Return result
			AVDebugWriteLine("Set multimedia mode: " << adl_Res0);
			return adl_Res0 == ADL_OK;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("Failed to set multimedia mode (Exception)");
			return false;
		}
	}
}