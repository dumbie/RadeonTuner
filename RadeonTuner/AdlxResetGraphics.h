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

			//FSR Upscaling Override
			toggleswitch_FsrOverrideUpscaling().IsOn(true);

			//FSR Frame Generation Override
			toggleswitch_FsrOverrideFrameGeneration().IsOn(true);

			//FSR Multi Frame Generation Override
			toggleswitch_FsrOverrideMultiFrameGeneration().IsOn(false);

			//FSR Ray Regeneration Denoiser Override
			toggleswitch_FsrOverrideRayRegeneration().IsOn(false);

			//FSR Neural Radiance Caching Override
			toggleswitch_FsrOverrideNeuralRadianceCaching().IsOn(false);

			//FSR Multi Frame Generation Ratio
			combobox_MultiFrameGenerationRatio().SelectedIndex(0);

			//FSR Override Library
			FsrOverrideDllReset();

			//FSR Over-The-Air Updates
			combobox_FsrOtaUpdates().SelectedIndex(1);

			//FSR Latency Reduction
			toggleswitch_FsrLatencyReduction().IsOn(false);

			//Radeon Boost
			toggleswitch_RadeonBoost().IsOn(false);
			slider_RadeonBoost_MinRes().Value(68);
			slider_RadeonBoost_MinRes().IsEnabled(false);

			//Radeon Frame Rate Target Control
			toggleswitch_Frtc().IsOn(false);
			slider_Frtc_Fps().Value(60);
			slider_Frtc_Fps().IsEnabled(false);

			//Radeon Chill
			toggleswitch_RadeonChill().IsOn(false);
			slider_RadeonChill_Min().Value(75);
			slider_RadeonChill_Max().Value(140);
			slider_RadeonChill_Min().IsEnabled(false);
			slider_RadeonChill_Max().IsEnabled(false);
			button_RadeonChill_Link().IsEnabled(false);

			//Radeon Image Sharpening 1
			toggleswitch_RadeonImageSharpening1().IsOn(false);
			slider_RadeonImageSharpening1_Sharpening().Value(80);
			slider_RadeonImageSharpening1_Sharpening().IsEnabled(false);

			//Radeon Image Sharpening 2
			toggleswitch_RadeonImageSharpening2().IsOn(false);
			toggleswitch_RadeonImageSharpening2_Desktop().IsOn(false);
			toggleswitch_RadeonImageSharpening2_Desktop().IsEnabled(false);
			slider_RadeonImageSharpening2_Sharpening().Value(50);
			slider_RadeonImageSharpening2_Sharpening().IsEnabled(false);

			//Enhanced Sync
			toggleswitch_RadeonEnhancedSync().IsOn(false);

			//Vertical Refresh
			combobox_VerticalRefresh().SelectedIndex(1);

			//Anti-Aliasing Override
			toggleswitch_AntiAliasingOverride().IsOn(false);
			combobox_AntiAliasingMethod().IsEnabled(false);
			combobox_AntiAliasingLevel().IsEnabled(false);
			toggleswitch_EnhancedQualityAntiAliasing().IsEnabled(false);

			//Anti-Aliasing Method
			combobox_AntiAliasingMethod().SelectedIndex(0);

			//Anti-Aliasing Level
			combobox_AntiAliasingLevel().SelectedIndex(0);

			//Enhanced Quality Anti-Aliasing
			toggleswitch_EnhancedQualityAntiAliasing().IsOn(false);

			//Morphological Anti-Aliasing
			toggleswitch_MorphologicalAntiAliasing().IsOn(false);

			//Anisotropic Texture Filtering Override
			combobox_AnisotropicTextureFiltering_Level().SelectedIndex(0);

			//Texture Filtering Quality
			combobox_TextureFilteringQuality().SelectedIndex(1);

			//Surface Format Optimization
			toggleswitch_SurfaceFormatOptimization().IsOn(false);

			//Tessellation Mode
			combobox_Tessellation_Mode().SelectedIndex(0);
			combobox_Tessellation_Level().IsEnabled(false);

			//Tessellation Level
			combobox_Tessellation_Level().SelectedIndex(7);

			//OpenGL Triple Buffering
			toggleswitch_OpenGLTripleBuffering().IsOn(false);

			//OpenGL 10-Bit Pixel Format
			toggleswitch_OpenGL10BitPixelFormat().IsOn(false);

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