#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::GraphicsSettings_Convert_ToUI_Adl(GraphicsSettings graphicsSettings, AdlSettingGet settingType)
	{
		try
		{
			//FSR Upscaling Override
			if (graphicsSettings.FsrOverride.Support && graphicsSettings.FsrOverride.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = graphicsSettings.FsrOverride.Get(settingType, true).value();

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
			if (graphicsSettings.MlfiOverride.Support && graphicsSettings.MlfiOverride.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = graphicsSettings.MlfiOverride.Get(settingType, true).value();

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
			if (graphicsSettings.MfgOverride.Support && graphicsSettings.MfgOverride.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = graphicsSettings.MfgOverride.Get(settingType, true).value();

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
			if (graphicsSettings.MldOverride.Support && graphicsSettings.MldOverride.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = graphicsSettings.MldOverride.Get(settingType, true).value();

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
			if (graphicsSettings.NrcOverride.Support && graphicsSettings.NrcOverride.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = graphicsSettings.NrcOverride.Get(settingType, true).value();

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
			if (graphicsSettings.MfgRatio.Support && graphicsSettings.MfgRatio.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = graphicsSettings.MfgRatio.Get(settingType, true).value();

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
			if (graphicsSettings.FsrOvrDLLPath.Support && graphicsSettings.FsrOvrDLLPath.Get(settingType, true).has_value())
			{
				//Get setting
				std::wstring valueString = graphicsSettings.FsrOvrDLLPath.Get(settingType, true).value();

				//Set FSR library version information
				FsrOverrideDllUpdateTextPathInfo(valueString);
				FsrOverrideDllUpdateTextVersion(valueString);

				//Enable or disable interface
				button_FsrDllLoadPath_Default().IsEnabled(true);
				button_FsrDllLoadPath_Set().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				button_FsrDllLoadPath_Default().IsEnabled(false);
				button_FsrDllLoadPath_Set().IsEnabled(false);
			}

			//FSR Show Information
			if (graphicsSettings.FsrShowInformation.Support && graphicsSettings.FsrShowInformation.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = graphicsSettings.FsrShowInformation.Get(settingType, true).value();

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

			//FSR Disable ML Swapchain
			if (graphicsSettings.FsrDisableMLSwapchain.Support && graphicsSettings.FsrDisableMLSwapchain.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = graphicsSettings.FsrDisableMLSwapchain.Get(settingType, true).value();

				//Set setting value
				toggleswitch_FsrDisableMLSwapchain().IsOn(valueInt);

				//Set hint value
				std::wstring valueHint = valueInt ? L"Enabled" : L"Disabled";
				textblock_FsrDisableMLSwapchain_Value().Text(valueHint);

				//Enable or disable interface
				toggleswitch_FsrDisableMLSwapchain().IsEnabled(true);
			}
			else
			{
				//Set hint value
				textblock_FsrDisableMLSwapchain_Value().Text(L"");

				//Enable or disable interface
				toggleswitch_FsrDisableMLSwapchain().IsEnabled(false);
			}

			//FSR Latency Reduction
			if (graphicsSettings.DeLagEnabled.Support && graphicsSettings.DeLagEnabled.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = graphicsSettings.DeLagEnabled.Get(settingType, true).value();

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

			//Radeon Fluid Motion Frames - Enabled
			if (graphicsSettings.FrameGenEnabled.Support && graphicsSettings.FrameGenEnabled.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = graphicsSettings.FrameGenEnabled.Get(settingType, true).value();

				//Set setting value
				toggleswitch_FrameGenEnabled().IsOn(valueInt);

				//Set hint value
				std::wstring valueHint = valueInt ? L"Enabled" : L"Disabled";
				textblock_FrameGenEnabled_Value().Text(valueHint);

				//Enable or disable interface
				toggleswitch_FrameGenEnabled().IsEnabled(true);
				combobox_FrameGenAlgorithm().IsEnabled(valueInt);
			}
			else
			{
				//Set hint value
				textblock_FrameGenEnabled_Value().Text(L"");

				//Enable or disable interface
				toggleswitch_FrameGenEnabled().IsEnabled(false);
			}

			//Radeon Fluid Motion Frames - Algorithm
			if (graphicsSettings.FrameGenAlgorithm.Support && graphicsSettings.FrameGenAlgorithm.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = graphicsSettings.FrameGenAlgorithm.Get(settingType, true).value();

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
			if (graphicsSettings.BoostMode.Support && graphicsSettings.BoostMode.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = graphicsSettings.BoostMode.Get(settingType, true).value();

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
			if (graphicsSettings.BoostMinResolution.Support && graphicsSettings.BoostMinResolution.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = graphicsSettings.BoostMinResolution.Get(settingType, true).value();

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
			if (graphicsSettings.FrtcEnabled.Support && graphicsSettings.FrtcEnabled.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = graphicsSettings.FrtcEnabled.Get(settingType, true).value();

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
			if (graphicsSettings.FrtcFrameRateTarget.Support && graphicsSettings.FrtcFrameRateTarget.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = graphicsSettings.FrtcFrameRateTarget.Get(settingType, true).value();

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
			if (graphicsSettings.ChillEnabled.Support && graphicsSettings.ChillEnabled.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = graphicsSettings.ChillEnabled.Get(settingType, true).value();

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
			if (graphicsSettings.ChillMinFps.Support && graphicsSettings.ChillMinFps.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = graphicsSettings.ChillMinFps.Get(settingType, true).value();

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
			if (graphicsSettings.ChillMaxFps.Support && graphicsSettings.ChillMaxFps.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = graphicsSettings.ChillMaxFps.Get(settingType, true).value();

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
			if (graphicsSettings.RisEnabled.Support && graphicsSettings.RisEnabled.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = graphicsSettings.RisEnabled.Get(settingType, true).value();

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
			if (graphicsSettings.RisDesktopEnabled.Support && graphicsSettings.RisDesktopEnabled.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = graphicsSettings.RisDesktopEnabled.Get(settingType, true).value();

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
			if (graphicsSettings.RisSharpeningDegree.Support && graphicsSettings.RisSharpeningDegree.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = graphicsSettings.RisSharpeningDegree.Get(settingType, true).value();

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
			if (graphicsSettings.EnhancedSync.Support && graphicsSettings.EnhancedSync.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = graphicsSettings.EnhancedSync.Get(settingType, true).value();

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
			if (graphicsSettings.VerticalSync.Support && graphicsSettings.VerticalSync.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = graphicsSettings.VerticalSync.Get(settingType, true).value();

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
			if (graphicsSettings.AntiAliasingOverride.Support && graphicsSettings.AntiAliasingOverride.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = graphicsSettings.AntiAliasingOverride.Get(settingType, true).value();

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
			if (graphicsSettings.AntiAliasingMethod.Support && graphicsSettings.AntiAliasingMethod.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = graphicsSettings.AntiAliasingMethod.Get(settingType, true).value();

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
			if (graphicsSettings.AntiAliasingLevel.Support && graphicsSettings.AntiAliasingLevel.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = graphicsSettings.AntiAliasingLevel.Get(settingType, true).value();

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
			if (graphicsSettings.AntiAliasingEnhancedQuality.Support && graphicsSettings.AntiAliasingEnhancedQuality.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = graphicsSettings.AntiAliasingEnhancedQuality.Get(settingType, true).value();

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
			if (graphicsSettings.AntiAliasingMorphological.Support && graphicsSettings.AntiAliasingMorphological.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = graphicsSettings.AntiAliasingMorphological.Get(settingType, true).value();

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
			if (graphicsSettings.AnisotropicOverride.Support && graphicsSettings.AnisotropicOverride.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = graphicsSettings.AnisotropicOverride.Get(settingType, true).value();

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
			if (graphicsSettings.TextureFilteringQuality.Support && graphicsSettings.TextureFilteringQuality.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = graphicsSettings.TextureFilteringQuality.Get(settingType, true).value();

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
			if (graphicsSettings.SurfaceFormatOptimization.Support && graphicsSettings.SurfaceFormatOptimization.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = graphicsSettings.SurfaceFormatOptimization.Get(settingType, true).value();

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
			if (graphicsSettings.TessellationMode.Support && graphicsSettings.TessellationMode.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = graphicsSettings.TessellationMode.Get(settingType, true).value();

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
			if (graphicsSettings.TessellationLevel.Support && graphicsSettings.TessellationLevel.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = graphicsSettings.TessellationLevel.Get(settingType, true).value();

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
			if (graphicsSettings.OpenGLTripleBuffering.Support && graphicsSettings.OpenGLTripleBuffering.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = graphicsSettings.OpenGLTripleBuffering.Get(settingType, true).value();

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
			if (graphicsSettings.OpenGL10BitPixelFormat.Support && graphicsSettings.OpenGL10BitPixelFormat.Get(settingType, true).has_value())
			{
				//Get setting
				int valueInt = graphicsSettings.OpenGL10BitPixelFormat.Get(settingType, true).value();

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

			//Top buttons
			button_AppSelect_Graphics().IsEnabled(true);
			button_AppAdd_Graphics().IsEnabled(true);
			button_AppRemove_Graphics().IsEnabled(true);
			button_Graphics_Apply().IsEnabled(true);
			button_Graphics_Reset().IsEnabled(true);
			button_Graphics_Import().IsEnabled(true);
			button_Graphics_Export().IsEnabled(true);

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