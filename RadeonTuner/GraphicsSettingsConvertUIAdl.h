#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::GraphicsSettings_Convert_ToUI_ADL(GraphicsSettings graphicsSettings)
	{
		try
		{
			//FSR Upscaling Override
			if (graphicsSettings.FsrOverride.Support.has_value() && graphicsSettings.FsrOverride.Support.value())
			{
				//Set setting
				if (graphicsSettings.FsrOverride.Current.has_value())
				{
					toggleswitch_FsrOverrideUpscaling().IsOn(graphicsSettings.FsrOverride.Current.value());
				}
				else if (graphicsSettings.FsrOverride.Default.has_value())
				{
					toggleswitch_FsrOverrideUpscaling().IsOn(graphicsSettings.FsrOverride.Default.value());
				}

				//Enable or disable interface
				toggleswitch_FsrOverrideUpscaling().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				toggleswitch_FsrOverrideUpscaling().IsEnabled(false);
			}

			//FSR Frame Generation Override
			if (graphicsSettings.MlfiOverride.Support.has_value() && graphicsSettings.MlfiOverride.Support.value())
			{
				//Set setting
				if (graphicsSettings.MlfiOverride.Current.has_value())
				{
					toggleswitch_FsrOverrideFrameGeneration().IsOn(graphicsSettings.MlfiOverride.Current.value());
				}
				else if (graphicsSettings.MlfiOverride.Default.has_value())
				{
					toggleswitch_FsrOverrideFrameGeneration().IsOn(graphicsSettings.MlfiOverride.Default.value());
				}

				//Enable or disable interface
				toggleswitch_FsrOverrideFrameGeneration().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				toggleswitch_FsrOverrideFrameGeneration().IsEnabled(false);
			}

			//FSR Multi Frame Generation Override
			if (graphicsSettings.MfgOverride.Support.has_value() && graphicsSettings.MfgOverride.Support.value())
			{
				//Set setting
				if (graphicsSettings.MfgOverride.Current.has_value())
				{
					toggleswitch_FsrOverrideMultiFrameGeneration().IsOn(graphicsSettings.MfgOverride.Current.value());
				}
				else if (graphicsSettings.MfgOverride.Default.has_value())
				{
					toggleswitch_FsrOverrideMultiFrameGeneration().IsOn(graphicsSettings.MfgOverride.Default.value());
				}

				//Enable or disable interface
				toggleswitch_FsrOverrideMultiFrameGeneration().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				toggleswitch_FsrOverrideMultiFrameGeneration().IsEnabled(false);
			}

			//FSR Ray Regeneration Denoiser Override
			if (graphicsSettings.MldOverride.Support.has_value() && graphicsSettings.MldOverride.Support.value())
			{
				//Set setting
				if (graphicsSettings.MldOverride.Current.has_value())
				{
					toggleswitch_FsrOverrideRayRegeneration().IsOn(graphicsSettings.MldOverride.Current.value());
				}
				else if (graphicsSettings.MldOverride.Default.has_value())
				{
					toggleswitch_FsrOverrideRayRegeneration().IsOn(graphicsSettings.MldOverride.Default.value());
				}

				//Enable or disable interface
				toggleswitch_FsrOverrideRayRegeneration().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				toggleswitch_FsrOverrideRayRegeneration().IsEnabled(false);
			}

			//FSR Neural Radiance Caching Override
			if (graphicsSettings.NrcOverride.Support.has_value() && graphicsSettings.NrcOverride.Support.value())
			{
				//Set setting
				if (graphicsSettings.NrcOverride.Current.has_value())
				{
					toggleswitch_FsrOverrideNeuralRadianceCaching().IsOn(graphicsSettings.NrcOverride.Current.value());
				}
				else if (graphicsSettings.NrcOverride.Default.has_value())
				{
					toggleswitch_FsrOverrideNeuralRadianceCaching().IsOn(graphicsSettings.NrcOverride.Default.value());
				}

				//Enable or disable interface
				toggleswitch_FsrOverrideNeuralRadianceCaching().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				toggleswitch_FsrOverrideNeuralRadianceCaching().IsEnabled(false);
			}

			//FSR Multi Frame Generation Ratio
			if (graphicsSettings.MfgRatio.Support.has_value() && graphicsSettings.MfgRatio.Support.value())
			{
				//Set setting
				if (graphicsSettings.MfgRatio.Current.has_value())
				{
					combobox_MultiFrameGenerationRatio().SelectedIndex(graphicsSettings.MfgRatio.Current.value());
				}
				else if (graphicsSettings.MfgRatio.Default.has_value())
				{
					combobox_MultiFrameGenerationRatio().SelectedIndex(graphicsSettings.MfgRatio.Default.value());
				}

				//Enable or disable interface
				combobox_MultiFrameGenerationRatio().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				combobox_MultiFrameGenerationRatio().IsEnabled(false);
			}

			//FSR Override Library
			if (graphicsSettings.FsrOvrDLLPath.Support.has_value() && graphicsSettings.FsrOvrDLLPath.Support.value())
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
			if (graphicsSettings.FsrOtaIndex.Support.has_value() && graphicsSettings.FsrOtaIndex.Support.value())
			{
				//Set setting
				if (graphicsSettings.FsrOtaIndex.Current.has_value())
				{
					combobox_FsrOtaUpdates().SelectedIndex(graphicsSettings.FsrOtaIndex.Current.value());
				}
				else if (graphicsSettings.FsrOtaIndex.Default.has_value())
				{
					combobox_FsrOtaUpdates().SelectedIndex(graphicsSettings.FsrOtaIndex.Default.value());
				}

				//Enable or disable interface
				combobox_FsrOtaUpdates().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				combobox_FsrOtaUpdates().IsEnabled(false);
			}

			//FSR Latency Reduction
			if (graphicsSettings.DeLagEnabled.Support.has_value() && graphicsSettings.DeLagEnabled.Support.value())
			{
				//Set setting
				if (graphicsSettings.DeLagEnabled.Current.has_value())
				{
					toggleswitch_FsrLatencyReduction().IsOn(graphicsSettings.DeLagEnabled.Current.value());
				}
				else if (graphicsSettings.DeLagEnabled.Default.has_value())
				{
					toggleswitch_FsrLatencyReduction().IsOn(graphicsSettings.DeLagEnabled.Default.value());
				}

				//Enable or disable interface
				toggleswitch_FsrLatencyReduction().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				toggleswitch_FsrLatencyReduction().IsEnabled(false);
			}

			//Radeon Fluid Motion Frames
			if (graphicsSettings.FrameGenEnabled.Support.has_value() && graphicsSettings.FrameGenEnabled.Support.value())
			{
				//Set setting
				if (graphicsSettings.FrameGenEnabled.Current.has_value())
				{
					toggleswitch_FrameGenEnabled().IsOn(graphicsSettings.FrameGenEnabled.Current.value());
					combobox_FrameGenSearchMode().IsEnabled(graphicsSettings.FrameGenEnabled.Current.value());
					combobox_FrameGenPerfMode().IsEnabled(graphicsSettings.FrameGenEnabled.Current.value());
					combobox_FrameGenResponseMode().IsEnabled(graphicsSettings.FrameGenEnabled.Current.value());
					combobox_FrameGenAlgorithm().IsEnabled(graphicsSettings.FrameGenEnabled.Current.value());
				}
				else if (graphicsSettings.FrameGenEnabled.Default.has_value())
				{
					toggleswitch_FrameGenEnabled().IsOn(graphicsSettings.FrameGenEnabled.Default.value());
					combobox_FrameGenSearchMode().IsEnabled(graphicsSettings.FrameGenEnabled.Default.value());
					combobox_FrameGenPerfMode().IsEnabled(graphicsSettings.FrameGenEnabled.Default.value());
					combobox_FrameGenResponseMode().IsEnabled(graphicsSettings.FrameGenEnabled.Default.value());
					combobox_FrameGenAlgorithm().IsEnabled(graphicsSettings.FrameGenEnabled.Default.value());
				}

				//Enable or disable interface
				toggleswitch_FrameGenEnabled().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				toggleswitch_FrameGenEnabled().IsEnabled(false);
			}

			//Radeon Fluid Motion Frames - Search Mode
			if (graphicsSettings.FrameGenSearchMode.Support.has_value() && graphicsSettings.FrameGenSearchMode.Support.value())
			{
				//Set setting
				if (graphicsSettings.FrameGenSearchMode.Current.has_value())
				{
					combobox_FrameGenSearchMode().SelectedIndex(graphicsSettings.FrameGenSearchMode.Current.value());
				}
				else if (graphicsSettings.FrameGenSearchMode.Default.has_value())
				{
					combobox_FrameGenSearchMode().SelectedIndex(graphicsSettings.FrameGenSearchMode.Default.value());
				}
			}
			else
			{
				//Enable or disable interface
				combobox_FrameGenSearchMode().IsEnabled(false);
			}

			//Radeon Fluid Motion Frames - Performance Mode
			if (graphicsSettings.FrameGenPerfMode.Support.has_value() && graphicsSettings.FrameGenPerfMode.Support.value())
			{
				//Set setting
				if (graphicsSettings.FrameGenPerfMode.Current.has_value())
				{
					combobox_FrameGenPerfMode().SelectedIndex(graphicsSettings.FrameGenPerfMode.Current.value());
				}
				else if (graphicsSettings.FrameGenPerfMode.Default.has_value())
				{
					combobox_FrameGenPerfMode().SelectedIndex(graphicsSettings.FrameGenPerfMode.Default.value());
				}
			}
			else
			{
				//Enable or disable interface
				combobox_FrameGenPerfMode().IsEnabled(false);
			}

			//Radeon Fluid Motion Frames - Response Mode
			if (graphicsSettings.FrameGenResponseMode.Support.has_value() && graphicsSettings.FrameGenResponseMode.Support.value())
			{
				//Set setting
				if (graphicsSettings.FrameGenResponseMode.Current.has_value())
				{
					combobox_FrameGenResponseMode().SelectedIndex(graphicsSettings.FrameGenResponseMode.Current.value());
				}
				else if (graphicsSettings.FrameGenResponseMode.Default.has_value())
				{
					combobox_FrameGenResponseMode().SelectedIndex(graphicsSettings.FrameGenResponseMode.Default.value());
				}
			}
			else
			{
				//Enable or disable interface
				combobox_FrameGenResponseMode().IsEnabled(false);
			}

			//Radeon Fluid Motion Frames - Algorithm
			if (graphicsSettings.FrameGenAlgorithm.Support.has_value() && graphicsSettings.FrameGenAlgorithm.Support.value())
			{
				//Set setting
				if (graphicsSettings.FrameGenAlgorithm.Current.has_value())
				{
					combobox_FrameGenAlgorithm().SelectedIndex(graphicsSettings.FrameGenAlgorithm.Current.value());
				}
				else if (graphicsSettings.FrameGenAlgorithm.Default.has_value())
				{
					combobox_FrameGenAlgorithm().SelectedIndex(graphicsSettings.FrameGenAlgorithm.Default.value());
				}
			}
			else
			{
				//Enable or disable interface
				combobox_FrameGenAlgorithm().IsEnabled(false);
			}

			//Radeon Boost
			if (graphicsSettings.BoostEnabled.Support.has_value() && graphicsSettings.BoostEnabled.Support.value())
			{
				//Set setting
				if (graphicsSettings.BoostEnabled.Current.has_value())
				{
					toggleswitch_RadeonBoost().IsOn(graphicsSettings.BoostEnabled.Current.value());
					slider_RadeonBoost_MinResolution().IsEnabled(graphicsSettings.BoostEnabled.Current.value());
				}
				else if (graphicsSettings.BoostEnabled.Default.has_value())
				{
					toggleswitch_RadeonBoost().IsOn(graphicsSettings.BoostEnabled.Default.value());
					slider_RadeonBoost_MinResolution().IsEnabled(graphicsSettings.BoostEnabled.Default.value());
				}

				//Enable or disable interface
				toggleswitch_RadeonBoost().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				toggleswitch_RadeonBoost().IsEnabled(false);
			}

			//Radeon Boost - Minimum Resolution
			if (graphicsSettings.BoostMinResolution.Support.has_value() && graphicsSettings.BoostMinResolution.Support.value())
			{
				//Set setting
				if (graphicsSettings.BoostMinResolution.Current.has_value())
				{
					slider_RadeonBoost_MinResolution().Value(graphicsSettings.BoostMinResolution.Current.value());
				}
				else if (graphicsSettings.BoostMinResolution.Default.has_value())
				{
					slider_RadeonBoost_MinResolution().Value(graphicsSettings.BoostMinResolution.Default.value());
				}

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
				//Enable or disable interface
				slider_RadeonBoost_MinResolution().IsEnabled(false);
			}

			//Radeon Frame Rate Target Control
			if (graphicsSettings.FrtcEnabled.Support.has_value() && graphicsSettings.FrtcEnabled.Support.value())
			{
				//Set setting
				if (graphicsSettings.FrtcEnabled.Current.has_value())
				{
					toggleswitch_Frtc().IsOn(graphicsSettings.FrtcEnabled.Current.value());
					slider_Frtc_FrameRateTarget().IsEnabled(graphicsSettings.FrtcEnabled.Current.value());
				}
				else if (graphicsSettings.FrtcEnabled.Default.has_value())
				{
					toggleswitch_Frtc().IsOn(graphicsSettings.FrtcEnabled.Default.value());
					slider_Frtc_FrameRateTarget().IsEnabled(graphicsSettings.FrtcEnabled.Default.value());
				}

				//Enable or disable interface
				toggleswitch_Frtc().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				toggleswitch_Frtc().IsEnabled(false);
			}

			//Radeon Frame Rate Target Control - Maximum Frame Rate
			if (graphicsSettings.FrtcFrameRateTarget.Support.has_value() && graphicsSettings.FrtcFrameRateTarget.Support.value())
			{
				//Set setting
				if (graphicsSettings.FrtcFrameRateTarget.Current.has_value())
				{
					slider_Frtc_FrameRateTarget().Value(graphicsSettings.FrtcFrameRateTarget.Current.value());
				}
				else if (graphicsSettings.FrtcFrameRateTarget.Default.has_value())
				{
					slider_Frtc_FrameRateTarget().Value(graphicsSettings.FrtcFrameRateTarget.Default.value());
				}

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
				//Enable or disable interface
				slider_Frtc_FrameRateTarget().IsEnabled(false);
			}

			//Radeon Chill
			if (graphicsSettings.ChillEnabled.Support.has_value() && graphicsSettings.ChillEnabled.Support.value())
			{
				//Set setting
				bool chillEnabled = false;
				if (graphicsSettings.ChillEnabled.Current.has_value())
				{
					chillEnabled = graphicsSettings.ChillEnabled.Current.value();
					toggleswitch_RadeonChill().IsOn(chillEnabled);
					slider_RadeonChill_Min().IsEnabled(chillEnabled);
					slider_RadeonChill_Max().IsEnabled(chillEnabled);
					button_RadeonChill_Link().IsEnabled(chillEnabled);
				}
				else if (graphicsSettings.ChillEnabled.Default.has_value())
				{
					chillEnabled = graphicsSettings.ChillEnabled.Default.value();
					toggleswitch_RadeonChill().IsOn(chillEnabled);
					slider_RadeonChill_Min().IsEnabled(chillEnabled);
					slider_RadeonChill_Max().IsEnabled(chillEnabled);
					button_RadeonChill_Link().IsEnabled(chillEnabled);
				}

				//Check Radeon Chill Link
				if (chillEnabled && radeon_Chill_Linked)
				{
					slider_RadeonChill_Min().IsEnabled(false);
				}

				//Enable or disable interface
				toggleswitch_RadeonChill().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				toggleswitch_RadeonChill().IsEnabled(false);
			}

			//Radeon Chill - Minimum Frame Rate
			if (graphicsSettings.ChillMinFps.Support.has_value() && graphicsSettings.ChillMinFps.Support.value())
			{
				//Set setting
				if (graphicsSettings.ChillMinFps.Current.has_value())
				{
					slider_RadeonChill_Min().Value(graphicsSettings.ChillMinFps.Current.value());
				}
				else if (graphicsSettings.ChillMinFps.Default.has_value())
				{
					slider_RadeonChill_Min().Value(graphicsSettings.ChillMinFps.Default.value());
				}

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
				//Enable or disable interface
				slider_RadeonChill_Min().IsEnabled(false);
			}

			//Radeon Chill - Maximum Frame Rate
			if (graphicsSettings.ChillMaxFps.Support.has_value() && graphicsSettings.ChillMaxFps.Support.value())
			{
				//Set setting
				if (graphicsSettings.ChillMaxFps.Current.has_value())
				{
					slider_RadeonChill_Max().Value(graphicsSettings.ChillMaxFps.Current.value());
				}
				else if (graphicsSettings.ChillMaxFps.Default.has_value())
				{
					slider_RadeonChill_Max().Value(graphicsSettings.ChillMaxFps.Default.value());
				}

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
				//Enable or disable interface
				slider_RadeonChill_Max().IsEnabled(false);
			}

			//Radeon Image Sharpening 1
			if (graphicsSettings.RisEnabled.Support.has_value() && graphicsSettings.RisEnabled.Support.value())
			{
				//Set setting
				if (graphicsSettings.RisEnabled.Current.has_value())
				{
					toggleswitch_RadeonImageSharpening1().IsOn(graphicsSettings.RisEnabled.Current.value());
					slider_RadeonImageSharpening1_Sharpening().IsEnabled(graphicsSettings.RisEnabled.Current.value());
				}
				else if (graphicsSettings.RisEnabled.Default.has_value())
				{
					toggleswitch_RadeonImageSharpening1().IsOn(graphicsSettings.RisEnabled.Default.value());
					slider_RadeonImageSharpening1_Sharpening().IsEnabled(graphicsSettings.RisEnabled.Default.value());
				}

				//Enable or disable interface
				toggleswitch_RadeonImageSharpening1().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				toggleswitch_RadeonImageSharpening1().IsEnabled(false);
			}

			//Radeon Image Sharpening 1 - Sharpening Degree
			if (graphicsSettings.RisSharpeningDegree.Support.has_value() && graphicsSettings.RisSharpeningDegree.Support.value())
			{
				//Set setting
				if (graphicsSettings.RisSharpeningDegree.Current.has_value())
				{
					slider_RadeonImageSharpening1_Sharpening().Value(graphicsSettings.RisSharpeningDegree.Current.value());
				}
				else if (graphicsSettings.RisSharpeningDegree.Default.has_value())
				{
					slider_RadeonImageSharpening1_Sharpening().Value(graphicsSettings.RisSharpeningDegree.Default.value());
				}

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
				//Enable or disable interface
				slider_RadeonImageSharpening1_Sharpening().IsEnabled(false);
			}

			//Radeon Image Sharpening 2
			if (graphicsSettings.Ris2Enabled.Support.has_value() && graphicsSettings.Ris2Enabled.Support.value())
			{
				//Set setting
				if (graphicsSettings.Ris2Enabled.Current.has_value())
				{
					toggleswitch_RadeonImageSharpening2().IsOn(graphicsSettings.Ris2Enabled.Current.value());
					toggleswitch_RadeonImageSharpening2_Desktop().IsEnabled(graphicsSettings.Ris2Enabled.Current.value());
					slider_RadeonImageSharpening2_Sharpening().IsEnabled(graphicsSettings.Ris2Enabled.Current.value());
				}
				else if (graphicsSettings.Ris2Enabled.Default.has_value())
				{
					toggleswitch_RadeonImageSharpening2().IsOn(graphicsSettings.Ris2Enabled.Default.value());
					toggleswitch_RadeonImageSharpening2_Desktop().IsEnabled(graphicsSettings.Ris2Enabled.Default.value());
					slider_RadeonImageSharpening2_Sharpening().IsEnabled(graphicsSettings.Ris2Enabled.Default.value());
				}

				//Enable or disable interface
				toggleswitch_RadeonImageSharpening2().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				toggleswitch_RadeonImageSharpening2().IsEnabled(false);
			}

			//Radeon Image Sharpening 2 - Sharpen Desktop
			if (graphicsSettings.Ris2DesktopEnabled.Support.has_value() && graphicsSettings.Ris2DesktopEnabled.Support.value())
			{
				//Set setting
				if (graphicsSettings.Ris2DesktopEnabled.Current.has_value())
				{
					toggleswitch_RadeonImageSharpening2_Desktop().IsOn(graphicsSettings.Ris2DesktopEnabled.Current.value());
				}
				else if (graphicsSettings.Ris2DesktopEnabled.Default.has_value())
				{
					toggleswitch_RadeonImageSharpening2_Desktop().IsOn(graphicsSettings.Ris2DesktopEnabled.Default.value());
				}
			}
			else
			{
				//Enable or disable interface
				toggleswitch_RadeonImageSharpening2_Desktop().IsEnabled(false);
			}

			//Radeon Image Sharpening 2 - Sharpening Degree
			if (graphicsSettings.Ris2SharpeningDegree.Support.has_value() && graphicsSettings.Ris2SharpeningDegree.Support.value())
			{
				//Set setting
				if (graphicsSettings.Ris2SharpeningDegree.Current.has_value())
				{
					slider_RadeonImageSharpening2_Sharpening().Value(graphicsSettings.Ris2SharpeningDegree.Current.value());
				}
				else if (graphicsSettings.Ris2SharpeningDegree.Default.has_value())
				{
					slider_RadeonImageSharpening2_Sharpening().Value(graphicsSettings.Ris2SharpeningDegree.Default.value());
				}

				//Set interface
				if (graphicsSettings.Ris2SharpeningDegree.Minimum.has_value())
				{
					slider_RadeonImageSharpening2_Sharpening().Minimum(graphicsSettings.Ris2SharpeningDegree.Minimum.value());
					slider_RadeonImageSharpening2_Sharpening().Maximum(graphicsSettings.Ris2SharpeningDegree.Maximum.value());
					slider_RadeonImageSharpening2_Sharpening().StepFrequency(graphicsSettings.Ris2SharpeningDegree.Step.value());
					slider_RadeonImageSharpening2_Sharpening().SmallChange(graphicsSettings.Ris2SharpeningDegree.Step.value());
				}
			}
			else
			{
				//Enable or disable interface
				slider_RadeonImageSharpening2_Sharpening().IsEnabled(false);
			}

			//Enhanced Sync
			if (graphicsSettings.EnhancedSync.Support.has_value() && graphicsSettings.EnhancedSync.Support.value())
			{
				//Set setting
				if (graphicsSettings.EnhancedSync.Current.has_value())
				{
					toggleswitch_RadeonEnhancedSync().IsOn(graphicsSettings.EnhancedSync.Current.value());
				}
				else if (graphicsSettings.EnhancedSync.Default.has_value())
				{
					toggleswitch_RadeonEnhancedSync().IsOn(graphicsSettings.EnhancedSync.Default.value());
				}

				//Enable or disable interface
				toggleswitch_RadeonEnhancedSync().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				toggleswitch_RadeonEnhancedSync().IsEnabled(false);
			}

			//Vertical Sync
			if (graphicsSettings.VerticalSync.Support.has_value() && graphicsSettings.VerticalSync.Support.value())
			{
				//Set setting
				if (graphicsSettings.VerticalSync.Current.has_value())
				{
					combobox_VerticalSync().SelectedIndex(graphicsSettings.VerticalSync.Current.value());
				}
				else if (graphicsSettings.VerticalSync.Default.has_value())
				{
					combobox_VerticalSync().SelectedIndex(graphicsSettings.VerticalSync.Default.value());
				}

				//Enable or disable interface
				combobox_VerticalSync().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				combobox_VerticalSync().IsEnabled(false);
			}

			//Anti-Aliasing Override
			if (graphicsSettings.AntiAliasingOverride.Support.has_value() && graphicsSettings.AntiAliasingOverride.Support.value())
			{
				//Set setting
				if (graphicsSettings.AntiAliasingOverride.Current.has_value())
				{
					toggleswitch_AntiAliasingOverride().IsOn(graphicsSettings.AntiAliasingOverride.Current.value());
					combobox_AntiAliasingMethod().IsEnabled(graphicsSettings.AntiAliasingOverride.Current.value());
					combobox_AntiAliasingLevel().IsEnabled(graphicsSettings.AntiAliasingOverride.Current.value());
					toggleswitch_AntiAliasingEnhancedQuality().IsEnabled(graphicsSettings.AntiAliasingOverride.Current.value());
				}
				else if (graphicsSettings.AntiAliasingOverride.Default.has_value())
				{
					toggleswitch_AntiAliasingOverride().IsOn(graphicsSettings.AntiAliasingOverride.Default.value());
					combobox_AntiAliasingMethod().IsEnabled(graphicsSettings.AntiAliasingOverride.Default.value());
					combobox_AntiAliasingLevel().IsEnabled(graphicsSettings.AntiAliasingOverride.Default.value());
					toggleswitch_AntiAliasingEnhancedQuality().IsEnabled(graphicsSettings.AntiAliasingOverride.Default.value());
				}

				//Enable or disable interface
				toggleswitch_AntiAliasingOverride().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				toggleswitch_AntiAliasingOverride().IsEnabled(false);
			}

			//Anti-Aliasing Method
			if (graphicsSettings.AntiAliasingMethod.Support.has_value() && graphicsSettings.AntiAliasingMethod.Support.value())
			{
				//Set setting
				if (graphicsSettings.AntiAliasingMethod.Current.has_value())
				{
					combobox_AntiAliasingMethod().SelectedIndex(graphicsSettings.AntiAliasingMethod.Current.value());
				}
				else if (graphicsSettings.AntiAliasingMethod.Default.has_value())
				{
					combobox_AntiAliasingMethod().SelectedIndex(graphicsSettings.AntiAliasingMethod.Default.value());
				}
			}
			else
			{
				//Enable or disable interface
				combobox_AntiAliasingMethod().IsEnabled(false);
			}

			//Anti-Aliasing Level
			if (graphicsSettings.AntiAliasingLevel.Support.has_value() && graphicsSettings.AntiAliasingLevel.Support.value())
			{
				//Set setting
				if (graphicsSettings.AntiAliasingLevel.Current.has_value())
				{
					combobox_AntiAliasingLevel().SelectedIndex(graphicsSettings.AntiAliasingLevel.Current.value());
				}
				else if (graphicsSettings.AntiAliasingLevel.Default.has_value())
				{
					combobox_AntiAliasingLevel().SelectedIndex(graphicsSettings.AntiAliasingLevel.Default.value());
				}
			}
			else
			{
				//Enable or disable interface
				combobox_AntiAliasingLevel().IsEnabled(false);
			}

			//Enhanced Quality Anti-Aliasing
			if (graphicsSettings.AntiAliasingEnhancedQuality.Support.has_value() && graphicsSettings.AntiAliasingEnhancedQuality.Support.value())
			{
				//Set setting
				if (graphicsSettings.AntiAliasingEnhancedQuality.Current.has_value())
				{
					toggleswitch_AntiAliasingEnhancedQuality().IsOn(graphicsSettings.AntiAliasingEnhancedQuality.Current.value());
				}
				else if (graphicsSettings.AntiAliasingEnhancedQuality.Default.has_value())
				{
					toggleswitch_AntiAliasingEnhancedQuality().IsOn(graphicsSettings.AntiAliasingEnhancedQuality.Default.value());
				}
			}
			else
			{
				//Enable or disable interface
				toggleswitch_AntiAliasingEnhancedQuality().IsEnabled(false);
			}

			//Morphological Anti-Aliasing
			if (graphicsSettings.AntiAliasingMorphological.Support.has_value() && graphicsSettings.AntiAliasingMorphological.Support.value())
			{
				//Set setting
				if (graphicsSettings.AntiAliasingMorphological.Current.has_value())
				{
					toggleswitch_MorphologicalAntiAliasing().IsOn(graphicsSettings.AntiAliasingMorphological.Current.value());
				}
				else if (graphicsSettings.AntiAliasingMorphological.Default.has_value())
				{
					toggleswitch_MorphologicalAntiAliasing().IsOn(graphicsSettings.AntiAliasingMorphological.Default.value());
				}

				//Enable or disable interface
				toggleswitch_MorphologicalAntiAliasing().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				toggleswitch_MorphologicalAntiAliasing().IsEnabled(false);
			}

			//Anisotropic Texture Filtering Override
			if (graphicsSettings.AnisotropicOverride.Support.has_value() && graphicsSettings.AnisotropicOverride.Support.value())
			{
				//Set setting
				if (graphicsSettings.AnisotropicOverride.Current.has_value())
				{
					combobox_AnisotropicTextureFiltering().SelectedIndex(graphicsSettings.AnisotropicOverride.Current.value());
				}
				else if (graphicsSettings.AnisotropicOverride.Default.has_value())
				{
					combobox_AnisotropicTextureFiltering().SelectedIndex(graphicsSettings.AnisotropicOverride.Default.value());
				}

				//Enable or disable interface
				combobox_AnisotropicTextureFiltering().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				combobox_AnisotropicTextureFiltering().IsEnabled(false);
			}

			//Texture Filtering Quality
			if (graphicsSettings.TextureFilteringQuality.Support.has_value() && graphicsSettings.TextureFilteringQuality.Support.value())
			{
				//Set setting
				if (graphicsSettings.TextureFilteringQuality.Current.has_value())
				{
					combobox_TextureFilteringQuality().SelectedIndex(graphicsSettings.TextureFilteringQuality.Current.value());
				}
				else if (graphicsSettings.TextureFilteringQuality.Default.has_value())
				{
					combobox_TextureFilteringQuality().SelectedIndex(graphicsSettings.TextureFilteringQuality.Default.value());
				}

				//Enable or disable interface
				combobox_TextureFilteringQuality().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				combobox_TextureFilteringQuality().IsEnabled(false);
			}

			//Surface Format Optimization
			if (graphicsSettings.SurfaceFormatOptimization.Support.has_value() && graphicsSettings.SurfaceFormatOptimization.Support.value())
			{
				//Set setting
				if (graphicsSettings.SurfaceFormatOptimization.Current.has_value())
				{
					toggleswitch_SurfaceFormatOptimization().IsOn(graphicsSettings.SurfaceFormatOptimization.Current.value());
				}
				else if (graphicsSettings.SurfaceFormatOptimization.Default.has_value())
				{
					toggleswitch_SurfaceFormatOptimization().IsOn(graphicsSettings.SurfaceFormatOptimization.Default.value());
				}

				//Enable or disable interface
				toggleswitch_SurfaceFormatOptimization().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				toggleswitch_SurfaceFormatOptimization().IsEnabled(false);
			}

			//Tessellation Mode
			if (graphicsSettings.TessellationMode.Support.has_value() && graphicsSettings.TessellationMode.Support.value())
			{
				//Set setting
				if (graphicsSettings.TessellationMode.Current.has_value())
				{
					combobox_Tessellation_Mode().SelectedIndex(graphicsSettings.TessellationMode.Current.value());
					combobox_Tessellation_Level().IsEnabled(graphicsSettings.TessellationMode.Current.value());
				}
				else if (graphicsSettings.TessellationMode.Default.has_value())
				{
					combobox_Tessellation_Mode().SelectedIndex(graphicsSettings.TessellationMode.Default.value());
					combobox_Tessellation_Level().IsEnabled(graphicsSettings.TessellationMode.Default.value());
				}

				//Enable or disable interface
				combobox_Tessellation_Mode().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				combobox_Tessellation_Mode().IsEnabled(false);
			}

			//Tessellation Level
			if (graphicsSettings.TessellationLevel.Support.has_value() && graphicsSettings.TessellationLevel.Support.value())
			{
				//Set setting
				if (graphicsSettings.TessellationLevel.Current.has_value())
				{
					combobox_Tessellation_Level().SelectedIndex(graphicsSettings.TessellationLevel.Current.value());
				}
				else if (graphicsSettings.TessellationLevel.Default.has_value())
				{
					combobox_Tessellation_Level().SelectedIndex(graphicsSettings.TessellationLevel.Default.value());
				}
			}
			else
			{
				//Enable or disable interface
				combobox_Tessellation_Level().IsEnabled(false);
			}

			//OpenGL Triple Buffering
			if (graphicsSettings.OpenGLTripleBuffering.Support.has_value() && graphicsSettings.OpenGLTripleBuffering.Support.value())
			{
				//Set setting
				if (graphicsSettings.OpenGLTripleBuffering.Current.has_value())
				{
					toggleswitch_OpenGLTripleBuffering().IsOn(graphicsSettings.OpenGLTripleBuffering.Current.value());
				}
				else if (graphicsSettings.OpenGLTripleBuffering.Default.has_value())
				{
					toggleswitch_OpenGLTripleBuffering().IsOn(graphicsSettings.OpenGLTripleBuffering.Default.value());
				}

				//Enable or disable interface
				toggleswitch_OpenGLTripleBuffering().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				toggleswitch_OpenGLTripleBuffering().IsEnabled(false);
			}

			//OpenGL 10-Bit Pixel Format
			if (graphicsSettings.OpenGL10BitPixelFormat.Support.has_value() && graphicsSettings.OpenGL10BitPixelFormat.Support.value())
			{
				//Set setting
				if (graphicsSettings.OpenGL10BitPixelFormat.Current.has_value())
				{
					toggleswitch_OpenGL10BitPixelFormat().IsOn(graphicsSettings.OpenGL10BitPixelFormat.Current.value());
				}
				else if (graphicsSettings.OpenGL10BitPixelFormat.Default.has_value())
				{
					toggleswitch_OpenGL10BitPixelFormat().IsOn(graphicsSettings.OpenGL10BitPixelFormat.Default.value());
				}

				//Enable or disable interface
				toggleswitch_OpenGL10BitPixelFormat().IsEnabled(true);
			}
			else
			{
				//Enable or disable interface
				toggleswitch_OpenGL10BitPixelFormat().IsEnabled(false);
			}

			//Return result
			AVDebugWriteLine(L"Graphics settings applied to interface.");
			return true;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine(L"Failed applying graphics settings to interface.");
			return false;
		}
	}
}