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
				//Get default FSR override dll path
				std::wstring newValue = FsrOverrideDllDefaultPath();
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "FsrOvrDLLPath", newValue);
			}

			//FSR Over-The-Air Updates
			{
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "FsrOtaIndex", L"1");
			}

			//FSR Latency Reduction
			try
			{
				//Set setting
				ADL_DELAG_SETTINGS adlSettings{};
				adlSettings.GlobalEnable = false;

				ADL_DELAG_NOTFICATION_REASON adlNotificationReason{};
				adlNotificationReason.GlobalEnableChanged = true;

				ADL_ERROR_REASON2 adlErrorReason;
				adl_Res0 = _ADL2_DELAG_SettingsX2_Set(adl_Context, adl_Gpu_AdapterIndex, adlSettings, adlNotificationReason, &adlErrorReason);

				//Notify change
				_ADL2_User_Settings_Notify(adl_Context, adl_Gpu_AdapterIndex, ADL_USER_SETTINGS_DELAG_PROFILE, ADL_TRUE);
			}
			catch (...) {}

			//Radeon Boost
			try
			{
				//Set setting
				ADL_BOOST_SETTINGS adlSettings{};
				adlSettings.GlobalEnable = false;
				adlSettings.GlobalMinRes = 84;

				ADL_BOOST_NOTFICATION_REASON adlNotificationReason{};
				adlNotificationReason.GlobalEnableChanged = true;
				adlNotificationReason.GlobalMinResChanged = true;

				ADL_ERROR_REASON2 adlErrorReason;
				adl_Res0 = _ADL2_BOOST_SettingsX2_Set(adl_Context, adl_Gpu_AdapterIndex, adlSettings, adlNotificationReason, &adlErrorReason);

				//Notify change
				_ADL2_User_Settings_Notify(adl_Context, adl_Gpu_AdapterIndex, ADL_USER_SETTINGS_BOOST_PROFILE, ADL_TRUE);
			}
			catch (...) {}

			//Radeon Chill
			try
			{
				//Set setting
				ADL_CHILL_SETTINGS adlSettings{};
				adlSettings.GlobalEnable = false;
				adlSettings.GlobalMinFPS = 75;
				adlSettings.GlobalMaxFPS = 140;

				ADL_CHILL_NOTFICATION_REASON adlNotificationReason{};
				adlNotificationReason.GlobalEnableChanged = true;
				adlNotificationReason.GlobalMinFPSChanged = true;
				adlNotificationReason.GlobalMaxFPSChanged = true;

				ADL_ERROR_REASON adlErrorReason;
				adl_Res0 = _ADL2_CHILL_SettingsX2_Set(adl_Context, adl_Gpu_AdapterIndex, adlSettings, adlNotificationReason, &adlErrorReason);

				//Notify change
				_ADL2_User_Settings_Notify(adl_Context, adl_Gpu_AdapterIndex, ADL_USER_SETTINGS_CHILL_PROFILE, ADL_TRUE);
			}
			catch (...) {}

			//Radeon Image Sharpening 1
			try
			{
				ADL_RIS_SETTINGS adlSettings{};
				adlSettings.GlobalEnable = false;
				adlSettings.GlobalSharpeningDegree = 80;

				ADL_RIS_NOTFICATION_REASON adlNotificationReason{};
				adlNotificationReason.GlobalEnableChanged = true;
				adlNotificationReason.GlobalSharpeningDegreeChanged = true;

				adl_Res0 = _ADL2_RIS_Settings_Set(adl_Context, adl_Gpu_AdapterIndex, adlSettings, adlNotificationReason);

				//Notify change
				_ADL2_User_Settings_Notify(adl_Context, adl_Gpu_AdapterIndex, ADL_USER_SETTINGS_USU_PROFILE, ADL_TRUE);
			}
			catch (...) {}

			//Radeon Image Sharpening 2
			try
			{
				ADL_RIS2_SETTINGS adlSettings{};
				adlSettings.GlobalEnable = 0;
				adlSettings.GlobalSharpeningDegree = 50;

				ADL_RIS2_NOTIFICATION_REASON adlNotificationReason{};
				adlNotificationReason.GlobalEnableChanged = true;
				adlNotificationReason.GlobalSharpeningDegreeChanged = true;

				adl_Res0 = _ADL2_RIS_SettingsX2_Set(adl_Context, adl_Gpu_AdapterIndex, adlSettings, adlNotificationReason);

				//Notify change
				_ADL2_User_Settings_Notify(adl_Context, adl_Gpu_AdapterIndex, ADL_USER_SETTINGS_USU2_PROFILE, ADL_TRUE);
			}
			catch (...) {}

			//Enhanced Sync
			try
			{
				//Set setting
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "TurboSync", L"0");

				//Notify change
				_ADL2_User_Settings_Notify(adl_Context, adl_Gpu_AdapterIndex, ADL_USER_SETTINGS_ENHANCEDSYNC, ADL_TRUE);
			}
			catch (...) {}

			//Vertical Refresh
			{
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "VSyncControl", L"1");
			}

			//Frame Rate Target Control
			try
			{
				//Set setting
				_ADL2_FPS_Settings_Reset(adl_Context, adl_Gpu_AdapterIndex);
			}
			catch (...) {}

			//Anti-Aliasing Override
			{
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "AntiAlias", L"1");
			}

			//Anti-Aliasing Method
			{
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "ASD", L"-1");
				AdlRegistrySettingSet(adl_Gpu_AdapterIndex, "UMD", "ASE", L"0");
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
			AVDebugWriteLine("ADL graphics registry values reset.");
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