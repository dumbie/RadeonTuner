#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::GraphicsSettings_Convert_ToUI(GraphicsSettings graphicsSettings)
	{
		try
		{
			//FSR Upscaling Override
			if (graphicsSettings.FsrOverride.has_value())
			{
				toggleswitch_FsrOverrideUpscaling().IsOn(graphicsSettings.FsrOverride.value());
			}

			//FSR Frame Generation Override
			if (graphicsSettings.MlfiOverride.has_value())
			{
				toggleswitch_FsrOverrideFrameGeneration().IsOn(graphicsSettings.MlfiOverride.value());
			}

			//FSR Multi Frame Generation Override
			if (graphicsSettings.MfgOverride.has_value())
			{
				toggleswitch_FsrOverrideMultiFrameGeneration().IsOn(graphicsSettings.MfgOverride.value());
			}

			//FSR Ray Regeneration Denoiser Override
			if (graphicsSettings.MldOverride.has_value())
			{
				toggleswitch_FsrOverrideRayRegeneration().IsOn(graphicsSettings.MldOverride.value());
			}

			//FSR Neural Radiance Caching Override
			if (graphicsSettings.MldOverride.has_value())
			{
				toggleswitch_FsrOverrideNeuralRadianceCaching().IsOn(graphicsSettings.NrcOverride.value());
			}

			//FSR Multi Frame Generation Ratio
			if (graphicsSettings.MfgRatio.has_value())
			{
				combobox_MultiFrameGenerationRatio().SelectedIndex(graphicsSettings.MfgRatio.value());
			}

			//FSR Override Library
			{
				//Skip import export
			}

			//FSR Over-The-Air Updates
			{
				//Skip import export
			}

			//FSR Latency Reduction
			if (graphicsSettings.DeLagEnabled.has_value())
			{
				toggleswitch_FsrLatencyReduction().IsOn(graphicsSettings.DeLagEnabled.value());
			}

			//Radeon Fluid Motion Frames
			if (graphicsSettings.FrameGenEnabled.has_value())
			{
				toggleswitch_FrameGenEnabled().IsOn(graphicsSettings.FrameGenEnabled.value());
			}
			if (graphicsSettings.FrameGenSearchMode.has_value())
			{
				combobox_FrameGenSearchMode().SelectedIndex(graphicsSettings.FrameGenSearchMode.value());
			}
			if (graphicsSettings.FrameGenPerfMode.has_value())
			{
				combobox_FrameGenPerfMode().SelectedIndex(graphicsSettings.FrameGenPerfMode.value());
			}
			if (graphicsSettings.FrameGenResponseMode.has_value())
			{
				combobox_FrameGenResponseMode().SelectedIndex(graphicsSettings.FrameGenResponseMode.value());
			}
			if (graphicsSettings.FrameGenAlgorithm.has_value())
			{
				combobox_FrameGenAlgorithm().SelectedIndex(graphicsSettings.FrameGenAlgorithm.value());
			}

			//Radeon Boost
			if (graphicsSettings.BoostEnabled.has_value())
			{
				toggleswitch_RadeonBoost().IsOn(graphicsSettings.BoostEnabled.value());
			}
			if (graphicsSettings.BoostMinResolution.has_value())
			{
				slider_RadeonBoost_MinRes().Value(graphicsSettings.BoostMinResolution.value());
			}

			//Radeon Chill
			if (graphicsSettings.ChillEnabled.has_value())
			{
				toggleswitch_RadeonChill().IsOn(graphicsSettings.ChillEnabled.value());
			}

			//Radeon Image Sharpening 1
			if (graphicsSettings.RisEnable.has_value())
			{
				toggleswitch_RadeonImageSharpening1().IsOn(graphicsSettings.RisEnable.value());
			}
			if (graphicsSettings.RisSharpeningDegree.has_value())
			{
				slider_RadeonImageSharpening1_Sharpening().Value(graphicsSettings.RisSharpeningDegree.value());
			}

			//Radeon Image Sharpening 2
			if (graphicsSettings.Ris2Enable.has_value())
			{
				toggleswitch_RadeonImageSharpening2().IsOn(graphicsSettings.Ris2Enable.value());
			}
			if (graphicsSettings.Ris2Desktop.has_value())
			{
				toggleswitch_RadeonImageSharpening2_Desktop().IsOn(graphicsSettings.Ris2Desktop.value());
			}
			if (graphicsSettings.Ris2SharpeningDegree.has_value())
			{
				slider_RadeonImageSharpening2_Sharpening().Value(graphicsSettings.Ris2SharpeningDegree.value());
			}

			//Enhanced Sync
			if (graphicsSettings.TurboSync.has_value())
			{
				toggleswitch_RadeonEnhancedSync().IsOn(graphicsSettings.TurboSync.value());
			}

			//Vertical Refresh
			if (graphicsSettings.VSyncControl.has_value())
			{
				combobox_VerticalRefresh().SelectedIndex(graphicsSettings.VSyncControl.value());
			}

			//Frame Rate Target Control
			if (graphicsSettings.FRTCEnabled.has_value())
			{
				toggleswitch_Frtc().IsOn(graphicsSettings.FRTCEnabled.value());
			}
			if (graphicsSettings.FRTCFrameRateTarget.has_value())
			{
				slider_Frtc_Fps().Value(graphicsSettings.FRTCFrameRateTarget.value());
			}

			//Anti-Aliasing Override
			if (graphicsSettings.AntiAlias.has_value())
			{
				toggleswitch_AntiAliasingOverride().IsOn(graphicsSettings.AntiAlias.value());
			}

			//Anti-Aliasing Method
			if (graphicsSettings.AntiAliasMethod.has_value())
			{
				combobox_AntiAliasingMethod().SelectedIndex(graphicsSettings.AntiAliasMethod.value());
			}

			//Anti-Aliasing Level
			if (graphicsSettings.AntiAliasSamples.has_value())
			{
				combobox_AntiAliasingLevel().SelectedIndex(graphicsSettings.AntiAliasSamples.value());
			}

			//Enhanced Quality Anti-Aliasing
			if (graphicsSettings.EQAA.has_value())
			{
				toggleswitch_EnhancedQualityAntiAliasing().IsOn(graphicsSettings.EQAA.value());
			}

			//Morphological Anti-Aliasing
			if (graphicsSettings.MLF.has_value())
			{
				toggleswitch_MorphologicalAntiAliasing().IsOn(graphicsSettings.MLF.value());
			}

			//Anisotropic Texture Filtering Override
			if (graphicsSettings.AnisoDegree.has_value())
			{
				combobox_AnisotropicTextureFiltering_Level().SelectedIndex(graphicsSettings.AnisoDegree.value());
			}

			//Texture Filtering Quality
			if (graphicsSettings.TFQ.has_value())
			{
				combobox_TextureFilteringQuality().SelectedIndex(graphicsSettings.TFQ.value());
			}

			//Surface Format Optimization
			if (graphicsSettings.SurfaceFormatReplacements.has_value())
			{
				toggleswitch_SurfaceFormatOptimization().IsOn(graphicsSettings.SurfaceFormatReplacements.value());
			}

			//Tessellation Mode
			if (graphicsSettings.TessellationMode.has_value())
			{
				combobox_Tessellation_Mode().SelectedIndex(graphicsSettings.TessellationMode.value());
			}

			//Tessellation Level
			if (graphicsSettings.TessellationLevel.has_value())
			{
				combobox_Tessellation_Level().SelectedIndex(graphicsSettings.TessellationLevel.value());
			}

			//OpenGL Triple Buffering
			if (graphicsSettings.EnableTripleBuffering.has_value())
			{
				toggleswitch_OpenGLTripleBuffering().IsOn(graphicsSettings.EnableTripleBuffering.value());
			}

			//OpenGL 10-Bit Pixel Format
			if (graphicsSettings.OpenGL10BitPixelFormat.has_value())
			{
				toggleswitch_OpenGL10BitPixelFormat().IsOn(graphicsSettings.OpenGL10BitPixelFormat.value());
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

	std::optional<GraphicsSettings> MainPage::GraphicsSettings_Generate_FromUI()
	{
		try
		{
			GraphicsSettings graphicsSettings{};

			//FSR Upscaling Override
			if (toggleswitch_FsrOverrideUpscaling().IsEnabled())
			{
				graphicsSettings.FsrOverride = toggleswitch_FsrOverrideUpscaling().IsOn();
			}

			//FSR Frame Generation Override
			if (toggleswitch_FsrOverrideFrameGeneration().IsEnabled())
			{
				graphicsSettings.MlfiOverride = toggleswitch_FsrOverrideFrameGeneration().IsOn();
			}

			//FSR Multi Frame Generation Override
			if (toggleswitch_FsrOverrideMultiFrameGeneration().IsEnabled())
			{
				graphicsSettings.MfgOverride = toggleswitch_FsrOverrideMultiFrameGeneration().IsOn();
			}

			//FSR Ray Regeneration Denoiser Override
			if (toggleswitch_FsrOverrideRayRegeneration().IsEnabled())
			{
				graphicsSettings.MldOverride = toggleswitch_FsrOverrideRayRegeneration().IsOn();
			}

			//FSR Neural Radiance Caching Override
			if (toggleswitch_FsrOverrideNeuralRadianceCaching().IsEnabled())
			{
				graphicsSettings.NrcOverride = toggleswitch_FsrOverrideNeuralRadianceCaching().IsOn();
			}

			//FSR Multi Frame Generation Ratio
			if (combobox_MultiFrameGenerationRatio().IsEnabled())
			{
				graphicsSettings.MfgRatio = combobox_MultiFrameGenerationRatio().SelectedIndex();
			}

			//FSR Override Library
			{
				//Skip import export
			}

			//FSR Over-The-Air Updates
			{
				//Skip import export
			}

			//FSR Latency Reduction
			if (toggleswitch_FsrLatencyReduction().IsEnabled())
			{
				graphicsSettings.DeLagEnabled = toggleswitch_FsrLatencyReduction().IsOn();
			}

			//Radeon Fluid Motion Frames
			if (toggleswitch_FrameGenEnabled().IsEnabled())
			{
				graphicsSettings.FrameGenEnabled = toggleswitch_FrameGenEnabled().IsOn();
				graphicsSettings.FrameGenSearchMode = combobox_FrameGenSearchMode().SelectedIndex();
				graphicsSettings.FrameGenPerfMode = combobox_FrameGenPerfMode().SelectedIndex();
				graphicsSettings.FrameGenResponseMode = combobox_FrameGenResponseMode().SelectedIndex();
				graphicsSettings.FrameGenAlgorithm = combobox_FrameGenAlgorithm().SelectedIndex();
			}

			//Radeon Boost
			if (toggleswitch_RadeonBoost().IsEnabled())
			{
				graphicsSettings.BoostEnabled = toggleswitch_RadeonBoost().IsOn();
				graphicsSettings.BoostMinResolution = slider_RadeonBoost_MinRes().Value();
			}

			//Radeon Frame Rate Target Control
			if (toggleswitch_Frtc().IsEnabled())
			{
				graphicsSettings.FRTCEnabled = toggleswitch_Frtc().IsOn();
				graphicsSettings.FRTCFrameRateTarget = slider_Frtc_Fps().Value();
			}

			//Radeon Chill
			if (toggleswitch_RadeonChill().IsEnabled())
			{
				graphicsSettings.ChillEnabled = toggleswitch_RadeonChill().IsOn();
				graphicsSettings.ChillMinFps = slider_RadeonChill_Min().Value();
				graphicsSettings.ChillMaxFps = slider_RadeonChill_Max().Value();
			}
			//FixPort link status

			//Radeon Image Sharpening 1
			if (toggleswitch_RadeonImageSharpening1().IsEnabled())
			{
				graphicsSettings.RisEnable = toggleswitch_RadeonImageSharpening1().IsOn();
				graphicsSettings.RisSharpeningDegree = slider_RadeonImageSharpening1_Sharpening().Value();
			}

			//Radeon Image Sharpening 2
			if (toggleswitch_RadeonImageSharpening2().IsEnabled())
			{
				graphicsSettings.Ris2Enable = toggleswitch_RadeonImageSharpening2().IsOn();
				graphicsSettings.Ris2Desktop = toggleswitch_RadeonImageSharpening2_Desktop().IsOn();
				graphicsSettings.Ris2SharpeningDegree = slider_RadeonImageSharpening2_Sharpening().Value();
			}

			//Enhanced Sync
			if (toggleswitch_RadeonEnhancedSync().IsEnabled())
			{
				graphicsSettings.TurboSync = toggleswitch_RadeonEnhancedSync().IsOn();
			}

			//Vertical Refresh
			if (combobox_VerticalRefresh().IsEnabled())
			{
				graphicsSettings.VSyncControl = combobox_VerticalRefresh().SelectedIndex();
			}

			//Anti-Aliasing
			if (toggleswitch_AntiAliasingOverride().IsEnabled())
			{
				//Anti-Aliasing Override
				graphicsSettings.AntiAlias = toggleswitch_AntiAliasingOverride().IsOn();

				//Anti-Aliasing Method
				graphicsSettings.AntiAliasMethod = combobox_AntiAliasingMethod().SelectedIndex();

				//Anti-Aliasing Level
				graphicsSettings.AntiAliasSamples = combobox_AntiAliasingLevel().SelectedIndex();

				//Enhanced Quality Anti-Aliasing
				graphicsSettings.EQAA = toggleswitch_EnhancedQualityAntiAliasing().IsOn();
			}	

			//Morphological Anti-Aliasing
			if (toggleswitch_MorphologicalAntiAliasing().IsEnabled())
			{
				graphicsSettings.MLF = toggleswitch_MorphologicalAntiAliasing().IsOn();
			}

			//Anisotropic Texture Filtering Override
			if (combobox_AnisotropicTextureFiltering_Level().IsEnabled())
			{
				graphicsSettings.AnisoDegree = combobox_AnisotropicTextureFiltering_Level().SelectedIndex();
			}

			//Texture Filtering Quality
			if (combobox_TextureFilteringQuality().IsEnabled())
			{
				graphicsSettings.TFQ = combobox_TextureFilteringQuality().SelectedIndex();
			}

			//Surface Format Optimization
			if (toggleswitch_SurfaceFormatOptimization().IsEnabled())
			{
				graphicsSettings.SurfaceFormatReplacements = toggleswitch_SurfaceFormatOptimization().IsOn();
			}

			//Tessellation Mode
			if (combobox_Tessellation_Mode().IsEnabled())
			{
				graphicsSettings.TessellationMode = combobox_Tessellation_Mode().SelectedIndex();
				graphicsSettings.TessellationLevel = combobox_Tessellation_Level().SelectedIndex();
			}

			//Tessellation Level

			//OpenGL Triple Buffering
			if (toggleswitch_OpenGLTripleBuffering().IsEnabled())
			{
				graphicsSettings.EnableTripleBuffering = toggleswitch_OpenGLTripleBuffering().IsOn();
			}

			//OpenGL 10-Bit Pixel Format
			if (toggleswitch_OpenGL10BitPixelFormat().IsEnabled())
			{
				graphicsSettings.OpenGL10BitPixelFormat = toggleswitch_OpenGL10BitPixelFormat().IsOn();
			}

			//Return result
			return graphicsSettings;
		}
		catch (...)
		{
			//Return result
			return std::nullopt;
		}
	}
}