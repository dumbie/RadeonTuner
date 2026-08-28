#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::GraphicsSettings_Convert_ToUI_Adl(GraphicsSettings graphicsSettings)
	{
		try
		{
			//FSR Upscaling Override
			if (graphicsSettings.FsrOverride.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.FsrOverride.Current.has_value())
				{
					valueInt = graphicsSettings.FsrOverride.Current.value();
				}
				else if (graphicsSettings.FsrOverride.Default.has_value())
				{
					valueInt = graphicsSettings.FsrOverride.Default.value();
				}

				//Set setting value
				toggleswitch_FsrOverrideUpscaling().IsOn(valueInt);

				//Set hint value
				std::wstring valueHint = valueInt ? L"Enabled" : L"Disabled";
				textblock_FsrOverrideUpscaling_Value().Text(valueHint);

				//Enable or disable interface
				toggleswitch_FsrOverrideUpscaling().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_FsrOverrideUpscaling_Value().Text(L"");

				//Enable or disable interface
				toggleswitch_FsrOverrideUpscaling().IsEnabled(false);
			}

			//FSR Frame Generation Override
			if (graphicsSettings.MlfiOverride.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.MlfiOverride.Current.has_value())
				{
					valueInt = graphicsSettings.MlfiOverride.Current.value();
				}
				else if (graphicsSettings.MlfiOverride.Default.has_value())
				{
					valueInt = graphicsSettings.MlfiOverride.Default.value();
				}

				//Set setting value
				toggleswitch_FsrOverrideFrameGeneration().IsOn(valueInt);

				//Set hint value
				std::wstring valueHint = valueInt ? L"Enabled" : L"Disabled";
				textblock_FsrOverrideFrameGeneration_Value().Text(valueHint);

				//Enable or disable interface
				toggleswitch_FsrOverrideFrameGeneration().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_FsrOverrideFrameGeneration_Value().Text(L"");

				//Enable or disable interface
				toggleswitch_FsrOverrideFrameGeneration().IsEnabled(false);
			}

			//FSR Multi Frame Generation Override
			if (graphicsSettings.MfgOverride.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.MfgOverride.Current.has_value())
				{
					valueInt = graphicsSettings.MfgOverride.Current.value();
				}
				else if (graphicsSettings.MfgOverride.Default.has_value())
				{
					valueInt = graphicsSettings.MfgOverride.Default.value();
				}

				//Set setting value
				toggleswitch_FsrOverrideMultiFrameGeneration().IsOn(valueInt);

				//Set hint value
				std::wstring valueHint = valueInt ? L"Enabled" : L"Disabled";
				textblock_FsrOverrideMultiFrameGeneration_Value().Text(valueHint);

				//Enable or disable interface
				toggleswitch_FsrOverrideMultiFrameGeneration().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_FsrOverrideMultiFrameGeneration_Value().Text(L"");

				//Enable or disable interface
				toggleswitch_FsrOverrideMultiFrameGeneration().IsEnabled(false);
			}

			//FSR Ray Regeneration Denoiser Override
			if (graphicsSettings.MldOverride.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.MldOverride.Current.has_value())
				{
					valueInt = graphicsSettings.MldOverride.Current.value();
				}
				else if (graphicsSettings.MldOverride.Default.has_value())
				{
					valueInt = graphicsSettings.MldOverride.Default.value();
				}

				//Set setting value
				toggleswitch_FsrOverrideRayRegeneration().IsOn(valueInt);

				//Set hint value
				std::wstring valueHint = valueInt ? L"Enabled" : L"Disabled";
				textblock_FsrOverrideRayRegeneration_Value().Text(valueHint);

				//Enable or disable interface
				toggleswitch_FsrOverrideRayRegeneration().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_FsrOverrideRayRegeneration_Value().Text(L"");

				//Enable or disable interface
				toggleswitch_FsrOverrideRayRegeneration().IsEnabled(false);
			}

			//FSR Neural Radiance Caching Override
			if (graphicsSettings.NrcOverride.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.NrcOverride.Current.has_value())
				{
					valueInt = graphicsSettings.NrcOverride.Current.value();
				}
				else if (graphicsSettings.NrcOverride.Default.has_value())
				{
					valueInt = graphicsSettings.NrcOverride.Default.value();
				}

				//Set setting value
				toggleswitch_FsrOverrideNeuralRadianceCaching().IsOn(valueInt);

				//Set hint value
				std::wstring valueHint = valueInt ? L"Enabled" : L"Disabled";
				textblock_FsrOverrideNeuralRadianceCaching_Value().Text(valueHint);

				//Enable or disable interface
				toggleswitch_FsrOverrideNeuralRadianceCaching().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_FsrOverrideNeuralRadianceCaching_Value().Text(L"");

				//Enable or disable interface
				toggleswitch_FsrOverrideNeuralRadianceCaching().IsEnabled(false);
			}

			//FSR Multi Frame Generation Ratio
			if (graphicsSettings.MfgRatio.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.MfgRatio.Current.has_value())
				{
					valueInt = graphicsSettings.MfgRatio.Current.value();
				}
				else if (graphicsSettings.MfgRatio.Default.has_value())
				{
					valueInt = graphicsSettings.MfgRatio.Default.value();
				}

				//Set setting value
				combobox_FsrMultiFrameGenerationRatio().SelectedIndex(valueInt);

				//Set hint value
				std::wstring valueHint = ADL_FSR_MULTIFRAMEGEN_RATIO[valueInt];
				textblock_FsrMultiFrameGenerationRatio_Value().Text(valueHint);

				//Enable or disable interface
				combobox_FsrMultiFrameGenerationRatio().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_FsrMultiFrameGenerationRatio_Value().Text(L"");

				//Enable or disable interface
				combobox_FsrMultiFrameGenerationRatio().IsEnabled(false);
			}

			//FSR Override Library
			if (graphicsSettings.FsrOvrDLLPath.Support)
			{
				//Set setting
				if (graphicsSettings.FsrOvrDLLPath.Current.has_value())
				{
					textbox_FsrDllLoadPath().Text(graphicsSettings.FsrOvrDLLPath.Current.value());
				}
				else if (graphicsSettings.FsrOvrDLLPath.Default.has_value())
				{
					textbox_FsrDllLoadPath().Text(graphicsSettings.FsrOvrDLLPath.Default.value());
				}

				//Enable or disable interface
				button_FsrDllLoadPath_Default().IsEnabled(true);
				button_FsrDllLoadPath_Set().IsEnabled(true);
				textbox_FsrDllLoadPath().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				button_FsrDllLoadPath_Default().IsEnabled(false);
				button_FsrDllLoadPath_Set().IsEnabled(false);
				textbox_FsrDllLoadPath().IsEnabled(false);
			}

			//FSR Over-The-Air Updates
			if (graphicsSettings.FsrOtaIndex.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.FsrOtaIndex.Current.has_value())
				{
					valueInt = graphicsSettings.FsrOtaIndex.Current.value();
				}
				else if (graphicsSettings.FsrOtaIndex.Default.has_value())
				{
					valueInt = graphicsSettings.FsrOtaIndex.Default.value();
				}

				//Set setting value
				combobox_FsrOtaUpdates().SelectedIndex(valueInt);

				//Set hint value
				std::wstring valueHint = REGISTRY_FSR_OTA_CONTROL_STRING[valueInt];
				textblock_FsrOtaUpdates_Value().Text(valueHint);

				//Enable or disable interface
				combobox_FsrOtaUpdates().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_FsrOtaUpdates_Value().Text(L"");

				//Enable or disable interface
				combobox_FsrOtaUpdates().IsEnabled(false);
			}

			//FSR Show Information
			if (graphicsSettings.FsrShowInformation.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.FsrShowInformation.Current.has_value())
				{
					valueInt = graphicsSettings.FsrShowInformation.Current.value();
				}
				else if (graphicsSettings.FsrShowInformation.Default.has_value())
				{
					valueInt = graphicsSettings.FsrShowInformation.Default.value();
				}

				//Set setting value
				toggleswitch_FsrShowInformation().IsOn(valueInt);

				//Set hint value
				std::wstring valueHint = valueInt ? L"Enabled" : L"Disabled";
				textblock_FsrShowInformation_Value().Text(valueHint);

				//Enable or disable interface
				toggleswitch_FsrShowInformation().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_FsrShowInformation_Value().Text(L"");

				//Enable or disable interface
				toggleswitch_FsrShowInformation().IsEnabled(false);
			}

			//FSR Latency Reduction
			if (graphicsSettings.DeLagEnabled.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.DeLagEnabled.Current.has_value())
				{
					valueInt = graphicsSettings.DeLagEnabled.Current.value();
				}
				else if (graphicsSettings.DeLagEnabled.Default.has_value())
				{
					valueInt = graphicsSettings.DeLagEnabled.Default.value();
				}

				//Set setting value
				toggleswitch_FsrLatencyReduction().IsOn(valueInt);

				//Set hint value
				std::wstring valueHint = valueInt ? L"Enabled" : L"Disabled";
				textblock_FsrLatencyReduction_Value().Text(valueHint);

				//Enable or disable interface
				toggleswitch_FsrLatencyReduction().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_FsrLatencyReduction_Value().Text(L"");

				//Enable or disable interface
				toggleswitch_FsrLatencyReduction().IsEnabled(false);
			}

			//Radeon Fluid Motion Frames
			if (graphicsSettings.FrameGenEnabled.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.FrameGenEnabled.Current.has_value())
				{
					valueInt = graphicsSettings.FrameGenEnabled.Current.value();
				}
				else if (graphicsSettings.FrameGenEnabled.Default.has_value())
				{
					valueInt = graphicsSettings.FrameGenEnabled.Default.value();
				}

				//Set setting value
				toggleswitch_FrameGenEnabled().IsOn(valueInt);

				//Set hint value
				std::wstring valueHint = valueInt ? L"Enabled" : L"Disabled";
				textblock_FrameGenEnabled_Value().Text(valueHint);

				//Enable or disable interface
				toggleswitch_FrameGenEnabled().IsEnabled(true);
				combobox_FrameGenSearchMode().IsEnabled(valueInt);
				combobox_FrameGenPerfMode().IsEnabled(valueInt);
				combobox_FrameGenResponseMode().IsEnabled(valueInt);
				combobox_FrameGenAlgorithm().IsEnabled(valueInt);
			}
			else
			{
				//Set hint value
				textblock_FrameGenEnabled_Value().Text(L"");

				//Enable or disable interface
				toggleswitch_FrameGenEnabled().IsEnabled(false);
			}

			//Radeon Fluid Motion Frames - Search Mode
			if (graphicsSettings.FrameGenSearchMode.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.FrameGenSearchMode.Current.has_value())
				{
					valueInt = graphicsSettings.FrameGenSearchMode.Current.value();
				}
				else if (graphicsSettings.FrameGenSearchMode.Default.has_value())
				{
					valueInt = graphicsSettings.FrameGenSearchMode.Default.value();
				}

				//Set setting value
				combobox_FrameGenSearchMode().SelectedIndex(valueInt);

				//Set hint value
				std::wstring valueHint = REGISTRY_FRAMEGEN_SEARCH_MODE_STRING[valueInt];
				textblock_FrameGenSearchMode_Value().Text(valueHint);
			}
			else
			{
				//Set hint value
				textblock_FrameGenSearchMode_Value().Text(L"");

				//Enable or disable interface
				combobox_FrameGenSearchMode().IsEnabled(false);
			}

			//Radeon Fluid Motion Frames - Performance Mode
			if (graphicsSettings.FrameGenPerfMode.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.FrameGenPerfMode.Current.has_value())
				{
					valueInt = graphicsSettings.FrameGenPerfMode.Current.value();
				}
				else if (graphicsSettings.FrameGenPerfMode.Default.has_value())
				{
					valueInt = graphicsSettings.FrameGenPerfMode.Default.value();
				}

				//Set setting value
				combobox_FrameGenPerfMode().SelectedIndex(valueInt);

				//Set hint value
				std::wstring valueHint = REGISTRY_FRAMEGEN_PERFORMANCE_MODE_STRING[valueInt];
				textblock_FrameGenPerfMode_Value().Text(valueHint);
			}
			else
			{
				//Set hint value
				textblock_FrameGenPerfMode_Value().Text(L"");

				//Enable or disable interface
				combobox_FrameGenPerfMode().IsEnabled(false);
			}

			//Radeon Fluid Motion Frames - Response Mode
			if (graphicsSettings.FrameGenResponseMode.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.FrameGenResponseMode.Current.has_value())
				{
					valueInt = graphicsSettings.FrameGenResponseMode.Current.value();
				}
				else if (graphicsSettings.FrameGenResponseMode.Default.has_value())
				{
					valueInt = graphicsSettings.FrameGenResponseMode.Default.value();
				}

				//Set setting value
				combobox_FrameGenResponseMode().SelectedIndex(valueInt);

				//Set hint value
				std::wstring valueHint = REGISTRY_FRAMEGEN_RESPONSE_MODE_STRING[valueInt];
				textblock_FrameGenResponseMode_Value().Text(valueHint);
			}
			else
			{
				//Set hint value
				textblock_FrameGenResponseMode_Value().Text(L"");

				//Enable or disable interface
				combobox_FrameGenResponseMode().IsEnabled(false);
			}

			//Radeon Fluid Motion Frames - Algorithm
			if (graphicsSettings.FrameGenAlgorithm.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.FrameGenAlgorithm.Current.has_value())
				{
					valueInt = graphicsSettings.FrameGenAlgorithm.Current.value();
				}
				else if (graphicsSettings.FrameGenAlgorithm.Default.has_value())
				{
					valueInt = graphicsSettings.FrameGenAlgorithm.Default.value();
				}

				//Set setting value
				combobox_FrameGenAlgorithm().SelectedIndex(valueInt);

				//Set hint value
				std::wstring valueHint = REGISTRY_FRAMEGEN_ALGORITHM_MODE_STRING[valueInt];
				textblock_FrameGenAlgorithm_Value().Text(valueHint);
			}
			else
			{
				//Set hint value
				textblock_FrameGenAlgorithm_Value().Text(L"");

				//Enable or disable interface
				combobox_FrameGenAlgorithm().IsEnabled(false);
			}

			//Radeon Boost
			if (graphicsSettings.BoostMode.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.BoostMode.Current.has_value())
				{
					valueInt = graphicsSettings.BoostMode.Current.value();
				}
				else if (graphicsSettings.BoostMode.Default.has_value())
				{
					valueInt = graphicsSettings.BoostMode.Default.value();
				}

				//Set setting value
				combobox_RadeonBoost().SelectedIndex(valueInt);

				//Set hint value
				std::wstring valueHint = ADL_BOOST2_ALGORITHM[valueInt];
				textblock_RadeonBoost_Value().Text(valueHint);

				//Enable or disable interface
				combobox_RadeonBoost().IsEnabled(true);
				slider_RadeonBoost_MinResolution().IsEnabled(valueInt);
			}
			else
			{
				//Set hint value
				textblock_RadeonBoost_Value().Text(L"");

				//Enable or disable interface
				combobox_RadeonBoost().IsEnabled(false);
			}

			//Radeon Boost - Minimum Resolution
			if (graphicsSettings.BoostMinResolution.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.BoostMinResolution.Current.has_value())
				{
					valueInt = graphicsSettings.BoostMinResolution.Current.value();
				}
				else if (graphicsSettings.BoostMinResolution.Default.has_value())
				{
					valueInt = graphicsSettings.BoostMinResolution.Default.value();
				}

				//Set setting value
				slider_RadeonBoost_MinResolution().Value(valueInt);

				//Set hint value
				std::wstring valueHint = number_to_wstring(valueInt) + L"%";
				textblock_RadeonBoost_MinResolution_Value().Text(valueHint);

				//Set interface
				if (graphicsSettings.BoostMinResolution.Minimum.has_value())
				{
					slider_RadeonBoost_MinResolution().Minimum(graphicsSettings.BoostMinResolution.Minimum.value());
					slider_RadeonBoost_MinResolution().Maximum(graphicsSettings.BoostMinResolution.Maximum.value());
					slider_RadeonBoost_MinResolution().StepFrequency(graphicsSettings.BoostMinResolution.Step.value());
					slider_RadeonBoost_MinResolution().SmallChange(graphicsSettings.BoostMinResolution.Step.value());
				}
			}
			else
			{
				//Set hint value
				textblock_RadeonBoost_MinResolution_Value().Text(L"");

				//Enable or disable interface
				slider_RadeonBoost_MinResolution().IsEnabled(false);
			}

			//Radeon Frame Rate Target Control - Enabled
			if (graphicsSettings.FrtcEnabled.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.FrtcEnabled.Current.has_value())
				{
					valueInt = graphicsSettings.FrtcEnabled.Current.value();
				}
				else if (graphicsSettings.FrtcEnabled.Default.has_value())
				{
					valueInt = graphicsSettings.FrtcEnabled.Default.value();
				}

				//Set setting value
				toggleswitch_Frtc().IsOn(valueInt);

				//Set hint value
				std::wstring valueHint = valueInt ? L"Enabled" : L"Disabled";
				textblock_Frtc_Value().Text(valueHint);

				//Enable or disable interface
				toggleswitch_Frtc().IsEnabled(true);
				slider_Frtc_FrameRateTarget().IsEnabled(valueInt);
			}
			else
			{
				//Set hint value
				textblock_Frtc_Value().Text(L"");

				//Enable or disable interface
				toggleswitch_Frtc().IsEnabled(false);
			}

			//Radeon Frame Rate Target Control - Maximum Frame Rate
			if (graphicsSettings.FrtcFrameRateTarget.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.FrtcFrameRateTarget.Current.has_value())
				{
					valueInt = graphicsSettings.FrtcFrameRateTarget.Current.value();
				}
				else if (graphicsSettings.FrtcFrameRateTarget.Default.has_value())
				{
					valueInt = graphicsSettings.FrtcFrameRateTarget.Default.value();
				}

				//Set setting value
				slider_Frtc_FrameRateTarget().Value(valueInt);

				//Set hint value
				std::wstring valueHint = number_to_wstring(valueInt) + L" FPS";
				textblock_Frtc_FrameRateTarget_Value().Text(valueHint);

				//Set interface
				if (graphicsSettings.FrtcFrameRateTarget.Minimum.has_value())
				{
					slider_Frtc_FrameRateTarget().Minimum(graphicsSettings.FrtcFrameRateTarget.Minimum.value());
					slider_Frtc_FrameRateTarget().Maximum(graphicsSettings.FrtcFrameRateTarget.Maximum.value());
					slider_Frtc_FrameRateTarget().StepFrequency(graphicsSettings.FrtcFrameRateTarget.Step.value());
					slider_Frtc_FrameRateTarget().SmallChange(graphicsSettings.FrtcFrameRateTarget.Step.value());
				}
			}
			else
			{
				//Set hint value
				textblock_Frtc_FrameRateTarget_Value().Text(L"");

				//Enable or disable interface
				slider_Frtc_FrameRateTarget().IsEnabled(false);
			}

			//Radeon Chill
			if (graphicsSettings.ChillEnabled.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.ChillEnabled.Current.has_value())
				{
					valueInt = graphicsSettings.ChillEnabled.Current.value();
				}
				else if (graphicsSettings.ChillEnabled.Default.has_value())
				{
					valueInt = graphicsSettings.ChillEnabled.Default.value();
				}

				//Set setting value
				toggleswitch_RadeonChill().IsOn(valueInt);

				//Set hint value
				std::wstring valueHint = valueInt ? L"Enabled" : L"Disabled";
				textblock_RadeonChill_Value().Text(valueHint);

				//Check Radeon Chill Link
				if (radeon_Chill_Linked)
				{
					slider_RadeonChill_Min().IsEnabled(false);
				}

				//Enable or disable interface
				toggleswitch_RadeonChill().IsEnabled(true);
				slider_RadeonChill_Min().IsEnabled(valueInt);
				slider_RadeonChill_Max().IsEnabled(valueInt);
				button_RadeonChill_Link().IsEnabled(valueInt);
			}
			else
			{
				//Set hint value
				textblock_RadeonChill_Value().Text(L"");

				//Enable or disable interface
				toggleswitch_RadeonChill().IsEnabled(false);
			}

			//Radeon Chill - Minimum Frame Rate
			if (graphicsSettings.ChillMinFps.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.ChillMinFps.Current.has_value())
				{
					valueInt = graphicsSettings.ChillMinFps.Current.value();
				}
				else if (graphicsSettings.ChillMinFps.Default.has_value())
				{
					valueInt = graphicsSettings.ChillMinFps.Default.value();
				}

				//Set setting value
				slider_RadeonChill_Min().Value(valueInt);

				//Set hint value
				std::wstring valueHint = number_to_wstring(valueInt) + L" /";
				textblock_RadeonChill_Min_Value().Text(valueHint);

				//Set interface
				if (graphicsSettings.ChillMinFps.Minimum.has_value())
				{
					slider_RadeonChill_Min().Minimum(graphicsSettings.ChillMinFps.Minimum.value());
					slider_RadeonChill_Min().Maximum(graphicsSettings.ChillMinFps.Maximum.value());
					slider_RadeonChill_Min().StepFrequency(graphicsSettings.ChillMinFps.Step.value());
					slider_RadeonChill_Min().SmallChange(graphicsSettings.ChillMinFps.Step.value());
				}
			}
			else
			{
				//Set hint value
				textblock_RadeonChill_Min_Value().Text(L"");

				//Enable or disable interface
				slider_RadeonChill_Min().IsEnabled(false);
			}

			//Radeon Chill - Maximum Frame Rate
			if (graphicsSettings.ChillMaxFps.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.ChillMaxFps.Current.has_value())
				{
					valueInt = graphicsSettings.ChillMaxFps.Current.value();
				}
				else if (graphicsSettings.ChillMaxFps.Default.has_value())
				{
					valueInt = graphicsSettings.ChillMaxFps.Default.value();
				}

				//Set setting value
				slider_RadeonChill_Max().Value(valueInt);

				//Set hint value
				std::wstring valueHint = number_to_wstring(valueInt) + L" FPS";
				textblock_RadeonChill_Max_Value().Text(valueHint);

				//Set interface
				if (graphicsSettings.ChillMaxFps.Minimum.has_value())
				{
					slider_RadeonChill_Max().Minimum(graphicsSettings.ChillMaxFps.Minimum.value());
					slider_RadeonChill_Max().Maximum(graphicsSettings.ChillMaxFps.Maximum.value());
					slider_RadeonChill_Max().StepFrequency(graphicsSettings.ChillMaxFps.Step.value());
					slider_RadeonChill_Max().SmallChange(graphicsSettings.ChillMaxFps.Step.value());
				}
			}
			else
			{
				//Set hint value
				textblock_RadeonChill_Max_Value().Text(L"");

				//Enable or disable interface
				slider_RadeonChill_Max().IsEnabled(false);
			}

			//Radeon Image Sharpening - Enabled
			if (graphicsSettings.RisEnabled.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.RisEnabled.Current.has_value())
				{
					valueInt = graphicsSettings.RisEnabled.Current.value();
				}
				else if (graphicsSettings.RisEnabled.Default.has_value())
				{
					valueInt = graphicsSettings.RisEnabled.Default.value();
				}

				//Check setting version
				if (graphicsSettings.RisVersion.Version <= 1)
				{
					//Set setting value
					toggleswitch_RadeonImageSharpening1().IsOn(valueInt);

					//Set hint value
					std::wstring valueHint = valueInt ? L"Enabled" : L"Disabled";
					textblock_RadeonImageSharpening1_Value().Text(valueHint);

					//Enable or disable interface
					toggleswitch_RadeonImageSharpening1().IsEnabled(true);
					slider_RadeonImageSharpening1_Sharpening().IsEnabled(valueInt);

					toggleswitch_RadeonImageSharpening2().IsEnabled(false);
					toggleswitch_RadeonImageSharpening2_Desktop().IsEnabled(false);
					slider_RadeonImageSharpening2_Sharpening().IsEnabled(false);
				}
				else
				{
					//Set setting value
					toggleswitch_RadeonImageSharpening2().IsOn(valueInt);

					//Set hint value
					std::wstring valueHint = valueInt ? L"Enabled" : L"Disabled";
					textblock_RadeonImageSharpening2_Value().Text(valueHint);

					//Enable or disable interface
					toggleswitch_RadeonImageSharpening2().IsEnabled(true);
					if (valueInt)
					{
						toggleswitch_RadeonImageSharpening2_Desktop().IsEnabled(graphicsSettings.Global());
						slider_RadeonImageSharpening2_Sharpening().IsEnabled(true);
					}
					else
					{
						toggleswitch_RadeonImageSharpening2_Desktop().IsEnabled(false);
						slider_RadeonImageSharpening2_Sharpening().IsEnabled(false);
					}

					toggleswitch_RadeonImageSharpening1().IsEnabled(false);
					slider_RadeonImageSharpening1_Sharpening().IsEnabled(false);
				}
			}
			else
			{
				//Set hint value
				textblock_RadeonImageSharpening1_Value().Text(L"");
				textblock_RadeonImageSharpening2_Value().Text(L"");

				//Enable or disable interface
				toggleswitch_RadeonImageSharpening1().IsEnabled(false);
				toggleswitch_RadeonImageSharpening2().IsEnabled(false);
			}

			//Radeon Image Sharpening - Sharpen Desktop
			if (graphicsSettings.RisDesktopEnabled.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.RisDesktopEnabled.Current.has_value())
				{
					valueInt = graphicsSettings.RisDesktopEnabled.Current.value();
				}
				else if (graphicsSettings.RisDesktopEnabled.Default.has_value())
				{
					valueInt = graphicsSettings.RisDesktopEnabled.Default.value();
				}

				//Set setting value
				toggleswitch_RadeonImageSharpening2_Desktop().IsOn(valueInt);

				//Set hint value
				std::wstring valueHint = valueInt ? L"Enabled" : L"Disabled";
				textblock_RadeonImageSharpening2_Desktop_Value().Text(valueHint);
			}
			else
			{
				//Set hint value
				textblock_RadeonImageSharpening2_Desktop_Value().Text(L"");

				//Enable or disable interface
				toggleswitch_RadeonImageSharpening2_Desktop().IsEnabled(false);
			}

			//Radeon Image Sharpening - Sharpening Degree
			if (graphicsSettings.RisSharpeningDegree.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.RisSharpeningDegree.Current.has_value())
				{
					valueInt = graphicsSettings.RisSharpeningDegree.Current.value();
				}
				else if (graphicsSettings.RisSharpeningDegree.Default.has_value())
				{
					valueInt = graphicsSettings.RisSharpeningDegree.Default.value();
				}

				//Check setting version
				if (graphicsSettings.RisVersion.Version <= 1)
				{
					//Set setting value
					slider_RadeonImageSharpening1_Sharpening().Value(valueInt);

					//Set hint value
					std::wstring valueHint = number_to_wstring(valueInt) + L"%";
					textblock_RadeonImageSharpening1_Sharpening_Value().Text(valueHint);

					//Set interface
					if (graphicsSettings.RisSharpeningDegree.Minimum.has_value())
					{
						slider_RadeonImageSharpening1_Sharpening().Minimum(graphicsSettings.RisSharpeningDegree.Minimum.value());
						slider_RadeonImageSharpening1_Sharpening().Maximum(graphicsSettings.RisSharpeningDegree.Maximum.value());
						slider_RadeonImageSharpening1_Sharpening().StepFrequency(graphicsSettings.RisSharpeningDegree.Step.value());
						slider_RadeonImageSharpening1_Sharpening().SmallChange(graphicsSettings.RisSharpeningDegree.Step.value());
					}
				}
				else
				{
					//Set setting value
					slider_RadeonImageSharpening2_Sharpening().Value(valueInt);

					//Set hint value
					std::wstring valueHint = number_to_wstring(valueInt) + L"%";
					textblock_RadeonImageSharpening2_Sharpening_Value().Text(valueHint);

					//Set interface
					if (graphicsSettings.RisSharpeningDegree.Minimum.has_value())
					{
						slider_RadeonImageSharpening2_Sharpening().Minimum(graphicsSettings.RisSharpeningDegree.Minimum.value());
						slider_RadeonImageSharpening2_Sharpening().Maximum(graphicsSettings.RisSharpeningDegree.Maximum.value());
						slider_RadeonImageSharpening2_Sharpening().StepFrequency(graphicsSettings.RisSharpeningDegree.Step.value());
						slider_RadeonImageSharpening2_Sharpening().SmallChange(graphicsSettings.RisSharpeningDegree.Step.value());
					}
				}
			}
			else
			{
				//Set hint value
				textblock_RadeonImageSharpening2_Sharpening_Value().Text(L"");

				//Enable or disable interface
				slider_RadeonImageSharpening2_Sharpening().IsEnabled(false);
			}

			//Enhanced Sync
			if (graphicsSettings.EnhancedSync.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.EnhancedSync.Current.has_value())
				{
					valueInt = graphicsSettings.EnhancedSync.Current.value();
				}
				else if (graphicsSettings.EnhancedSync.Default.has_value())
				{
					valueInt = graphicsSettings.EnhancedSync.Default.value();
				}

				//Set setting value
				toggleswitch_RadeonEnhancedSync().IsOn(valueInt);

				//Set hint value
				std::wstring valueHint = valueInt ? L"Enabled" : L"Disabled";
				textblock_RadeonEnhancedSync_Value().Text(valueHint);

				//Enable or disable interface
				toggleswitch_RadeonEnhancedSync().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_RadeonEnhancedSync_Value().Text(L"");

				//Enable or disable interface
				toggleswitch_RadeonEnhancedSync().IsEnabled(false);
			}

			//Vertical Sync
			if (graphicsSettings.VerticalSync.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.VerticalSync.Current.has_value())
				{
					valueInt = graphicsSettings.VerticalSync.Current.value();
				}
				else if (graphicsSettings.VerticalSync.Default.has_value())
				{
					valueInt = graphicsSettings.VerticalSync.Default.value();
				}

				//Set setting value
				combobox_VerticalSync().SelectedIndex(valueInt);

				//Set hint value
				std::wstring valueHint = ADLX_WAIT_FOR_VERTICAL_REFRESH_MODE_STRING[valueInt];
				textblock_VerticalSync_Value().Text(valueHint);

				//Enable or disable interface
				combobox_VerticalSync().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_VerticalSync_Value().Text(L"");

				//Enable or disable interface
				combobox_VerticalSync().IsEnabled(false);
			}

			//Anti-Aliasing Override
			if (graphicsSettings.AntiAliasingOverride.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.AntiAliasingOverride.Current.has_value())
				{
					valueInt = graphicsSettings.AntiAliasingOverride.Current.value();
				}
				else if (graphicsSettings.AntiAliasingOverride.Default.has_value())
				{
					valueInt = graphicsSettings.AntiAliasingOverride.Default.value();
				}

				//Set setting value
				toggleswitch_AntiAliasingOverride().IsOn(valueInt);

				//Set hint value
				std::wstring valueHint = valueInt ? L"Enabled" : L"Disabled";
				textblock_AntiAliasingOverride_Value().Text(valueHint);

				//Enable or disable interface
				toggleswitch_AntiAliasingOverride().IsEnabled(true);
				combobox_AntiAliasingMethod().IsEnabled(valueInt);
				combobox_AntiAliasingLevel().IsEnabled(valueInt);
				toggleswitch_AntiAliasingEnhancedQuality().IsEnabled(valueInt);
			}
			else
			{
				//Set hint value
				textblock_AntiAliasingOverride_Value().Text(L"");

				//Enable or disable interface
				toggleswitch_AntiAliasingOverride().IsEnabled(false);
			}

			//Anti-Aliasing Method
			if (graphicsSettings.AntiAliasingMethod.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.AntiAliasingMethod.Current.has_value())
				{
					valueInt = graphicsSettings.AntiAliasingMethod.Current.value();
				}
				else if (graphicsSettings.AntiAliasingMethod.Default.has_value())
				{
					valueInt = graphicsSettings.AntiAliasingMethod.Default.value();
				}

				//Set setting value
				combobox_AntiAliasingMethod().SelectedIndex(valueInt);

				//Set hint value
				std::wstring valueHint = ADLX_ANTI_ALIASING_METHOD_STRING[valueInt];
				textblock_AntiAliasingMethod_Value().Text(valueHint);
			}
			else
			{
				//Set hint value
				textblock_AntiAliasingMethod_Value().Text(L"");

				//Enable or disable interface
				combobox_AntiAliasingMethod().IsEnabled(false);
			}

			//Anti-Aliasing Level
			if (graphicsSettings.AntiAliasingLevel.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.AntiAliasingLevel.Current.has_value())
				{
					valueInt = graphicsSettings.AntiAliasingLevel.Current.value();
				}
				else if (graphicsSettings.AntiAliasingLevel.Default.has_value())
				{
					valueInt = graphicsSettings.AntiAliasingLevel.Default.value();
				}

				//Set setting value
				combobox_AntiAliasingLevel().SelectedIndex(valueInt);

				//Set hint value
				std::wstring valueHint = ADLX_ANTI_ALIASING_LEVEL_STRING[valueInt];
				textblock_AntiAliasingLevel_Value().Text(valueHint);
			}
			else
			{
				//Set hint value
				textblock_AntiAliasingLevel_Value().Text(L"");

				//Enable or disable interface
				combobox_AntiAliasingLevel().IsEnabled(false);
			}

			//Enhanced Quality Anti-Aliasing
			if (graphicsSettings.AntiAliasingEnhancedQuality.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.AntiAliasingEnhancedQuality.Current.has_value())
				{
					valueInt = graphicsSettings.AntiAliasingEnhancedQuality.Current.value();
				}
				else if (graphicsSettings.AntiAliasingEnhancedQuality.Default.has_value())
				{
					valueInt = graphicsSettings.AntiAliasingEnhancedQuality.Default.value();
				}

				//Set setting value
				toggleswitch_AntiAliasingEnhancedQuality().IsOn(valueInt);

				//Set hint value
				std::wstring valueHint = valueInt ? L"Enabled" : L"Disabled";
				textblock_AntiAliasingEnhancedQuality_Value().Text(valueHint);
			}
			else
			{
				//Set hint value
				textblock_AntiAliasingEnhancedQuality_Value().Text(L"");

				//Enable or disable interface
				toggleswitch_AntiAliasingEnhancedQuality().IsEnabled(false);
			}

			//Morphological Anti-Aliasing
			if (graphicsSettings.AntiAliasingMorphological.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.AntiAliasingMorphological.Current.has_value())
				{
					valueInt = graphicsSettings.AntiAliasingMorphological.Current.value();
				}
				else if (graphicsSettings.AntiAliasingMorphological.Default.has_value())
				{
					valueInt = graphicsSettings.AntiAliasingMorphological.Default.value();
				}

				//Set setting value
				toggleswitch_MorphologicalAntiAliasing().IsOn(valueInt);

				//Set hint value
				std::wstring valueHint = valueInt ? L"Enabled" : L"Disabled";
				textblock_MorphologicalAntiAliasing_Value().Text(valueHint);

				//Enable or disable interface
				toggleswitch_MorphologicalAntiAliasing().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_MorphologicalAntiAliasing_Value().Text(L"");

				//Enable or disable interface
				toggleswitch_MorphologicalAntiAliasing().IsEnabled(false);
			}

			//Anisotropic Texture Filtering Override
			if (graphicsSettings.AnisotropicOverride.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.AnisotropicOverride.Current.has_value())
				{
					valueInt = graphicsSettings.AnisotropicOverride.Current.value();
				}
				else if (graphicsSettings.AnisotropicOverride.Default.has_value())
				{
					valueInt = graphicsSettings.AnisotropicOverride.Default.value();
				}

				//Set setting value
				combobox_AnisotropicTextureFiltering().SelectedIndex(valueInt);

				//Set hint value
				std::wstring valueHint = ADLX_ANISOTROPIC_FILTERING_LEVEL_STRING[valueInt];
				textblock_AnisotropicTextureFiltering_Value().Text(valueHint);

				//Enable or disable interface
				combobox_AnisotropicTextureFiltering().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_AnisotropicTextureFiltering_Value().Text(L"");

				//Enable or disable interface
				combobox_AnisotropicTextureFiltering().IsEnabled(false);
			}

			//Texture Filtering Quality
			if (graphicsSettings.TextureFilteringQuality.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.TextureFilteringQuality.Current.has_value())
				{
					valueInt = graphicsSettings.TextureFilteringQuality.Current.value();
				}
				else if (graphicsSettings.TextureFilteringQuality.Default.has_value())
				{
					valueInt = graphicsSettings.TextureFilteringQuality.Default.value();
				}

				//Set setting value
				combobox_TextureFilteringQuality().SelectedIndex(valueInt);

				//Set hint value
				std::wstring valueHint = REGISTRY_TEXTURE_FILTERING_QUALITY_STRING[valueInt];
				textblock_TextureFilteringQuality_Value().Text(valueHint);

				//Enable or disable interface
				combobox_TextureFilteringQuality().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_TextureFilteringQuality_Value().Text(L"");

				//Enable or disable interface
				combobox_TextureFilteringQuality().IsEnabled(false);
			}

			//Surface Format Optimization
			if (graphicsSettings.SurfaceFormatOptimization.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.SurfaceFormatOptimization.Current.has_value())
				{
					valueInt = graphicsSettings.SurfaceFormatOptimization.Current.value();
				}
				else if (graphicsSettings.SurfaceFormatOptimization.Default.has_value())
				{
					valueInt = graphicsSettings.SurfaceFormatOptimization.Default.value();
				}

				//Set setting value
				toggleswitch_SurfaceFormatOptimization().IsOn(valueInt);

				//Set hint value
				std::wstring valueHint = valueInt ? L"Enabled" : L"Disabled";
				textblock_SurfaceFormatOptimization_Value().Text(valueHint);

				//Enable or disable interface
				toggleswitch_SurfaceFormatOptimization().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_SurfaceFormatOptimization_Value().Text(L"");

				//Enable or disable interface
				toggleswitch_SurfaceFormatOptimization().IsEnabled(false);
			}

			//Tessellation Mode
			if (graphicsSettings.TessellationMode.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.TessellationMode.Current.has_value())
				{
					valueInt = graphicsSettings.TessellationMode.Current.value();
				}
				else if (graphicsSettings.TessellationMode.Default.has_value())
				{
					valueInt = graphicsSettings.TessellationMode.Default.value();
				}

				//Set setting value
				combobox_Tessellation_Mode().SelectedIndex(valueInt);

				//Set hint value
				std::wstring valueHint = ADLX_TESSELLATION_MODE_STRING[valueInt];
				textblock_TessellationMode_Value().Text(valueHint);

				//Enable or disable interface
				combobox_Tessellation_Mode().IsEnabled(true);

				bool subSettingEnabled = valueInt == 2;
				combobox_Tessellation_Level().IsEnabled(subSettingEnabled);
			}
			else
			{
				//Enable or disable interface
				combobox_Tessellation_Mode().IsEnabled(false);
			}

			//Tessellation Level
			if (graphicsSettings.TessellationLevel.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.TessellationLevel.Current.has_value())
				{
					valueInt = graphicsSettings.TessellationLevel.Current.value();
				}
				else if (graphicsSettings.TessellationLevel.Default.has_value())
				{
					valueInt = graphicsSettings.TessellationLevel.Default.value();
				}

				//Set setting value
				combobox_Tessellation_Level().SelectedIndex(valueInt);

				//Set hint value
				std::wstring valueHint = ADLX_TESSELLATION_LEVEL_STRING[valueInt];
				textblock_TessellationLevel_Value().Text(valueHint);
			}
			else
			{
				//Set hint value
				textblock_TessellationLevel_Value().Text(L"");

				//Enable or disable interface
				combobox_Tessellation_Level().IsEnabled(false);
			}

			//OpenGL Triple Buffering
			if (graphicsSettings.OpenGLTripleBuffering.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.OpenGLTripleBuffering.Current.has_value())
				{
					valueInt = graphicsSettings.OpenGLTripleBuffering.Current.value();
				}
				else if (graphicsSettings.OpenGLTripleBuffering.Default.has_value())
				{
					valueInt = graphicsSettings.OpenGLTripleBuffering.Default.value();
				}

				//Set setting value
				toggleswitch_OpenGLTripleBuffering().IsOn(valueInt);

				//Set hint value
				std::wstring valueHint = valueInt ? L"Enabled" : L"Disabled";
				textblock_OpenGLTripleBuffering_Value().Text(valueHint);

				//Enable or disable interface
				toggleswitch_OpenGLTripleBuffering().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_OpenGLTripleBuffering_Value().Text(L"");

				//Enable or disable interface
				toggleswitch_OpenGLTripleBuffering().IsEnabled(false);
			}

			//OpenGL 10-Bit Pixel Format
			if (graphicsSettings.OpenGL10BitPixelFormat.Support)
			{
				//Get setting
				int valueInt = 0;
				if (graphicsSettings.OpenGL10BitPixelFormat.Current.has_value())
				{
					valueInt = graphicsSettings.OpenGL10BitPixelFormat.Current.value();
				}
				else if (graphicsSettings.OpenGL10BitPixelFormat.Default.has_value())
				{
					valueInt = graphicsSettings.OpenGL10BitPixelFormat.Default.value();
				}

				//Set setting value
				toggleswitch_OpenGL10BitPixelFormat().IsOn(valueInt);

				//Set hint value
				std::wstring valueHint = valueInt ? L"Enabled" : L"Disabled";
				textblock_OpenGL10BitPixelFormat_Value().Text(valueHint);

				//Enable or disable interface
				toggleswitch_OpenGL10BitPixelFormat().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_OpenGL10BitPixelFormat_Value().Text(L"");

				//Enable or disable interface
				toggleswitch_OpenGL10BitPixelFormat().IsEnabled(false);
			}

			//Return result
			AVDebugWriteLine(L"Graphics settings applied to interface (ADL)");
			return true;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine(L"Failed applying graphics settings to interface (ADL)");
			return false;
		}
	}
}