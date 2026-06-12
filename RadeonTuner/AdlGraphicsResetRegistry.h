#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::AdlGraphicsResetRegistry()
	{
		try
		{
			AVDebugWriteLine("Resetting registry graphics to defaults.");

			//Set default application properties
			std::vector<AdlAppProperty> adlAppProperties{};

			//FSR Upscaling Override
			{
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "FsrOverride", L"1");
			}

			//FSR Interpolation Frame Generation Override
			{
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "MlfiOverride", L"0");
			}

			//FSR Multi Frame Generation Override
			{
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "MfgOverride", L"0");
			}

			//FSR Multi Frame Generation Ratio
			{
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "MfgRatio", L"0");
			}

			//FSR Ray Regeneration Denoiser Override
			{
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "MldOverride", L"0");
			}

			//FSR Neural Radiance Caching Override
			{
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "NrcOverride", L"0");
			}

			//FSR Override DLL Path
			{
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "FsrOvrDLLPath", L"");
			}

			//FSR Over-The-Air Updates
			{
				//AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "FsrOtaIndex", L"1");
			}

			//FSR Latency Reduction
			{
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "", "KMD_DeLagEnabled", 0);
				_ADL2_User_Settings_Notify(adl_Context, adl_Gpu_AdapterIndex, ADL_USER_SETTINGS_DELAG_PROFILE, ADL_TRUE);
			}

			//Radeon Boost
			{
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "", "KMD_RadeonBoostEnabled", 0);
				_ADL2_User_Settings_Notify(adl_Context, adl_Gpu_AdapterIndex, ADL_USER_SETTINGS_BOOST_PROFILE, ADL_TRUE);
			}

			//Radeon Boost Minimum Resolution
			{
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "", "KMD_RadeonBoostMinResolution", 84);
				_ADL2_User_Settings_Notify(adl_Context, adl_Gpu_AdapterIndex, ADL_USER_SETTINGS_BOOST_PROFILE, ADL_TRUE);
			}

			//Radeon Chill
			{
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "", "KMD_ChillEnabled", 0);
				_ADL2_User_Settings_Notify(adl_Context, adl_Gpu_AdapterIndex, ADL_USER_SETTINGS_CHILL_PROFILE, ADL_TRUE);
			}

			//Radeon Chill Minimum Frame Rate
			{
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "", "KMD_ChillMinFps", 75);
				_ADL2_User_Settings_Notify(adl_Context, adl_Gpu_AdapterIndex, ADL_USER_SETTINGS_CHILL_PROFILE, ADL_TRUE);
			}

			//Radeon Chill Maximum Frame Rate
			{
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "", "KMD_ChillMaxFps", 140);
				_ADL2_User_Settings_Notify(adl_Context, adl_Gpu_AdapterIndex, ADL_USER_SETTINGS_CHILL_PROFILE, ADL_TRUE);
			}

			//Radeon Image Sharpening
			try
			{
				IADLX3DImageSharpeningPtr pp3DImageSharpening;
				adlx_Res0 = pp3DSettingsServices->GetImageSharpening(ppGpuInfo, &pp3DImageSharpening);
				adlx_Res0 = pp3DImageSharpening->SetEnabled(0);
			}
			catch (...) {}

			//Radeon Image Sharpening Sharpness
			try
			{
				IADLX3DImageSharpeningPtr pp3DImageSharpening;
				adlx_Res0 = pp3DSettingsServices->GetImageSharpening(ppGpuInfo, &pp3DImageSharpening);
				adlx_Res0 = pp3DImageSharpening->SetSharpness(80);
			}
			catch (...) {}

			//Enhanced Sync
			{
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "TurboSync", L"0");
			}

			//Vertical Refresh
			{
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "VSyncControl", L"1");
			}

			//Frame Rate Target Control
			try
			{
				IADLX3DFrameRateTargetControlPtr pp3DFrameRateTargetControl;
				adlx_Res0 = pp3DSettingsServices->GetFrameRateTargetControl(ppGpuInfo, &pp3DFrameRateTargetControl);
				adlx_Res0 = pp3DFrameRateTargetControl->SetEnabled(0);
			}
			catch (...){}

			//Frame Rate Target Control Maximum Frame Rate
			try
			{
				IADLX3DFrameRateTargetControlPtr pp3DFrameRateTargetControl;
				adlx_Res0 = pp3DSettingsServices->GetFrameRateTargetControl(ppGpuInfo, &pp3DFrameRateTargetControl);
				adlx_Res0 = pp3DFrameRateTargetControl->SetFPS(60);
			}
			catch (...) {}

			//Anti-Aliasing Override
			{
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "AntiAlias", L"1");
			}

			//Anti-Aliasing Method
			{
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "ASD", L"-1");
			}
			{
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "ASE", L"0");
			}
			{
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "ASTT", L"0");
			}

			//Anti-Aliasing Level
			{
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "AntiAliasSamples", L"2");
			}

			//Enhanced Quality Anti-Aliasing
			{
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "EQAA", L"0");
			}

			//Morphological Anti-Aliasing
			{
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "MLF", L"0");
			}

			//Anisotropic Texture Filtering Override
			{
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "AnisoDegree", L"0");
			}

			//Texture Filtering Quality
			{
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "TFQ", L"1");
			}

			//Surface Format Optimization
			{
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "SurfaceFormatReplacements", L"0");
			}

			//Tessellation Mode
			{
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "Tessellation_OPTION", L"0");
			}

			//Tessellation Level
			{
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "Tessellation", L"64");
			}

			//OpenGL Triple Buffering
			{
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "EnableTripleBuffering", L"0");
			}

			//OpenGL 10-Bit Pixel Format
			{
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "", "KMD_10BitMode", 2);
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "", "Gmx_Enable10BitMode", 2);
			}

			//Return result
			return true;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("Failed resetting registry graphics (Exception)");
			return false;
		}
	}
}