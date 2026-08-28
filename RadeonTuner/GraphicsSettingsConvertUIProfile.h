#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::GraphicsSettings_Convert_ToUI_Profile(GraphicsSettings graphicsSettings, AdlSettingGet settingType)
	{
		try
		{
			//FSR Upscaling Override
			if (graphicsSettings.FsrOverride.Get(settingType).has_value())
			{
				toggleswitch_FsrOverrideUpscaling().IsOn(graphicsSettings.FsrOverride.Get(settingType).value());
			}

			//FSR Frame Generation Override
			if (graphicsSettings.MlfiOverride.Get(settingType).has_value())
			{
				toggleswitch_FsrOverrideFrameGeneration().IsOn(graphicsSettings.MlfiOverride.Get(settingType).value());
			}

			//FSR Multi Frame Generation Override
			if (graphicsSettings.MfgOverride.Get(settingType).has_value())
			{
				toggleswitch_FsrOverrideMultiFrameGeneration().IsOn(graphicsSettings.MfgOverride.Get(settingType).value());
			}

			//FSR Ray Regeneration Denoiser Override
			if (graphicsSettings.MldOverride.Get(settingType).has_value())
			{
				toggleswitch_FsrOverrideRayRegeneration().IsOn(graphicsSettings.MldOverride.Get(settingType).value());
			}

			//FSR Neural Radiance Caching Override
			if (graphicsSettings.NrcOverride.Get(settingType).has_value())
			{
				toggleswitch_FsrOverrideNeuralRadianceCaching().IsOn(graphicsSettings.NrcOverride.Get(settingType).value());
			}

			//FSR Multi Frame Generation Ratio
			if (graphicsSettings.MfgRatio.Get(settingType).has_value())
			{
				combobox_FsrMultiFrameGenerationRatio().SelectedIndex(graphicsSettings.MfgRatio.Get(settingType).value());
			}

			//FSR Override Library
			if (graphicsSettings.FsrOvrDLLPath.Get(settingType).has_value())
			{
				textbox_FsrDllLoadPath().Text(graphicsSettings.FsrOvrDLLPath.Get(settingType).value());
			}

			//FSR Over-The-Air Updates
			if (graphicsSettings.FsrOtaIndex.Get(settingType).has_value())
			{
				combobox_FsrOtaUpdates().SelectedIndex(graphicsSettings.FsrOtaIndex.Get(settingType).value());
			}

			//FSR Latency Reduction
			if (graphicsSettings.DeLagEnabled.Get(settingType).has_value())
			{
				toggleswitch_FsrLatencyReduction().IsOn(graphicsSettings.DeLagEnabled.Get(settingType).value());
			}

			//Radeon Fluid Motion Frames
			if (graphicsSettings.FrameGenEnabled.Get(settingType).has_value())
			{
				toggleswitch_FrameGenEnabled().IsOn(graphicsSettings.FrameGenEnabled.Get(settingType).value());
				combobox_FrameGenSearchMode().IsEnabled(graphicsSettings.FrameGenEnabled.Get(settingType).value());
				combobox_FrameGenPerfMode().IsEnabled(graphicsSettings.FrameGenEnabled.Get(settingType).value());
				combobox_FrameGenResponseMode().IsEnabled(graphicsSettings.FrameGenEnabled.Get(settingType).value());
				combobox_FrameGenAlgorithm().IsEnabled(graphicsSettings.FrameGenEnabled.Get(settingType).value());
			}

			//Radeon Fluid Motion Frames - Search Mode
			if (graphicsSettings.FrameGenSearchMode.Get(settingType).has_value())
			{
				combobox_FrameGenSearchMode().SelectedIndex(graphicsSettings.FrameGenSearchMode.Get(settingType).value());
			}

			//Radeon Fluid Motion Frames - Performance Mode
			if (graphicsSettings.FrameGenPerfMode.Get(settingType).has_value())
			{
				combobox_FrameGenPerfMode().SelectedIndex(graphicsSettings.FrameGenPerfMode.Get(settingType).value());
			}

			//Radeon Fluid Motion Frames - Response Mode
			if (graphicsSettings.FrameGenResponseMode.Get(settingType).has_value())
			{
				combobox_FrameGenResponseMode().SelectedIndex(graphicsSettings.FrameGenResponseMode.Get(settingType).value());
			}

			//Radeon Fluid Motion Frames - Algorithm
			if (graphicsSettings.FrameGenAlgorithm.Get(settingType).has_value())
			{
				combobox_FrameGenAlgorithm().SelectedIndex(graphicsSettings.FrameGenAlgorithm.Get(settingType).value());
			}

			//Radeon Boost
			if (graphicsSettings.BoostMode.Get(settingType).has_value())
			{
				combobox_RadeonBoost().SelectedIndex(graphicsSettings.BoostMode.Get(settingType).value());
				slider_RadeonBoost_MinResolution().IsEnabled(graphicsSettings.BoostMode.Get(settingType).value());
			}

			//Radeon Boost - Minimum Resolution
			if (graphicsSettings.BoostMinResolution.Get(settingType).has_value())
			{
				slider_RadeonBoost_MinResolution().Value(graphicsSettings.BoostMinResolution.Get(settingType).value());
			}

			//Radeon Frame Rate Target Control - Enabled
			if (graphicsSettings.FrtcEnabled.Get(settingType).has_value())
			{
				toggleswitch_Frtc().IsOn(graphicsSettings.FrtcEnabled.Get(settingType).value());
				slider_Frtc_FrameRateTarget().IsEnabled(graphicsSettings.FrtcEnabled.Get(settingType).value());
			}

			//Radeon Frame Rate Target Control - Maximum Frame Rate
			if (graphicsSettings.FrtcFrameRateTarget.Get(settingType).has_value())
			{
				slider_Frtc_FrameRateTarget().Value(graphicsSettings.FrtcFrameRateTarget.Get(settingType).value());
			}

			//Radeon Chill
			if (graphicsSettings.ChillEnabled.Get(settingType).has_value())
			{
				toggleswitch_RadeonChill().IsOn(graphicsSettings.ChillEnabled.Get(settingType).value());
				slider_RadeonChill_Max().IsEnabled(graphicsSettings.ChillEnabled.Get(settingType).value());
				button_RadeonChill_Link().IsEnabled(graphicsSettings.ChillEnabled.Get(settingType).value());

				//Check Radeon Chill Link
				if (radeon_Chill_Linked)
				{
					slider_RadeonChill_Min().IsEnabled(false);
				}
				else
				{
					slider_RadeonChill_Min().IsEnabled(graphicsSettings.ChillEnabled.Get(settingType).value());
				}
			}

			//Radeon Chill - Minimum Frame Rate
			if (graphicsSettings.ChillMinFps.Get(settingType).has_value())
			{
				slider_RadeonChill_Min().Value(graphicsSettings.ChillMinFps.Get(settingType).value());
			}

			//Radeon Chill - Maximum Frame Rate
			if (graphicsSettings.ChillMaxFps.Get(settingType).has_value())
			{
				slider_RadeonChill_Max().Value(graphicsSettings.ChillMaxFps.Get(settingType).value());
			}

			//Radeon Image Sharpening - Enabled
			if (graphicsSettings.RisEnabled.Get(settingType).has_value())
			{
				if (graphicsSettings.RisVersion.Version <= 1)
				{
					toggleswitch_RadeonImageSharpening1().IsOn(graphicsSettings.RisEnabled.Get(settingType).value());
					slider_RadeonImageSharpening1_Sharpening().IsEnabled(graphicsSettings.RisEnabled.Get(settingType).value());
				}
				else
				{
					toggleswitch_RadeonImageSharpening2().IsOn(graphicsSettings.RisEnabled.Get(settingType).value());
					if (graphicsSettings.RisEnabled.Get(settingType).value())
					{
						toggleswitch_RadeonImageSharpening2_Desktop().IsEnabled(graphicsSettings.Global());
						slider_RadeonImageSharpening2_Sharpening().IsEnabled(true);
					}
					else
					{
						toggleswitch_RadeonImageSharpening2_Desktop().IsEnabled(false);
						slider_RadeonImageSharpening2_Sharpening().IsEnabled(false);
					}
				}
			}

			//Radeon Image Sharpening - Sharpen Desktop
			if (graphicsSettings.RisDesktopEnabled.Get(settingType).has_value())
			{
				toggleswitch_RadeonImageSharpening2_Desktop().IsOn(graphicsSettings.RisDesktopEnabled.Get(settingType).value());
			}

			//Radeon Image Sharpening - Sharpening Degree
			if (graphicsSettings.RisSharpeningDegree.Get(settingType).has_value())
			{
				if (graphicsSettings.RisVersion.Version <= 1)
				{
					slider_RadeonImageSharpening1_Sharpening().Value(graphicsSettings.RisSharpeningDegree.Get(settingType).value());
				}
				else
				{
					slider_RadeonImageSharpening2_Sharpening().Value(graphicsSettings.RisSharpeningDegree.Get(settingType).value());
				}
			}

			//Enhanced Sync
			if (graphicsSettings.EnhancedSync.Get(settingType).has_value())
			{
				toggleswitch_RadeonEnhancedSync().IsOn(graphicsSettings.EnhancedSync.Get(settingType).value());
			}

			//Vertical Sync
			if (graphicsSettings.VerticalSync.Get(settingType).has_value())
			{
				combobox_VerticalSync().SelectedIndex(graphicsSettings.VerticalSync.Get(settingType).value());
			}

			//Anti-Aliasing Override
			if (graphicsSettings.AntiAliasingOverride.Get(settingType).has_value())
			{
				toggleswitch_AntiAliasingOverride().IsOn(graphicsSettings.AntiAliasingOverride.Get(settingType).value());
				combobox_AntiAliasingMethod().IsEnabled(graphicsSettings.AntiAliasingOverride.Get(settingType).value());
				combobox_AntiAliasingLevel().IsEnabled(graphicsSettings.AntiAliasingOverride.Get(settingType).value());
				toggleswitch_AntiAliasingEnhancedQuality().IsEnabled(graphicsSettings.AntiAliasingOverride.Get(settingType).value());
			}

			//Anti-Aliasing Method
			if (graphicsSettings.AntiAliasingMethod.Get(settingType).has_value())
			{
				combobox_AntiAliasingMethod().SelectedIndex(graphicsSettings.AntiAliasingMethod.Get(settingType).value());
			}

			//Anti-Aliasing Level
			if (graphicsSettings.AntiAliasingLevel.Get(settingType).has_value())
			{
				combobox_AntiAliasingLevel().SelectedIndex(graphicsSettings.AntiAliasingLevel.Get(settingType).value());
			}

			//Enhanced Quality Anti-Aliasing
			if (graphicsSettings.AntiAliasingEnhancedQuality.Get(settingType).has_value())
			{
				toggleswitch_AntiAliasingEnhancedQuality().IsOn(graphicsSettings.AntiAliasingEnhancedQuality.Get(settingType).value());
			}

			//Morphological Anti-Aliasing
			if (graphicsSettings.AntiAliasingMorphological.Get(settingType).has_value())
			{
				toggleswitch_MorphologicalAntiAliasing().IsOn(graphicsSettings.AntiAliasingMorphological.Get(settingType).value());
			}

			//Anisotropic Texture Filtering Override
			if (graphicsSettings.AnisotropicOverride.Get(settingType).has_value())
			{
				combobox_AnisotropicTextureFiltering().SelectedIndex(graphicsSettings.AnisotropicOverride.Get(settingType).value());
			}

			//Texture Filtering Quality
			if (graphicsSettings.TextureFilteringQuality.Get(settingType).has_value())
			{
				combobox_TextureFilteringQuality().SelectedIndex(graphicsSettings.TextureFilteringQuality.Get(settingType).value());
			}

			//Surface Format Optimization
			if (graphicsSettings.SurfaceFormatOptimization.Get(settingType).has_value())
			{
				toggleswitch_SurfaceFormatOptimization().IsOn(graphicsSettings.SurfaceFormatOptimization.Get(settingType).value());
			}

			//Tessellation Mode
			if (graphicsSettings.TessellationMode.Get(settingType).has_value())
			{
				combobox_Tessellation_Mode().SelectedIndex(graphicsSettings.TessellationMode.Get(settingType).value());

				bool subSettingEnabled = graphicsSettings.TessellationMode.Get(settingType).value() == 2;
				combobox_Tessellation_Level().IsEnabled(subSettingEnabled);
			}

			//Tessellation Level
			if (graphicsSettings.TessellationLevel.Get(settingType).has_value())
			{
				combobox_Tessellation_Level().SelectedIndex(graphicsSettings.TessellationLevel.Get(settingType).value());
			}

			//OpenGL Triple Buffering
			if (graphicsSettings.OpenGLTripleBuffering.Get(settingType).has_value())
			{
				toggleswitch_OpenGLTripleBuffering().IsOn(graphicsSettings.OpenGLTripleBuffering.Get(settingType).value());
			}

			//OpenGL 10-Bit Pixel Format
			if (graphicsSettings.OpenGL10BitPixelFormat.Get(settingType).has_value())
			{
				toggleswitch_OpenGL10BitPixelFormat().IsOn(graphicsSettings.OpenGL10BitPixelFormat.Get(settingType).value());
			}

			//Return result
			AVDebugWriteLine(L"Graphics settings applied to interface (Profile)");
			return true;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine(L"Failed applying graphics settings to interface (Profile)");
			return false;
		}
	}
}