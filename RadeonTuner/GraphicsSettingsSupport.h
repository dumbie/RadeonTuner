#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	GraphicsSettings MainPage::GraphicsSettingsGetSupport(int gpuAdapterIndex)
	{
		GraphicsSettings graphicsSettings{};
		try
		{
			//Note: ADL2_Adapter_Feature_Caps does not seem to be reliable for example FRTC always returns as not supported.

			//FSR Upscaling Override
			try
			{
				//Get feature support
				int featureSupport = -1;
				adl_Res0 = _ADL2_DriverMLSRSupport_Get(adl_Context, gpuAdapterIndex, &featureSupport);
				if (adl_Res0 == ADL_OK)
				{
					graphicsSettings.FsrOverride.Support = featureSupport;
				}
			}
			catch (...) {}

			//FSR Frame Generation Override
			try
			{
				//Get feature support
				int featureSupport = -1;
				adl_Res0 = _ADL2_DriverMLFISupport_Get(adl_Context, gpuAdapterIndex, &featureSupport);
				if (adl_Res0 == ADL_OK)
				{
					graphicsSettings.MlfiOverride.Support = featureSupport;
				}
			}
			catch (...) {}

			//FSR Multi Frame Generation Override / Ratio
			try
			{
				//Get feature support
				int featureSupport = -1;
				adl_Res0 = _ADL2_DriverMFGSupport_Get(adl_Context, gpuAdapterIndex, &featureSupport);
				if (adl_Res0 == ADL_OK)
				{
					graphicsSettings.MfgOverride.Support = featureSupport;
					graphicsSettings.MfgRatio.Support = featureSupport;
				}
			}
			catch (...) {}

			//FSR Ray Regeneration Denoiser Override
			try
			{
				//Get feature support
				int featureSupport = -1;
				adl_Res0 = _ADL2_DriverMLDSupport_Get(adl_Context, gpuAdapterIndex, &featureSupport);
				if (adl_Res0 == ADL_OK)
				{
					graphicsSettings.MldOverride.Support = featureSupport;
				}
			}
			catch (...) {}

			//FSR Neural Radiance Caching Override
			try
			{
				//Get feature support
				int featureSupport = -1;
				adl_Res0 = _ADL2_DriverNRCSupport_Get(adl_Context, gpuAdapterIndex, &featureSupport);
				if (adl_Res0 == ADL_OK)
				{
					graphicsSettings.NrcOverride.Support = featureSupport;
				}
			}
			catch (...) {}

			//FSR Override Library
			try
			{
				//Get feature support
				int featureSupport = -1;
				adl_Res0 = _ADL2_DriverMLSRSupport_Get(adl_Context, gpuAdapterIndex, &featureSupport);
				if (adl_Res0 == ADL_OK)
				{
					graphicsSettings.FsrOvrDLLPath.Support = featureSupport;
				}
			}
			catch (...) {}

			//FSR Over-The-Air Updates
			try
			{
				//Fix switch to ADL2_CloudProfile_DLL_Get

				//Get feature support
				int featureSupport = -1;
				adl_Res0 = _ADL2_DriverMLSRSupport_Get(adl_Context, gpuAdapterIndex, &featureSupport);
				if (adl_Res0 == ADL_OK)
				{
					graphicsSettings.FsrOtaIndex.Support = featureSupport;
				}
			}
			catch (...) {}

			//FSR Show Information
			try
			{
				graphicsSettings.FsrShowInformation.Support = true;
			}
			catch (...) {}

			//FSR Latency Reduction
			try
			{
				//Get feature support
				ADL_DELAG_SETTINGSX4 adlSettings;
				adl_Res0 = _ADL2_DELAG_SettingsX4_Get(adl_Context, gpuAdapterIndex, &adlSettings);
				if (adl_Res0 == ADL_OK)
				{
					graphicsSettings.DeLagEnabled.Support = true;
				}
			}
			catch (...) {}

			//Radeon Fluid Motion Frames
			try
			{
				//Get feature support
				int featureSupport = -1;
				adl_Res0 = _ADL2_DriverFrameGenerationSupport_Get(adl_Context, gpuAdapterIndex, &featureSupport);
				if (adl_Res0 == ADL_OK)
				{
					graphicsSettings.FrameGenEnabled.Support = featureSupport;
					graphicsSettings.FrameGenSearchMode.Support = featureSupport;
					graphicsSettings.FrameGenPerfMode.Support = featureSupport;
					graphicsSettings.FrameGenResponseMode.Support = featureSupport;
					graphicsSettings.FrameGenAlgorithm.Support = featureSupport;
				}
			}
			catch (...) {}

			//Radeon Boost
			try
			{
				//Get feature support
				ADL_BOOST_SETTINGSX4 adlSettings;
				adl_Res0 = _ADL2_BOOST_SettingsX4_Get(adl_Context, gpuAdapterIndex, &adlSettings);
				if (adl_Res0 == ADL_OK)
				{
					graphicsSettings.BoostMode.Support = true;
					graphicsSettings.BoostMinResolution.Support = true;
				}
			}
			catch (...) {}

			//Radeon Frame Rate Target Control
			try
			{
				//Get feature support
				int featureSupport = -1;
				int versionSupport = -1;
				adl_Res0 = _ADL2_FPS_Caps(adl_Context, gpuAdapterIndex, &featureSupport, &versionSupport);
				if (adl_Res0 == ADL_OK)
				{
					graphicsSettings.FrtcEnabled.Support = featureSupport;
					graphicsSettings.FrtcFrameRateTarget.Support = featureSupport;
				}
			}
			catch (...) {}

			//Radeon Chill
			try
			{
				//Get feature support
				int featureSupport = -1;
				int versionSupport = -1;
				adl_Res0 = _ADL2_Chill_Caps_Get(adl_Context, gpuAdapterIndex, &featureSupport, &versionSupport);
				if (adl_Res0 == ADL_OK)
				{
					graphicsSettings.ChillEnabled.Support = featureSupport;
					graphicsSettings.ChillMinFps.Support = featureSupport;
					graphicsSettings.ChillMaxFps.Support = featureSupport;
				}
			}
			catch (...) {}

			//Radeon Image Sharpening 1
			try
			{
				//Get feature support
				ADL_RIS_SETTINGS adlSettings;
				adl_Res0 = _ADL2_RIS_Settings_Get(adl_Context, gpuAdapterIndex, &adlSettings);
				if (adl_Res0 == ADL_OK)
				{
					graphicsSettings.RisVersion.Version = 1;
					graphicsSettings.RisEnabled.Support = true;
					graphicsSettings.RisSharpeningDegree.Support = true;
				}
			}
			catch (...) {}

			//Radeon Image Sharpening 2
			try
			{
				//Get feature support
				ADL_RIS2_SETTINGS adlSettings;
				adl_Res0 = _ADL2_RIS_SettingsX2_Get(adl_Context, gpuAdapterIndex, &adlSettings);
				if (adl_Res0 == ADL_OK)
				{
					graphicsSettings.RisVersion.Version = 2;
					graphicsSettings.RisEnabled.Support = true;
					graphicsSettings.RisSharpeningDegree.Support = true;
					graphicsSettings.RisDesktopEnabled.Support = true;
				}
			}
			catch (...) {}

			//Enhanced Sync
			try
			{
				//Get feature support
				int featureSupport = -1;
				adl_Res0 = _ADL2_TurboSyncSupport_Get(adl_Context, gpuAdapterIndex, &featureSupport);
				if (adl_Res0 == ADL_OK)
				{
					graphicsSettings.EnhancedSync.Support = featureSupport;
				}
			}
			catch (...) {}

			//Vertical Sync
			try
			{
				//Fix check registry UMD\VSyncControl_NA == 1
				graphicsSettings.VerticalSync.Support = true;
			}
			catch (...) {}

			//Anti-Aliasing
			try
			{
				//Fix check registry UMD\AntiAlias_NA == 1
				graphicsSettings.AntiAliasingOverride.Support = true;
				graphicsSettings.AntiAliasingMethod.Support = true;
				graphicsSettings.AntiAliasingLevel.Support = true;
			}
			catch (...) {}

			//Enhanced Quality Anti-Aliasing
			try
			{
				//Fix check registry UMD\EQAA_NA == 1
				graphicsSettings.AntiAliasingEnhancedQuality.Support = true;
			}
			catch (...) {}

			//Morphological Anti-Aliasing
			try
			{
				//Fix check registry UMD\MLF_NA == 1
				graphicsSettings.AntiAliasingMorphological.Support = true;
			}
			catch (...) {}

			//Anisotropic Texture Filtering Override
			try
			{
				//Fix check registry UMD\AnisoDegree_NA == 1
				graphicsSettings.AnisotropicOverride.Support = true;
			}
			catch (...) {}

			//Texture Filtering Quality
			try
			{
				//Fix check registry UMD\TFQ_NA == 1
				graphicsSettings.TextureFilteringQuality.Support = true;
			}
			catch (...) {}

			//Surface Format Optimization
			try
			{
				//Fix check registry UMD\SurfaceFormatReplacements_NA == 1
				graphicsSettings.SurfaceFormatOptimization.Support = true;
			}
			catch (...) {}

			//Tessellation
			try
			{
				//Fix check registry UMD\Tessellation_NA == 1
				graphicsSettings.TessellationMode.Support = true;
				graphicsSettings.TessellationLevel.Support = true;
			}
			catch (...) {}

			//OpenGL Triple Buffering
			try
			{
				//Fix check registry UMD\EnableTripleBuffering_NA == 1
				graphicsSettings.OpenGLTripleBuffering.Support = true;
			}
			catch (...) {}

			//OpenGL 10-Bit Pixel Format
			try
			{
				//Fix find way to check support
				graphicsSettings.OpenGL10BitPixelFormat.Support = true;
			}
			catch (...) {}

			//Return result
			AVDebugWriteLine(L"Got graphics settings support.");
			return graphicsSettings;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine(L"Failed to get graphics settings support.");
			return graphicsSettings;
		}
	}
}