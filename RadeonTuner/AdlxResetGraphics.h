#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::AdlxValuesResetGraphics()
	{
		try
		{
			AVDebugWriteLine("Resetting graphics settings to defaults.");

			//Get current and default settings
			GraphicsSettings graphicsSettings = GraphicsSettings_Generate_FromADLRegistry(adl_Gpu_AdapterIndex).value();

			//FSR Upscaling Override
			if (graphicsSettings.FsrOverride.Default.has_value())
			{
				toggleswitch_FsrOverrideUpscaling().IsOn(graphicsSettings.FsrOverride.Default.value());
			}

			//FSR Frame Generation Override
			if (graphicsSettings.MlfiOverride.Default.has_value())
			{
				toggleswitch_FsrOverrideFrameGeneration().IsOn(graphicsSettings.MlfiOverride.Default.value());
			}

			//FSR Multi Frame Generation Override
			if (graphicsSettings.MfgOverride.Default.has_value())
			{
				toggleswitch_FsrOverrideMultiFrameGeneration().IsOn(graphicsSettings.MfgOverride.Default.value());
			}

			//FSR Ray Regeneration Denoiser Override
			if (graphicsSettings.MldOverride.Default.has_value())
			{
				toggleswitch_FsrOverrideRayRegeneration().IsOn(graphicsSettings.MldOverride.Default.value());
			}

			//FSR Neural Radiance Caching Override
			if (graphicsSettings.NrcOverride.Default.has_value())
			{
				toggleswitch_FsrOverrideNeuralRadianceCaching().IsOn(graphicsSettings.NrcOverride.Default.value());
			}

			//FSR Multi Frame Generation Ratio
			if (graphicsSettings.MfgRatio.Default.has_value())
			{
				combobox_MultiFrameGenerationRatio().SelectedIndex(graphicsSettings.MfgRatio.Default.value());
			}

			//FSR Override Library
			FsrOverrideDllReset();

			//FSR Over-The-Air Updates
			if (graphicsSettings.FsrOtaIndex.Default.has_value())
			{
				combobox_FsrOtaUpdates().SelectedIndex(graphicsSettings.FsrOtaIndex.Default.value());
			}

			//FSR Latency Reduction
			if (graphicsSettings.DeLagEnabled.Default.has_value())
			{
				toggleswitch_FsrLatencyReduction().IsOn(graphicsSettings.DeLagEnabled.Default.value());
			}

			//Radeon Fluid Motion Frames
			if (graphicsSettings.FrameGenEnabled.Default.has_value())
			{
				toggleswitch_FrameGenEnabled().IsOn(graphicsSettings.FrameGenEnabled.Default.value());
				combobox_FrameGenSearchMode().IsEnabled(graphicsSettings.FrameGenEnabled.Default.value());
				combobox_FrameGenPerfMode().IsEnabled(graphicsSettings.FrameGenEnabled.Default.value());
				combobox_FrameGenResponseMode().IsEnabled(graphicsSettings.FrameGenEnabled.Default.value());
				combobox_FrameGenAlgorithm().IsEnabled(graphicsSettings.FrameGenEnabled.Default.value());
			}

			//Radeon Fluid Motion Frames - Search Mode
			if (graphicsSettings.FrameGenSearchMode.Default.has_value())
			{
				combobox_FrameGenSearchMode().SelectedIndex(graphicsSettings.FrameGenSearchMode.Default.value());
			}

			//Radeon Fluid Motion Frames - Performance Mode
			if (graphicsSettings.FrameGenPerfMode.Default.has_value())
			{
				combobox_FrameGenPerfMode().SelectedIndex(graphicsSettings.FrameGenPerfMode.Default.value());
			}

			//Radeon Fluid Motion Frames - Response Mode
			if (graphicsSettings.FrameGenResponseMode.Default.has_value())
			{
				combobox_FrameGenResponseMode().SelectedIndex(graphicsSettings.FrameGenResponseMode.Default.value());
			}

			//Radeon Fluid Motion Frames - Algorithm
			if (graphicsSettings.FrameGenAlgorithm.Default.has_value())
			{
				combobox_FrameGenAlgorithm().SelectedIndex(graphicsSettings.FrameGenAlgorithm.Default.value());
			}

			//Radeon Boost
			if (graphicsSettings.BoostEnabled.Default.has_value())
			{
				toggleswitch_RadeonBoost().IsOn(graphicsSettings.BoostEnabled.Default.value());
				slider_RadeonBoost_MinResolution().IsEnabled(graphicsSettings.BoostEnabled.Default.value());
			}

			//Radeon Boost - Minimum Resolution
			if (graphicsSettings.BoostMinResolution.Default.has_value())
			{
				slider_RadeonBoost_MinResolution().Value(graphicsSettings.BoostMinResolution.Default.value());
			}

			//Radeon Frame Rate Target Control - Maximum Frame Rate
			//Note: changing the FRTC frame rate will force enable FRTC so reset this first.
			if (graphicsSettings.FrtcFrameRateTarget.Default.has_value())
			{
				slider_Frtc_FrameRateTarget().Value(graphicsSettings.FrtcFrameRateTarget.Default.value());
			}

			//Radeon Frame Rate Target Control
			if (graphicsSettings.FrtcEnabled.Default.has_value())
			{
				toggleswitch_Frtc().IsOn(graphicsSettings.FrtcEnabled.Default.value());
				slider_Frtc_FrameRateTarget().IsEnabled(graphicsSettings.FrtcEnabled.Default.value());
			}

			//Radeon Chill
			if (graphicsSettings.ChillEnabled.Default.has_value())
			{
				//Disable Radeon Chill Link
				radeon_Chill_Linked = false;

				toggleswitch_RadeonChill().IsOn(graphicsSettings.ChillEnabled.Default.value());
				slider_RadeonChill_Min().IsEnabled(graphicsSettings.ChillEnabled.Default.value());
				slider_RadeonChill_Max().IsEnabled(graphicsSettings.ChillEnabled.Default.value());
				button_RadeonChill_Link().IsEnabled(graphicsSettings.ChillEnabled.Default.value());
			}

			//Radeon Chill - Minimum Frame Rate
			if (graphicsSettings.ChillMinFps.Default.has_value())
			{
				slider_RadeonChill_Min().Value(graphicsSettings.ChillMinFps.Default.value());
			}

			//Radeon Chill - Maximum Frame Rate
			if (graphicsSettings.ChillMaxFps.Default.has_value())
			{
				slider_RadeonChill_Max().Value(graphicsSettings.ChillMaxFps.Default.value());
			}

			//Radeon Image Sharpening 1
			if (graphicsSettings.RisEnabled.Default.has_value())
			{
				toggleswitch_RadeonImageSharpening1().IsOn(graphicsSettings.RisEnabled.Default.value());
				slider_RadeonImageSharpening1_Sharpening().IsEnabled(graphicsSettings.RisEnabled.Default.value());
			}

			//Radeon Image Sharpening 1 - Sharpening Degree
			if (graphicsSettings.RisSharpeningDegree.Default.has_value())
			{
				slider_RadeonImageSharpening1_Sharpening().Value(graphicsSettings.RisSharpeningDegree.Default.value());
			}

			//Radeon Image Sharpening 2
			if (graphicsSettings.Ris2Enabled.Default.has_value())
			{
				toggleswitch_RadeonImageSharpening2().IsOn(graphicsSettings.Ris2Enabled.Default.value());
				toggleswitch_RadeonImageSharpening2_Desktop().IsEnabled(graphicsSettings.Ris2Enabled.Default.value());
				slider_RadeonImageSharpening2_Sharpening().IsEnabled(graphicsSettings.Ris2Enabled.Default.value());
			}

			//Radeon Image Sharpening 2 - Sharpen Desktop
			if (graphicsSettings.Ris2DesktopEnabled.Default.has_value())
			{
				toggleswitch_RadeonImageSharpening2_Desktop().IsOn(graphicsSettings.Ris2DesktopEnabled.Default.value());
			}

			//Radeon Image Sharpening 2 - Sharpening Degree
			if (graphicsSettings.Ris2SharpeningDegree.Default.has_value())
			{
				slider_RadeonImageSharpening2_Sharpening().Value(graphicsSettings.Ris2SharpeningDegree.Default.value());
			}

			//Enhanced Sync
			if (graphicsSettings.EnhancedSync.Default.has_value())
			{
				toggleswitch_RadeonEnhancedSync().IsOn(graphicsSettings.EnhancedSync.Default.value());
			}

			//Vertical Sync
			if (graphicsSettings.VerticalSync.Default.has_value())
			{
				combobox_VerticalSync().SelectedIndex(graphicsSettings.VerticalSync.Default.value());
			}

			//Anti-Aliasing Override
			if (graphicsSettings.AntiAliasingOverride.Default.has_value())
			{
				toggleswitch_AntiAliasingOverride().IsOn(graphicsSettings.AntiAliasingOverride.Default.value());
				combobox_AntiAliasingMethod().IsEnabled(graphicsSettings.AntiAliasingOverride.Default.value());
				combobox_AntiAliasingLevel().IsEnabled(graphicsSettings.AntiAliasingOverride.Default.value());
				toggleswitch_AntiAliasingEnhancedQuality().IsEnabled(graphicsSettings.AntiAliasingOverride.Default.value());
			}

			//Anti-Aliasing Method
			if (graphicsSettings.AntiAliasingMethod.Default.has_value())
			{
				combobox_AntiAliasingMethod().SelectedIndex(graphicsSettings.AntiAliasingMethod.Default.value());
			}

			//Anti-Aliasing Level
			if (graphicsSettings.AntiAliasingLevel.Default.has_value())
			{
				combobox_AntiAliasingLevel().SelectedIndex(graphicsSettings.AntiAliasingLevel.Default.value());
			}

			//Enhanced Quality Anti-Aliasing
			if (graphicsSettings.AntiAliasingEnhancedQuality.Default.has_value())
			{
				toggleswitch_AntiAliasingEnhancedQuality().IsOn(graphicsSettings.AntiAliasingEnhancedQuality.Default.value());
			}

			//Morphological Anti-Aliasing
			if (graphicsSettings.AntiAliasingMorphological.Default.has_value())
			{
				toggleswitch_MorphologicalAntiAliasing().IsOn(graphicsSettings.AntiAliasingMorphological.Default.value());
			}

			//Anisotropic Texture Filtering Override
			if (graphicsSettings.AnisotropicOverride.Default.has_value())
			{
				combobox_AnisotropicTextureFiltering().SelectedIndex(graphicsSettings.AnisotropicOverride.Default.value());
			}

			//Texture Filtering Quality
			if (graphicsSettings.TextureFilteringQuality.Default.has_value())
			{
				combobox_TextureFilteringQuality().SelectedIndex(graphicsSettings.TextureFilteringQuality.Default.value());
			}

			//Surface Format Optimization
			if (graphicsSettings.SurfaceFormatOptimization.Default.has_value())
			{
				toggleswitch_SurfaceFormatOptimization().IsOn(graphicsSettings.SurfaceFormatOptimization.Default.value());
			}

			//Tessellation Mode
			if (graphicsSettings.TessellationMode.Default.has_value())
			{
				combobox_Tessellation_Mode().SelectedIndex(graphicsSettings.TessellationMode.Default.value());
				combobox_Tessellation_Level().IsEnabled(graphicsSettings.TessellationMode.Default.value());
			}

			//Tessellation Level
			if (graphicsSettings.TessellationLevel.Default.has_value())
			{
				combobox_Tessellation_Level().SelectedIndex(graphicsSettings.TessellationLevel.Default.value());
			}

			//OpenGL Triple Buffering
			if (graphicsSettings.OpenGLTripleBuffering.Default.has_value())
			{
				toggleswitch_OpenGLTripleBuffering().IsOn(graphicsSettings.OpenGLTripleBuffering.Default.value());
			}

			//OpenGL 10-Bit Pixel Format
			if (graphicsSettings.OpenGL10BitPixelFormat.Default.has_value())
			{
				toggleswitch_OpenGL10BitPixelFormat().IsOn(graphicsSettings.OpenGL10BitPixelFormat.Default.value());
			}

			//Return result
			AVDebugWriteLine("ADL graphics values reset.");
			return true;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("Failed resetting graphics values (Exception)");
			return false;
		}
	}
}