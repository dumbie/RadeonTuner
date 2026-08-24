#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	std::optional<MultimediaSettings> MainPage::MultimediaSettings_Generate_FromADL(int gpuAdapterIndex, std::wstring application, bool loadDefault)
	{
		try
		{
			//Fix add SteadyVideo FluidMotion Color support

			AVDebugWriteLine(L"Generating multimedia settings for: " << gpuAdapterIndex << L" / " << application);
			MultimediaSettings multimediaSettings{};

			//Device identifier
			multimediaSettings.DeviceId = AdlxGetGpuIdentifier(gpuAdapterIndex);

			//Device application
			multimediaSettings.Application = application;

			//Get setting values
			int adlFeatureValuesCount = 0;
			auto adlFeatureValues = AVFin<ADLFeatureValues*>(AVFinMethod::FreeMarshal);
			adl_Res0 = _ADL2_MMD_FeatureValues_Get(adl_Context, gpuAdapterIndex, &adlFeatureValues.Get(), &adlFeatureValuesCount);
			AVDebugWriteLine(L"Multimedia values count: " << adlFeatureValuesCount);

			//Get setting capabilities
			int adlFeatureCapsCount = 0;
			auto adlFeatureCaps = AVFin<ADLFeatureCaps*>(AVFinMethod::FreeMarshal);
			adl_Res0 = _ADL2_MMD_Features_Caps(adl_Context, gpuAdapterIndex, &adlFeatureCaps.Get(), &adlFeatureCapsCount);
			AVDebugWriteLine(L"Multimedia capabilities count: " << adlFeatureCapsCount);

			//Load all multimedia setting values
			for (int index = 0; index < adlFeatureValuesCount; index++)
			{
				try
				{
					//Get feature name
					std::string featureName = std::string(adlFeatureValues.Get()[index].Name.FeatureName);

					//Check feature name
					if (featureName == "VideoUpScale")
					{
						//Check setting support
						bool featureSupported = (adlFeatureCaps.Get()[index].iFeatureProperties & ADL_FEATURE_PROPERTIES_SUPPORTED) == ADL_FEATURE_PROPERTIES_SUPPORTED;

						multimediaSettings.VideoUpscaling.Default = 0;
						multimediaSettings.VideoUpscaling.Current = adlFeatureValues.Get()[index].bCurrent;
						multimediaSettings.VideoUpscaling.Support = featureSupported;
					}
					else if (featureName == "Sharpness")
					{
						//Check setting support
						bool featureSupported = (adlFeatureCaps.Get()[index].iFeatureProperties & ADL_FEATURE_PROPERTIES_SUPPORTED) == ADL_FEATURE_PROPERTIES_SUPPORTED;

						multimediaSettings.VideoSharpening.Default = 50;
						multimediaSettings.VideoSharpening.Current = adlFeatureValues.Get()[index].fCurrent;
						multimediaSettings.VideoSharpening.Support = featureSupported;
						multimediaSettings.VideoSharpening.Minimum = 1;
						multimediaSettings.VideoSharpening.Maximum = 100;
						multimediaSettings.VideoSharpening.Step = 1;
					}
					else if (featureName == "Brightness")
					{
						//Check setting support
						bool featureSupported = (adlFeatureCaps.Get()[index].iFeatureProperties & ADL_FEATURE_PROPERTIES_SUPPORTED) == ADL_FEATURE_PROPERTIES_SUPPORTED;

						multimediaSettings.VideoBrightness.Default = 0;
						multimediaSettings.VideoBrightness.Current = adlFeatureValues.Get()[index].fCurrent;
						multimediaSettings.VideoBrightness.Support = featureSupported;
						multimediaSettings.VideoBrightness.Minimum = -100;
						multimediaSettings.VideoBrightness.Maximum = 100;
						multimediaSettings.VideoBrightness.Step = 1;
					}

					//Set current value to default value
					if (loadDefault)
					{
						multimediaSettings.SetCurrentToDefault();
					}

					////Debug features
					//AVDebugWriteLine(featureName.c_str());
					//AVDebugWriteLine(((adlFeatureCaps.Get()[index].iFeatureProperties & ADL_FEATURE_PROPERTIES_SUPPORTED) == ADL_FEATURE_PROPERTIES_SUPPORTED));
					//AVDebugWriteLine(adlFeatureValues.Get()[index].bCurrent);
					//AVDebugWriteLine(adlFeatureValues.Get()[index].fCurrent);
					//AVDebugWriteLine(adlFeatureValues.Get()[index].iCurrent);
					//AVDebugWriteLine(adlFeatureValues.Get()[index].EnumStates);
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