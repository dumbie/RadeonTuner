#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	std::optional<MultimediaSettings> MainPage::MultimediaSettings_Generate_FromADL(int gpuAdapterIndex)
	{
		try
		{
			//Fix find way to check if setting is supported and disable interface. (ADL2_MMD_Features_Caps)
			//Fix add SteadyVideo FluidMotion Color Brightness support

			MultimediaSettings multimediaSettings{};

			//Set settings
			int adlFeatureCount = 0;
			ADLFeatureValues* adlFeatureValues{};
			adl_Res0 = _ADL2_MMD_FeatureValues_Get(adl_Context, gpuAdapterIndex, &adlFeatureValues, &adlFeatureCount);
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
						multimediaSettings.VideoUpscaling.Current = adlFeatureValues[index].bCurrent;
						multimediaSettings.VideoUpscaling.Default = 0;
						multimediaSettings.VideoUpscaling.Support = true;
					}
					else if (featureName == "Sharpness")
					{
						multimediaSettings.VideoSharpening.Current = adlFeatureValues[index].fCurrent;
						multimediaSettings.VideoSharpening.Default = 50;
						multimediaSettings.VideoSharpening.Support = true;
						multimediaSettings.VideoSharpening.Minimum = 1;
						multimediaSettings.VideoSharpening.Maximum = 100;
						multimediaSettings.VideoSharpening.Step = 1;
					}

					////Debug features
					//AVDebugWriteLine(featureName.c_str());
					//AVDebugWriteLine(adlFeatureValues[index].bCurrent);
					//AVDebugWriteLine(adlFeatureValues[index].fCurrent);
					//AVDebugWriteLine(adlFeatureValues[index].iCurrent);
				}
				catch (...) {}
			}

			//Return result
			return multimediaSettings;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("Failed to generate multimedia settings from ADL.");
			return std::nullopt;
		}
	}
}