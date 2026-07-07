#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::GraphicsSettings_Convert_ToUI_Current(GraphicsSettings graphicsSettings)
	{
		try
		{
			//FSR Upscaling Override
			if (graphicsSettings.FsrOverride.Current.has_value())
			{
				toggleswitch_FsrOverrideUpscaling().IsOn(graphicsSettings.FsrOverride.Current.value());
			}

			//FSR Frame Generation Override
			if (graphicsSettings.MlfiOverride.Current.has_value())
			{
				toggleswitch_FsrOverrideFrameGeneration().IsOn(graphicsSettings.MlfiOverride.Current.value());
			}

			//FSR Multi Frame Generation Override
			if (graphicsSettings.MfgOverride.Current.has_value())
			{
				toggleswitch_FsrOverrideMultiFrameGeneration().IsOn(graphicsSettings.MfgOverride.Current.value());
			}

			//FSR Ray Regeneration Denoiser Override
			if (graphicsSettings.MldOverride.Current.has_value())
			{
				toggleswitch_FsrOverrideRayRegeneration().IsOn(graphicsSettings.MldOverride.Current.value());
			}

			//FSR Neural Radiance Caching Override
			if (graphicsSettings.NrcOverride.Current.has_value())
			{
				toggleswitch_FsrOverrideNeuralRadianceCaching().IsOn(graphicsSettings.NrcOverride.Current.value());
			}

			//FSR Multi Frame Generation Ratio
			if (graphicsSettings.MfgRatio.Current.has_value())
			{
				combobox_MultiFrameGenerationRatio().SelectedIndex(graphicsSettings.MfgRatio.Current.value());
			}

			//FSR Override Library
			if (graphicsSettings.FsrOvrDLLPath.Current.has_value())
			{
				textbox_FsrDllLoadPath().Text(graphicsSettings.FsrOvrDLLPath.Current.value());
			}

			//FSR Over-The-Air Updates
			if (graphicsSettings.FsrOtaIndex.Current.has_value())
			{
				combobox_FsrOtaUpdates().SelectedIndex(graphicsSettings.FsrOtaIndex.Current.value());
			}

			//FSR Latency Reduction
			if (graphicsSettings.DeLagEnabled.Current.has_value())
			{
				toggleswitch_FsrLatencyReduction().IsOn(graphicsSettings.DeLagEnabled.Current.value());
			}

			//Radeon Fluid Motion Frames
			if (graphicsSettings.FrameGenEnabled.Current.has_value())
			{
				toggleswitch_FrameGenEnabled().IsOn(graphicsSettings.FrameGenEnabled.Current.value());
				combobox_FrameGenSearchMode().IsEnabled(graphicsSettings.FrameGenEnabled.Current.value());
				combobox_FrameGenPerfMode().IsEnabled(graphicsSettings.FrameGenEnabled.Current.value());
				combobox_FrameGenResponseMode().IsEnabled(graphicsSettings.FrameGenEnabled.Current.value());
				combobox_FrameGenAlgorithm().IsEnabled(graphicsSettings.FrameGenEnabled.Current.value());
			}

			//Radeon Fluid Motion Frames - Search Mode
			if (graphicsSettings.FrameGenSearchMode.Current.has_value())
			{
				combobox_FrameGenSearchMode().SelectedIndex(graphicsSettings.FrameGenSearchMode.Current.value());
			}

			//Radeon Fluid Motion Frames - Performance Mode
			if (graphicsSettings.FrameGenPerfMode.Current.has_value())
			{
				combobox_FrameGenPerfMode().SelectedIndex(graphicsSettings.FrameGenPerfMode.Current.value());
			}

			//Radeon Fluid Motion Frames - Response Mode
			if (graphicsSettings.FrameGenResponseMode.Current.has_value())
			{
				combobox_FrameGenResponseMode().SelectedIndex(graphicsSettings.FrameGenResponseMode.Current.value());
			}

			//Radeon Fluid Motion Frames - Algorithm
			if (graphicsSettings.FrameGenAlgorithm.Current.has_value())
			{
				combobox_FrameGenAlgorithm().SelectedIndex(graphicsSettings.FrameGenAlgorithm.Current.value());
			}

			//Radeon Boost
			if (graphicsSettings.BoostEnabled.Current.has_value())
			{
				toggleswitch_RadeonBoost().IsOn(graphicsSettings.BoostEnabled.Current.value());
				slider_RadeonBoost_MinResolution().IsEnabled(graphicsSettings.BoostEnabled.Current.value());
			}

			//Radeon Boost - Minimum Resolution
			if (graphicsSettings.BoostMinResolution.Current.has_value())
			{
				slider_RadeonBoost_MinResolution().Value(graphicsSettings.BoostMinResolution.Current.value());
			}

			//Radeon Frame Rate Target Control - Maximum Frame Rate
			if (graphicsSettings.FrtcFrameRateTarget.Current.has_value())
			{
				//Note: Changing the frame rate will force enable FRTC, set opposite of FRTC to trigger FRTC event.
				if (graphicsSettings.FrtcEnabled.Current.has_value())
				{
					toggleswitch_Frtc().IsOn(!graphicsSettings.FrtcEnabled.Current.value());
				}
				slider_Frtc_FrameRateTarget().Value(graphicsSettings.FrtcFrameRateTarget.Current.value());
			}

			//Radeon Frame Rate Target Control
			if (graphicsSettings.FrtcEnabled.Current.has_value())
			{
				toggleswitch_Frtc().IsOn(graphicsSettings.FrtcEnabled.Current.value());
				slider_Frtc_FrameRateTarget().IsEnabled(graphicsSettings.FrtcEnabled.Current.value());
			}

			//Radeon Chill
			if (graphicsSettings.ChillEnabled.Current.has_value())
			{
				//Disable Radeon Chill Link
				radeon_Chill_Linked = false;

				toggleswitch_RadeonChill().IsOn(graphicsSettings.ChillEnabled.Current.value());
				slider_RadeonChill_Min().IsEnabled(graphicsSettings.ChillEnabled.Current.value());
				slider_RadeonChill_Max().IsEnabled(graphicsSettings.ChillEnabled.Current.value());
				button_RadeonChill_Link().IsEnabled(graphicsSettings.ChillEnabled.Current.value());
			}

			//Radeon Chill - Minimum Frame Rate
			if (graphicsSettings.ChillMinFps.Current.has_value())
			{
				slider_RadeonChill_Min().Value(graphicsSettings.ChillMinFps.Current.value());
			}

			//Radeon Chill - Maximum Frame Rate
			if (graphicsSettings.ChillMaxFps.Current.has_value())
			{
				slider_RadeonChill_Max().Value(graphicsSettings.ChillMaxFps.Current.value());
			}

			//Radeon Image Sharpening 1
			if (graphicsSettings.RisEnabled.Current.has_value())
			{
				toggleswitch_RadeonImageSharpening1().IsOn(graphicsSettings.RisEnabled.Current.value());
				slider_RadeonImageSharpening1_Sharpening().IsEnabled(graphicsSettings.RisEnabled.Current.value());
			}

			//Radeon Image Sharpening 1 - Sharpening Degree
			if (graphicsSettings.RisSharpeningDegree.Current.has_value())
			{
				slider_RadeonImageSharpening1_Sharpening().Value(graphicsSettings.RisSharpeningDegree.Current.value());
			}

			//Radeon Image Sharpening 2
			if (graphicsSettings.Ris2Enabled.Current.has_value())
			{
				toggleswitch_RadeonImageSharpening2().IsOn(graphicsSettings.Ris2Enabled.Current.value());
				toggleswitch_RadeonImageSharpening2_Desktop().IsEnabled(graphicsSettings.Ris2Enabled.Current.value());
				slider_RadeonImageSharpening2_Sharpening().IsEnabled(graphicsSettings.Ris2Enabled.Current.value());
			}

			//Radeon Image Sharpening 2 - Sharpen Desktop
			if (graphicsSettings.Ris2DesktopEnabled.Current.has_value())
			{
				toggleswitch_RadeonImageSharpening2_Desktop().IsOn(graphicsSettings.Ris2DesktopEnabled.Current.value());
			}

			//Radeon Image Sharpening 2 - Sharpening Degree
			if (graphicsSettings.Ris2SharpeningDegree.Current.has_value())
			{
				slider_RadeonImageSharpening2_Sharpening().Value(graphicsSettings.Ris2SharpeningDegree.Current.value());
			}

			//Enhanced Sync
			if (graphicsSettings.EnhancedSync.Current.has_value())
			{
				toggleswitch_RadeonEnhancedSync().IsOn(graphicsSettings.EnhancedSync.Current.value());
			}

			//Vertical Sync
			if (graphicsSettings.VerticalSync.Current.has_value())
			{
				combobox_VerticalSync().SelectedIndex(graphicsSettings.VerticalSync.Current.value());
			}

			//Anti-Aliasing Override
			if (graphicsSettings.AntiAliasingOverride.Current.has_value())
			{
				toggleswitch_AntiAliasingOverride().IsOn(graphicsSettings.AntiAliasingOverride.Current.value());
				combobox_AntiAliasingMethod().IsEnabled(graphicsSettings.AntiAliasingOverride.Current.value());
				combobox_AntiAliasingLevel().IsEnabled(graphicsSettings.AntiAliasingOverride.Current.value());
				toggleswitch_AntiAliasingEnhancedQuality().IsEnabled(graphicsSettings.AntiAliasingOverride.Current.value());
			}

			//Anti-Aliasing Method
			if (graphicsSettings.AntiAliasingMethod.Current.has_value())
			{
				combobox_AntiAliasingMethod().SelectedIndex(graphicsSettings.AntiAliasingMethod.Current.value());
			}

			//Anti-Aliasing Level
			if (graphicsSettings.AntiAliasingLevel.Current.has_value())
			{
				combobox_AntiAliasingLevel().SelectedIndex(graphicsSettings.AntiAliasingLevel.Current.value());
			}

			//Enhanced Quality Anti-Aliasing
			if (graphicsSettings.AntiAliasingEnhancedQuality.Current.has_value())
			{
				toggleswitch_AntiAliasingEnhancedQuality().IsOn(graphicsSettings.AntiAliasingEnhancedQuality.Current.value());
			}

			//Morphological Anti-Aliasing
			if (graphicsSettings.AntiAliasingMorphological.Current.has_value())
			{
				toggleswitch_MorphologicalAntiAliasing().IsOn(graphicsSettings.AntiAliasingMorphological.Current.value());
			}

			//Anisotropic Texture Filtering Override
			if (graphicsSettings.AnisotropicOverride.Current.has_value())
			{
				combobox_AnisotropicTextureFiltering().SelectedIndex(graphicsSettings.AnisotropicOverride.Current.value());
			}

			//Texture Filtering Quality
			if (graphicsSettings.TextureFilteringQuality.Current.has_value())
			{
				combobox_TextureFilteringQuality().SelectedIndex(graphicsSettings.TextureFilteringQuality.Current.value());
			}

			//Surface Format Optimization
			if (graphicsSettings.SurfaceFormatOptimization.Current.has_value())
			{
				toggleswitch_SurfaceFormatOptimization().IsOn(graphicsSettings.SurfaceFormatOptimization.Current.value());
			}

			//Tessellation Mode
			if (graphicsSettings.TessellationMode.Current.has_value())
			{
				combobox_Tessellation_Mode().SelectedIndex(graphicsSettings.TessellationMode.Current.value());
				combobox_Tessellation_Level().IsEnabled(graphicsSettings.TessellationMode.Current.value());
			}

			//Tessellation Level
			if (graphicsSettings.TessellationLevel.Current.has_value())
			{
				combobox_Tessellation_Level().SelectedIndex(graphicsSettings.TessellationLevel.Current.value());
			}

			//OpenGL Triple Buffering
			if (graphicsSettings.OpenGLTripleBuffering.Current.has_value())
			{
				toggleswitch_OpenGLTripleBuffering().IsOn(graphicsSettings.OpenGLTripleBuffering.Current.value());
			}

			//OpenGL 10-Bit Pixel Format
			if (graphicsSettings.OpenGL10BitPixelFormat.Current.has_value())
			{
				toggleswitch_OpenGL10BitPixelFormat().IsOn(graphicsSettings.OpenGL10BitPixelFormat.Current.value());
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