#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::AdlGraphicsSettingsApply(int gpuAdapterIndex, std::wstring gpuUniqueIdentifierHex, AdlApplication& adlApp, GraphicsSettings targetSettings, AdlSettingGet settingGet)
	{
		try
		{
			std::vector<AdlAppProperty> adlAppProperties{};

			//FSR Upscaling Override
			try
			{
				if (targetSettings.FsrOverride.Get(settingGet).has_value())
				{
					//Get value
					auto newValue = targetSettings.FsrOverride.Get(settingGet).value();

					//Check application type
					if (targetSettings.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "FsrOverride", number_to_wstring(newValue));
					}
					else
					{
						//Set application properties
						AdlAppProperty adlAppProperty0{};
						adlAppProperty0.Name = L"FsrOverride";
						AdlAppPropertyValue adlAppPropertyValue0{};
						adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
						adlAppPropertyValue0.Value = number_to_wstring(newValue);
						adlAppProperty0.Values = { adlAppPropertyValue0 };
						adlAppProperties.push_back(adlAppProperty0);
					}
				}
			}
			catch (...) {}

			//FSR Frame Generation Override
			try
			{
				if (targetSettings.MlfiOverride.Get(settingGet).has_value())
				{
					//Get value
					auto newValue = targetSettings.MlfiOverride.Get(settingGet).value();

					//Check application type
					if (targetSettings.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "MlfiOverride", number_to_wstring(newValue));
					}
					else
					{
						//Set application properties
						AdlAppProperty adlAppProperty0{};
						adlAppProperty0.Name = L"MlfiOverride";
						AdlAppPropertyValue adlAppPropertyValue0{};
						adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
						adlAppPropertyValue0.Value = number_to_wstring(newValue);
						adlAppProperty0.Values = { adlAppPropertyValue0 };
						adlAppProperties.push_back(adlAppProperty0);
					}
				}
			}
			catch (...) {}

			//FSR Multi Frame Generation Override
			try
			{
				if (targetSettings.MfgOverride.Get(settingGet).has_value())
				{
					//Get value
					auto newValue = targetSettings.MfgOverride.Get(settingGet).value();

					//Check application type
					if (targetSettings.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "MfgOverride", number_to_wstring(newValue));
					}
					else
					{
						//Set application properties
						AdlAppProperty adlAppProperty0{};
						adlAppProperty0.Name = L"MfgOverride";
						AdlAppPropertyValue adlAppPropertyValue0{};
						adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
						adlAppPropertyValue0.Value = number_to_wstring(newValue);
						adlAppProperty0.Values = { adlAppPropertyValue0 };
						adlAppProperties.push_back(adlAppProperty0);
					}
				}
			}
			catch (...) {}

			//FSR Ray Regeneration Denoiser Override
			try
			{
				if (targetSettings.MldOverride.Get(settingGet).has_value())
				{
					//Get value
					auto newValue = targetSettings.MldOverride.Get(settingGet).value();

					//Check application type
					if (targetSettings.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "MldOverride", number_to_wstring(newValue));
					}
					else
					{
						//Set application properties
						AdlAppProperty adlAppProperty0{};
						adlAppProperty0.Name = L"MldOverride";
						AdlAppPropertyValue adlAppPropertyValue0{};
						adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
						adlAppPropertyValue0.Value = number_to_wstring(newValue);
						adlAppProperty0.Values = { adlAppPropertyValue0 };
						adlAppProperties.push_back(adlAppProperty0);
					}
				}
			}
			catch (...) {}

			//FSR Neural Radiance Caching Override
			try
			{
				if (targetSettings.NrcOverride.Get(settingGet).has_value())
				{
					//Get value
					auto newValue = targetSettings.NrcOverride.Get(settingGet).value();

					//Check application type
					if (targetSettings.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "NrcOverride", number_to_wstring(newValue));
					}
					else
					{
						//Set application properties
						AdlAppProperty adlAppProperty0{};
						adlAppProperty0.Name = L"NrcOverride";
						AdlAppPropertyValue adlAppPropertyValue0{};
						adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
						adlAppPropertyValue0.Value = number_to_wstring(newValue);
						adlAppProperty0.Values = { adlAppPropertyValue0 };
						adlAppProperties.push_back(adlAppProperty0);
					}
				}
			}
			catch (...) {}

			//FSR Multi Frame Generation Ratio
			try
			{
				if (targetSettings.MfgRatio.Get(settingGet).has_value())
				{
					//Get value
					auto newValue = targetSettings.MfgRatio.Get(settingGet).value();

					//Enumeration index correction
					std::wstring setValue = L"0";
					if (newValue == 0)
					{
						setValue = L"0";
					}
					else if (newValue == 1)
					{
						setValue = L"2";
					}
					else if (newValue == 2)
					{
						setValue = L"3";
					}
					else if (newValue == 3)
					{
						setValue = L"4";
					}

					//Check application type
					if (targetSettings.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "MfgRatio", setValue);
					}
					else
					{
						//Set application properties
						AdlAppProperty adlAppProperty0{};
						adlAppProperty0.Name = L"MfgRatio";
						AdlAppPropertyValue adlAppPropertyValue0{};
						adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
						adlAppPropertyValue0.Value = setValue;
						adlAppProperty0.Values = { adlAppPropertyValue0 };
						adlAppProperties.push_back(adlAppProperty0);
					}
				}
			}
			catch (...) {}

			//FSR Override Library
			try
			{
				if (targetSettings.FsrOvrDLLPath.Get(settingGet).has_value())
				{
					//Get value
					auto newValue = targetSettings.FsrOvrDLLPath.Get(settingGet).value();

					//Check application type
					if (targetSettings.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "FsrOvrDLLPath", newValue);
					}
					else
					{
						//Note: Disabled because setting does not seem to work.
						////Set application properties
						//AdlAppProperty adlAppProperty0{};
						//adlAppProperty0.Name = L"FfxDllPath";
						//AdlAppPropertyValue adlAppPropertyValue0{};
						//adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
						//adlAppPropertyValue0.Value = newValue;
						//adlAppProperty0.Values = { adlAppPropertyValue0 };
						//adlAppProperties.push_back(adlAppProperty0);
					}
				}
			}
			catch (...) {}

			//FSR Over-The-Air Updates
			try
			{
				if (targetSettings.FsrOtaIndex.Get(settingGet).has_value())
				{
					//Note: AMD Adrenalin also changes the FsrOvrDLLPath to the selected value switching between amdxcffx64techpreview.dll and amdxcffx64.dll.

					//Get value
					auto newValue = targetSettings.FsrOtaIndex.Get(settingGet).value();

					//Check application type
					if (targetSettings.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "FsrOtaIndex", number_to_wstring(newValue));
					}
					else
					{
						//Note: Disabled because setting does not seem to work.
						////Set application properties
						//AdlAppProperty adlAppProperty0{};
						//adlAppProperty0.Name = L"FsrOtaIndex";
						//AdlAppPropertyValue adlAppPropertyValue0{};
						//adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
						//adlAppPropertyValue0.Value = number_to_wstring(newValue);
						//adlAppProperty0.Values = { adlAppPropertyValue0 };
						//adlAppProperties.push_back(adlAppProperty0);
					}
				}
			}
			catch (...) {}

			//FSR Latency Reduction
			try
			{
				if (targetSettings.DeLagEnabled.Get(settingGet).has_value())
				{
					//Get value
					auto newValue = targetSettings.DeLagEnabled.Get(settingGet).value();

					//Check application type
					if (targetSettings.Global())
					{
						//Set setting
						ADL_DELAG_SETTINGS adlSettings{};
						adlSettings.GlobalEnable = newValue;

						ADL_DELAG_NOTFICATION_REASON adlNotificationReason{};
						adlNotificationReason.GlobalEnableChanged = true;

						ADL_ERROR_REASON2 adlErrorReason;
						adl_Res0 = _ADL2_DELAG_SettingsX2_Set(adl_Context, gpuAdapterIndex, adlSettings, adlNotificationReason, &adlErrorReason);

						//Notify change
						_ADL2_User_Settings_Notify(adl_Context, gpuAdapterIndex, ADL_USER_SETTINGS_DELAG_PROFILE, true);
					}
					else
					{
						//Set application properties
						AdlAppProperty adlAppProperty0{};
						adlAppProperty0.Name = L"Dlg_PFEnable";
						AdlAppPropertyValue adlAppPropertyValue0{};
						adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
						adlAppPropertyValue0.Value = number_to_wstring(newValue);
						adlAppProperty0.Values = { adlAppPropertyValue0 };
						adlAppProperties.push_back(adlAppProperty0);
					}
				}
			}
			catch (...) {}

			//Enhanced Sync
			try
			{
				if (targetSettings.EnhancedSync.Get(settingGet).has_value())
				{
					//Get value
					auto newValue = targetSettings.EnhancedSync.Get(settingGet).value();

					//Check application type
					if (targetSettings.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "TurboSync", number_to_wstring(newValue));

						//Notify change
						_ADL2_User_Settings_Notify(adl_Context, gpuAdapterIndex, ADL_USER_SETTINGS_ENHANCEDSYNC, true);
					}
					else
					{
						//Set application properties
						AdlAppProperty adlAppProperty0{};
						adlAppProperty0.Name = L"TurboSync";
						AdlAppPropertyValue adlAppPropertyValue0{};
						adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
						adlAppPropertyValue0.Value = number_to_wstring(newValue);
						adlAppProperty0.Values = { adlAppPropertyValue0 };
						adlAppProperties.push_back(adlAppProperty0);
					}
				}
			}
			catch (...) {}

			//Vertical Sync
			try
			{
				if (targetSettings.VerticalSync.Get(settingGet).has_value())
				{
					//Get value
					auto newValue = targetSettings.VerticalSync.Get(settingGet).value();

					//Check application type
					if (targetSettings.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "VSyncControl", number_to_wstring(newValue));
					}
					else
					{
						//Set application properties
						AdlAppProperty adlAppProperty0{};
						adlAppProperty0.Name = L"VSyncControl";
						AdlAppPropertyValue adlAppPropertyValue0{};
						adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
						adlAppPropertyValue0.Value = number_to_wstring(newValue);
						adlAppProperty0.Values = { adlAppPropertyValue0 };
						adlAppProperties.push_back(adlAppProperty0);
					}
				}
			}
			catch (...) {}

			//Radeon Fluid Motion Frames
			try
			{
				if (targetSettings.FrameGenEnabled.Get(settingGet).has_value())
				{
					//Get value
					auto newValue = targetSettings.FrameGenEnabled.Get(settingGet).value();

					//Check application type
					if (targetSettings.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "", "DrvFrameGenEnabled", newValue);
					}
				}
			}
			catch (...) {}

			//Radeon Fluid Motion Frames - Search Mode
			try
			{
				if (targetSettings.FrameGenSearchMode.Get(settingGet).has_value())
				{
					//Get value
					auto newValue = targetSettings.FrameGenSearchMode.Get(settingGet).value();

					//Check application type
					if (targetSettings.Global())
					{
						//Set setting
						RegistrySet(HKEY_ENUM::CURRENT_USER, L"Software\\AMD\\DVR", L"FrameGenSearchMode", newValue);
					}
				}
			}
			catch (...) {}

			//Radeon Fluid Motion Frames - Performance Mode
			try
			{
				if (targetSettings.FrameGenPerfMode.Get(settingGet).has_value())
				{
					//Get value
					auto newValue = targetSettings.FrameGenPerfMode.Get(settingGet).value();

					//Check application type
					if (targetSettings.Global())
					{
						//Set setting
						RegistrySet(HKEY_ENUM::CURRENT_USER, L"Software\\AMD\\DVR", L"FrameGenPerfMode", newValue);
					}
				}
			}
			catch (...) {}

			//Radeon Fluid Motion Frames - Response Mode
			try
			{
				if (targetSettings.FrameGenResponseMode.Get(settingGet).has_value())
				{
					//Get value
					auto newValue = targetSettings.FrameGenResponseMode.Get(settingGet).value();

					//Check application type
					if (targetSettings.Global())
					{
						//Set setting
						RegistrySet(HKEY_ENUM::CURRENT_USER, L"Software\\AMD\\DVR", L"FrameGenFallbackMode", newValue);
					}
				}
			}
			catch (...) {}

			//Radeon Fluid Motion Frames - Algorithm
			try
			{
				if (targetSettings.FrameGenAlgorithm.Get(settingGet).has_value())
				{
					//Get value
					auto newValue = targetSettings.FrameGenAlgorithm.Get(settingGet).value();

					//Check application type
					if (targetSettings.Global())
					{
						//Set setting
						RegistrySet(HKEY_ENUM::CURRENT_USER, L"Software\\AMD\\DVR", L"FrameGenAlgorithm", newValue);
					}
				}
			}
			catch (...) {}

			//Radeon Chill
			try
			{
				if (targetSettings.ChillEnabled.Get(settingGet).has_value())
				{
					//Get value
					auto newValue = targetSettings.ChillEnabled.Get(settingGet).value();

					//Check application type
					if (targetSettings.Global())
					{
						//Set setting
						ADL_CHILL_SETTINGS adlSettings{};
						adlSettings.GlobalEnable = newValue;

						ADL_CHILL_NOTFICATION_REASON adlNotificationReason{};
						adlNotificationReason.GlobalEnableChanged = true;

						ADL_ERROR_REASON adlErrorReason;
						adl_Res0 = _ADL2_CHILL_SettingsX2_Set(adl_Context, gpuAdapterIndex, adlSettings, adlNotificationReason, &adlErrorReason);

						//Notify change
						_ADL2_User_Settings_Notify(adl_Context, gpuAdapterIndex, ADL_USER_SETTINGS_CHILL_PROFILE, true);
					}
					else
					{
						//Set application properties
						AdlAppProperty adlAppProperty0{};
						adlAppProperty0.Name = L"Chil_PFEnable";
						AdlAppPropertyValue adlAppPropertyValue0{};
						adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
						adlAppPropertyValue0.Value = number_to_wstring(newValue);
						adlAppProperty0.Values = { adlAppPropertyValue0 };
						adlAppProperties.push_back(adlAppProperty0);
					}
				}
			}
			catch (...) {}

			//Radeon Chill - Minimum Frame Rate
			try
			{
				if (targetSettings.ChillMinFps.Get(settingGet).has_value())
				{
					//Get value
					auto newValue = targetSettings.ChillMinFps.Get(settingGet).value();

					//Check application type
					if (targetSettings.Global())
					{
						//Set setting
						ADL_CHILL_SETTINGS adlSettings{};
						adlSettings.GlobalMinFPS = newValue;

						ADL_CHILL_NOTFICATION_REASON adlNotificationReason{};
						adlNotificationReason.GlobalMinFPSChanged = true;

						ADL_ERROR_REASON adlErrorReason;
						adl_Res0 = _ADL2_CHILL_SettingsX2_Set(adl_Context, gpuAdapterIndex, adlSettings, adlNotificationReason, &adlErrorReason);

						//Notify change
						_ADL2_User_Settings_Notify(adl_Context, gpuAdapterIndex, ADL_USER_SETTINGS_CHILL_PROFILE, true);
					}
					else
					{
						//Set application properties
						AdlAppProperty adlAppProperty0{};
						adlAppProperty0.Name = L"Chil_MinFRate";
						AdlAppPropertyValue adlAppPropertyValue0{};
						adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
						adlAppPropertyValue0.Value = number_to_wstring(newValue);
						adlAppProperty0.Values = { adlAppPropertyValue0 };
						adlAppProperties.push_back(adlAppProperty0);
					}
				}
			}
			catch (...) {}

			//Radeon Chill - Maximum Frame Rate
			try
			{
				if (targetSettings.ChillMaxFps.Get(settingGet).has_value())
				{
					//Get value
					auto newValue = targetSettings.ChillMaxFps.Get(settingGet).value();

					//Check application type
					if (targetSettings.Global())
					{
						//Set setting
						ADL_CHILL_SETTINGS adlSettings{};
						adlSettings.GlobalMaxFPS = newValue;

						ADL_CHILL_NOTFICATION_REASON adlNotificationReason{};
						adlNotificationReason.GlobalMaxFPSChanged = true;

						ADL_ERROR_REASON adlErrorReason;
						adl_Res0 = _ADL2_CHILL_SettingsX2_Set(adl_Context, gpuAdapterIndex, adlSettings, adlNotificationReason, &adlErrorReason);

						//Notify change
						_ADL2_User_Settings_Notify(adl_Context, gpuAdapterIndex, ADL_USER_SETTINGS_CHILL_PROFILE, true);
					}
					else
					{
						//Set application properties
						AdlAppProperty adlAppProperty0{};
						adlAppProperty0.Name = L"Chil_MaxFRate";
						AdlAppPropertyValue adlAppPropertyValue0{};
						adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
						adlAppPropertyValue0.Value = number_to_wstring(newValue);
						adlAppProperty0.Values = { adlAppPropertyValue0 };
						adlAppProperties.push_back(adlAppProperty0);
					}
				}
			}
			catch (...) {}

			//Radeon Boost
			try
			{
				if (targetSettings.BoostMode.Get(settingGet).has_value())
				{
					//Get value
					auto newValue = targetSettings.BoostMode.Get(settingGet).value();

					//Enumeration index correction
					int setValueNormal = 0;
					int setValueAdaptive = 0;
					if (newValue == 0)
					{
						//Disabled
						setValueNormal = 0;
						setValueAdaptive = 0;
					}
					else if (newValue == 1)
					{
						//Input-Based
						setValueNormal = 1;
						setValueAdaptive = 0;
					}
					else if (newValue == 2)
					{
						//Scene-Based
						setValueNormal = 0;
						setValueAdaptive = 1;
					}
					else if (newValue == 3)
					{
						//Multi-Modal
						setValueNormal = 1;
						setValueAdaptive = 1;
					}

					//Check application type
					if (targetSettings.Global())
					{
						//Set setting
						ADL_BOOST_SETTINGSX4 adlSettings{};
						adlSettings.GlobalEnable = setValueNormal;
						adlSettings.AdaptiveVrsEnabled = setValueAdaptive;

						ADL_BOOST_NOTIFICATION_REASONX4 adlNotificationReason{};
						adlNotificationReason.GlobalEnableChanged = true;
						adlNotificationReason.AdaptiveVrsChanged = true;

						ADL_ERROR_REASON2 adlErrorReason;
						adl_Res0 = _ADL2_BOOST_SettingsX4_Set(adl_Context, gpuAdapterIndex, adlSettings, adlNotificationReason, &adlErrorReason);

						//Notify change
						_ADL2_User_Settings_Notify(adl_Context, gpuAdapterIndex, ADL_USER_SETTINGS_BOOST_PROFILE, true);
					}
					else
					{
						//Set application properties
						AdlAppProperty adlAppProperty0{};
						adlAppProperty0.Name = L"Bst_PFEnable";
						AdlAppPropertyValue adlAppPropertyValue0{};
						adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
						adlAppPropertyValue0.Value = number_to_wstring(setValueNormal);
						adlAppProperty0.Values = { adlAppPropertyValue0 };
						adlAppProperties.push_back(adlAppProperty0);

						AdlAppProperty adlAppProperty1{};
						adlAppProperty1.Name = L"Bst_AdaPFEnable";
						AdlAppPropertyValue adlAppPropertyValue1{};
						adlAppPropertyValue1.GpuId = gpuUniqueIdentifierHex;
						adlAppPropertyValue1.Value = number_to_wstring(setValueAdaptive);
						adlAppProperty1.Values = { adlAppPropertyValue1 };
						adlAppProperties.push_back(adlAppProperty1);
					}
				}
			}
			catch (...) {}

			//Radeon Boost - Minimum Resolution
			try
			{
				if (targetSettings.BoostMinResolution.Get(settingGet).has_value())
				{
					//Get value
					auto newValue = targetSettings.BoostMinResolution.Get(settingGet).value();

					//Check application type
					if (targetSettings.Global())
					{
						//Set setting
						ADL_BOOST_SETTINGSX4 adlSettings{};
						adlSettings.GlobalMinRes = newValue;

						ADL_BOOST_NOTIFICATION_REASONX4 adlNotificationReason{};
						adlNotificationReason.GlobalMinResChanged = true;

						ADL_ERROR_REASON2 adlErrorReason;
						adl_Res0 = _ADL2_BOOST_SettingsX4_Set(adl_Context, gpuAdapterIndex, adlSettings, adlNotificationReason, &adlErrorReason);

						//Notify change
						_ADL2_User_Settings_Notify(adl_Context, gpuAdapterIndex, ADL_USER_SETTINGS_BOOST_PROFILE, true);
					}
					else
					{
						//Set application properties
						AdlAppProperty adlAppProperty0{};
						adlAppProperty0.Name = L"Bst_MaxScale";
						AdlAppPropertyValue adlAppPropertyValue0{};
						adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
						adlAppPropertyValue0.Value = number_to_wstring(newValue);
						adlAppProperty0.Values = { adlAppPropertyValue0 };
						adlAppProperties.push_back(adlAppProperty0);
					}
				}
			}
			catch (...) {}

			//Radeon Image Sharpening 1
			try
			{
				if (targetSettings.RisEnabled.Get(settingGet).has_value() && targetSettings.RisSharpeningDegree.Get(settingGet).has_value())
				{
					//Get value
					auto enabledValue = targetSettings.RisEnabled.Get(settingGet).value();
					auto sharpeningValue = targetSettings.RisSharpeningDegree.Get(settingGet).value();
					float sharpeningValueApp = (float)sharpeningValue / 100.0F;

					//Check application type
					if (targetSettings.Global())
					{
						//Set setting
						ADL_RIS_SETTINGS adlSettings{};
						adlSettings.GlobalEnable = enabledValue;
						adlSettings.GlobalSharpeningDegree = sharpeningValue;

						ADL_RIS_NOTFICATION_REASON adlNotificationReason{};
						adlNotificationReason.GlobalEnableChanged = true;
						adlNotificationReason.GlobalSharpeningDegreeChanged = true;

						adl_Res0 = _ADL2_RIS_Settings_Set(adl_Context, gpuAdapterIndex, adlSettings, adlNotificationReason);

						//Notify change
						_ADL2_User_Settings_Notify(adl_Context, gpuAdapterIndex, ADL_USER_SETTINGS_USU_PROFILE, true);
					}
					else
					{
						//Set application properties
						AdlAppProperty adlAppProperty0{};
						adlAppProperty0.Name = L"Ris_PFEnable";
						AdlAppPropertyValue adlAppPropertyValue0{};
						adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
						adlAppPropertyValue0.Value = number_to_wstring(enabledValue);
						adlAppProperty0.Values = { adlAppPropertyValue0 };
						adlAppProperties.push_back(adlAppProperty0);

						AdlAppProperty adlAppProperty1{};
						adlAppProperty1.Name = L"Ris_SHDegree";
						AdlAppPropertyValue adlAppPropertyValue1{};
						adlAppPropertyValue1.GpuId = gpuUniqueIdentifierHex;
						adlAppPropertyValue1.Value = float_to_wstring(sharpeningValueApp, 1);
						adlAppProperty1.Values = { adlAppPropertyValue1 };
						adlAppProperties.push_back(adlAppProperty1);
					}
				}
			}
			catch (...) {}

			//Radeon Image Sharpening 2
			try
			{
				if (targetSettings.Ris2Enabled.Get(settingGet).has_value() && targetSettings.Ris2DesktopEnabled.Get(settingGet).has_value() && targetSettings.Ris2SharpeningDegree.Get(settingGet).has_value())
				{
					//Note: RIS2 registry states 0 = off / 1 = on / 2 = off + desktop / 3 = on + desktop

					//Get value
					auto enabledValue = targetSettings.Ris2Enabled.Get(settingGet).value();
					auto desktopValue = targetSettings.Ris2DesktopEnabled.Get(settingGet).value();
					auto sharpeningValue = targetSettings.Ris2SharpeningDegree.Get(settingGet).value();

					//Check application type
					if (targetSettings.Global())
					{
						//Set setting
						ADL_RIS2_SETTINGS adlSettings{};
						adlSettings.GlobalEnable = enabledValue;
						adlSettings.GlobalDesktop = desktopValue;
						adlSettings.GlobalSharpeningDegree = sharpeningValue;

						ADL_RIS2_NOTIFICATION_REASON adlNotificationReason{};
						adlNotificationReason.GlobalEnableChanged = true;
						adlNotificationReason.GlobalDesktopChanged = true;
						adlNotificationReason.GlobalSharpeningDegreeChanged = true;

						adl_Res0 = _ADL2_RIS_SettingsX2_Set(adl_Context, gpuAdapterIndex, adlSettings, adlNotificationReason);

						//Notify change
						_ADL2_User_Settings_Notify(adl_Context, gpuAdapterIndex, ADL_USER_SETTINGS_USU2_PROFILE, true);
					}
				}
			}
			catch (...) {}

			//Anti-Aliasing Override
			try
			{
				if (targetSettings.AntiAliasingOverride.Get(settingGet).has_value())
				{
					//Get value
					auto newValue = targetSettings.AntiAliasingOverride.Get(settingGet).value();

					//Enumeration index correction
					std::wstring setValue = newValue ? L"2" : L"1";

					//Check application type
					if (targetSettings.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "AntiAlias", setValue);
					}
					else
					{
						//Set application properties
						AdlAppProperty adlAppProperty0{};
						adlAppProperty0.Name = L"AntiAlias";
						AdlAppPropertyValue adlAppPropertyValue0{};
						adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
						adlAppPropertyValue0.Value = setValue;
						adlAppProperty0.Values = { adlAppPropertyValue0 };
						adlAppProperties.push_back(adlAppProperty0);
					}
				}
			}
			catch (...) {}

			//Anti-Aliasing Method
			try
			{
				if (targetSettings.AntiAliasingMethod.Get(settingGet).has_value())
				{
					//Get value
					auto newValue = targetSettings.AntiAliasingMethod.Get(settingGet).value();

					//Enumeration index correction
					std::wstring setValueAsd = L"-1";
					std::wstring setValueAse = L"0";
					std::wstring setValueAstt = L"0";
					if (newValue == 0)
					{
						//Multisampling
						setValueAsd = L"-1";
						setValueAse = L"0";
						setValueAstt = L"0";
					}
					else if (newValue == 1)
					{
						//Adaptive Multisampling
						setValueAsd = L"1";
						setValueAse = L"0";
						setValueAstt = L"1";
					}
					else if (newValue == 2)
					{
						//Supersampling
						setValueAsd = L"1";
						setValueAse = L"1";
						setValueAstt = L"1";
					}

					//Set setting
					if (targetSettings.Global())
					{
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "ASD", setValueAsd);
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "ASE", setValueAse);
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "ASTT", setValueAstt);
					}
					else
					{
						//Set application properties
						AdlAppProperty adlAppProperty0{};
						adlAppProperty0.Name = L"ASD";
						AdlAppPropertyValue adlAppPropertyValue0{};
						adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
						adlAppPropertyValue0.Value = setValueAsd;
						adlAppProperty0.Values = { adlAppPropertyValue0 };
						adlAppProperties.push_back(adlAppProperty0);

						AdlAppProperty adlAppProperty1{};
						adlAppProperty1.Name = L"ASE";
						AdlAppPropertyValue adlAppPropertyValue1{};
						adlAppPropertyValue1.GpuId = gpuUniqueIdentifierHex;
						adlAppPropertyValue1.Value = setValueAse;
						adlAppProperty1.Values = { adlAppPropertyValue1 };
						adlAppProperties.push_back(adlAppProperty1);

						AdlAppProperty adlAppProperty2{};
						adlAppProperty2.Name = L"ASTT";
						AdlAppPropertyValue adlAppPropertyValue2{};
						adlAppPropertyValue2.GpuId = gpuUniqueIdentifierHex;
						adlAppPropertyValue2.Value = setValueAstt;
						adlAppProperty2.Values = { adlAppPropertyValue2 };
						adlAppProperties.push_back(adlAppProperty2);
					}
				}
			}
			catch (...) {}

			//Anti-Aliasing Level
			try
			{
				if (targetSettings.AntiAliasingLevel.Get(settingGet).has_value())
				{
					//Get value
					auto newValue = targetSettings.AntiAliasingLevel.Get(settingGet).value();

					//Enumeration index correction
					std::wstring setValue = L"2";
					if (newValue == 0)
					{
						setValue = L"2";
					}
					else if (newValue == 1)
					{
						setValue = L"4";
					}
					else if (newValue == 2)
					{
						setValue = L"8";
					}

					//Check application type
					if (targetSettings.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "AntiAliasSamples", setValue);
					}
					else
					{
						//Set application properties
						AdlAppProperty adlAppProperty0{};
						adlAppProperty0.Name = L"AntiAliasSmpls";
						AdlAppPropertyValue adlAppPropertyValue0{};
						adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
						adlAppPropertyValue0.Value = setValue;
						adlAppProperty0.Values = { adlAppPropertyValue0 };
						adlAppProperties.push_back(adlAppProperty0);
					}
				}
			}
			catch (...) {}

			//Enhanced Quality Anti-Aliasing
			try
			{
				if (targetSettings.AntiAliasingEnhancedQuality.Get(settingGet).has_value())
				{
					//Get value
					auto newValue = targetSettings.AntiAliasingEnhancedQuality.Get(settingGet).value();

					//Check application type
					if (targetSettings.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "EQAA", number_to_wstring(newValue));
					}
					else
					{
						//Set application properties
						AdlAppProperty adlAppProperty0{};
						adlAppProperty0.Name = L"EQAA";
						AdlAppPropertyValue adlAppPropertyValue0{};
						adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
						adlAppPropertyValue0.Value = number_to_wstring(newValue);
						adlAppProperty0.Values = { adlAppPropertyValue0 };
						adlAppProperties.push_back(adlAppProperty0);
					}
				}
			}
			catch (...) {}

			//Morphological Anti-Aliasing
			try
			{
				if (targetSettings.AntiAliasingMorphological.Get(settingGet).has_value())
				{
					//Get value
					auto newValue = targetSettings.AntiAliasingMorphological.Get(settingGet).value();

					//Check application type
					if (targetSettings.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "MLF", number_to_wstring(newValue));
					}
					else
					{
						//Set application properties
						AdlAppProperty adlAppProperty0{};
						adlAppProperty0.Name = L"MLF";
						AdlAppPropertyValue adlAppPropertyValue0{};
						adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
						adlAppPropertyValue0.Value = number_to_wstring(newValue);
						adlAppProperty0.Values = { adlAppPropertyValue0 };
						adlAppProperties.push_back(adlAppProperty0);
					}
				}
			}
			catch (...) {}

			//Anisotropic Texture Filtering Override
			try
			{
				if (targetSettings.AnisotropicOverride.Get(settingGet).has_value())
				{
					//Get value
					auto newValue = targetSettings.AnisotropicOverride.Get(settingGet).value();

					//Enumeration index correction
					std::wstring setValue = L"0";
					if (newValue == 0)
					{
						setValue = L"0";
					}
					else if (newValue == 1)
					{
						setValue = L"2";
					}
					else if (newValue == 2)
					{
						setValue = L"4";
					}
					else if (newValue == 3)
					{
						setValue = L"8";
					}
					else if (newValue == 4)
					{
						setValue = L"16";
					}

					//Check application type
					if (targetSettings.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "AnisoDegree", setValue);
					}
					else
					{
						//Set application properties
						AdlAppProperty adlAppProperty0{};
						adlAppProperty0.Name = L"AnisoDegree";
						AdlAppPropertyValue adlAppPropertyValue0{};
						adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
						adlAppPropertyValue0.Value = setValue;
						adlAppProperty0.Values = { adlAppPropertyValue0 };
						adlAppProperties.push_back(adlAppProperty0);
					}
				}
			}
			catch (...) {}

			//Tessellation Mode
			try
			{
				if (targetSettings.TessellationMode.Get(settingGet).has_value())
				{
					//Get value
					auto newValue = targetSettings.TessellationMode.Get(settingGet).value();

					//Check application type
					if (targetSettings.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "Tessellation_OPTION", number_to_wstring(newValue));
					}
					else
					{
						//Set application properties
						AdlAppProperty adlAppProperty0{};
						adlAppProperty0.Name = L"Tessellation_OP";
						AdlAppPropertyValue adlAppPropertyValue0{};
						adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
						adlAppPropertyValue0.Value = number_to_wstring(newValue);
						adlAppProperty0.Values = { adlAppPropertyValue0 };
						adlAppProperties.push_back(adlAppProperty0);
					}
				}
			}
			catch (...) {}

			//Tessellation Level
			try
			{
				if (targetSettings.TessellationLevel.Get(settingGet).has_value())
				{
					//Get value
					auto newValue = targetSettings.TessellationLevel.Get(settingGet).value();

					//Enumeration index correction
					std::wstring setValue = L"1";
					if (newValue == 0)
					{
						setValue = L"1";
					}
					else if (newValue == 1)
					{
						setValue = L"2";
					}
					else if (newValue == 2)
					{
						setValue = L"4";
					}
					else if (newValue == 3)
					{
						setValue = L"6";
					}
					else if (newValue == 4)
					{
						setValue = L"8";
					}
					else if (newValue == 5)
					{
						setValue = L"16";
					}
					else if (newValue == 6)
					{
						setValue = L"32";
					}
					else if (newValue == 7)
					{
						setValue = L"64";
					}

					//Check application type
					if (targetSettings.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "Tessellation", setValue);
					}
					else
					{
						//Set application properties
						AdlAppProperty adlAppProperty0{};
						adlAppProperty0.Name = L"Tessellation";
						AdlAppPropertyValue adlAppPropertyValue0{};
						adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
						adlAppPropertyValue0.Value = setValue;
						adlAppProperty0.Values = { adlAppPropertyValue0 };
						adlAppProperties.push_back(adlAppProperty0);
					}
				}
			}
			catch (...) {}

			//OpenGL Triple Buffering
			try
			{
				if (targetSettings.OpenGLTripleBuffering.Get(settingGet).has_value())
				{
					//Get value
					auto newValue = targetSettings.OpenGLTripleBuffering.Get(settingGet).value();

					if (targetSettings.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "EnableTripleBuffering", number_to_wstring(newValue));
					}
					else
					{
						//Set application properties
						AdlAppProperty adlAppProperty0{};
						adlAppProperty0.Name = L"EnableTrplBffr";
						AdlAppPropertyValue adlAppPropertyValue0{};
						adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
						adlAppPropertyValue0.Value = number_to_wstring(newValue);
						adlAppProperty0.Values = { adlAppPropertyValue0 };
						adlAppProperties.push_back(adlAppProperty0);
					}
				}
			}
			catch (...) {}

			//Texture Filtering Quality
			try
			{
				if (targetSettings.TextureFilteringQuality.Get(settingGet).has_value())
				{
					//Get value
					auto newValue = targetSettings.TextureFilteringQuality.Get(settingGet).value();

					//Check application type
					if (targetSettings.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "TFQ", number_to_wstring(newValue));
					}
					else
					{
						//Set application properties
						AdlAppProperty adlAppProperty0{};
						adlAppProperty0.Name = L"TFQ";
						AdlAppPropertyValue adlAppPropertyValue0{};
						adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
						adlAppPropertyValue0.Value = number_to_wstring(newValue);
						adlAppProperty0.Values = { adlAppPropertyValue0 };
						adlAppProperties.push_back(adlAppProperty0);
					}
				}
			}
			catch (...) {}

			//Surface Format Optimization
			try
			{
				if (targetSettings.SurfaceFormatOptimization.Get(settingGet).has_value())
				{
					//Get value
					auto newValue = targetSettings.SurfaceFormatOptimization.Get(settingGet).value();

					//Check application type
					if (targetSettings.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "SurfaceFormatReplacements", number_to_wstring(newValue));
					}
					else
					{
						//Set application properties
						AdlAppProperty adlAppProperty0{};
						adlAppProperty0.Name = L"SrfcFrmtRplcmnt";
						AdlAppPropertyValue adlAppPropertyValue0{};
						adlAppPropertyValue0.GpuId = gpuUniqueIdentifierHex;
						adlAppPropertyValue0.Value = number_to_wstring(newValue);
						adlAppProperty0.Values = { adlAppPropertyValue0 };
						adlAppProperties.push_back(adlAppProperty0);
					}
				}
			}
			catch (...) {}

			//Radeon Frame Rate Target Control - Maximum Frame Rate
			//Note: Frame rate needs to be set before state because it force enables FRTC.
			try
			{
				if (targetSettings.FrtcFrameRateTarget.Get(settingGet).has_value())
				{
					//Get value
					auto frameRateValue = targetSettings.FrtcFrameRateTarget.Get(settingGet).value();

					//Check application type
					if (targetSettings.Global())
					{
						ADLFPSSettingsInput adlSettings{};
						adlSettings.bGlobalSettings = true;
						adlSettings.ulACFPSCurrent = frameRateValue;
						adlSettings.ulDCFPSCurrent = frameRateValue;
						adl_Res0 = _ADL2_FPS_Settings_Set(adl_Context, gpuAdapterIndex, adlSettings);
					}
				}
			}
			catch (...) {}

			//Radeon Frame Rate Target Control - Enabled
			try
			{
				if (targetSettings.FrtcEnabled.Get(settingGet).has_value() && targetSettings.FrtcFrameRateTarget.Get(settingGet).has_value())
				{
					//Get value
					auto enabledValue = targetSettings.FrtcEnabled.Get(settingGet).value();
					auto frameRateValue = targetSettings.FrtcFrameRateTarget.Get(settingGet).value();

					//Check application type
					if (targetSettings.Global())
					{
						//Set setting
						if (enabledValue)
						{
							ADLFPSSettingsInput adlSettings{};
							adlSettings.bGlobalSettings = true;
							adlSettings.ulACFPSCurrent = frameRateValue;
							adlSettings.ulDCFPSCurrent = frameRateValue;
							adl_Res0 = _ADL2_FPS_Settings_Set(adl_Context, gpuAdapterIndex, adlSettings);
						}
						else
						{
							ADLFPSSettingsInput adlSettings{};
							adlSettings.bGlobalSettings = true;
							adlSettings.ulACFPSCurrent = 0;
							adlSettings.ulDCFPSCurrent = 0;
							adl_Res0 = _ADL2_FPS_Settings_Set(adl_Context, gpuAdapterIndex, adlSettings);
						}
					}
				}
			}
			catch (...) {}

			//OpenGL 10-Bit Pixel Format
			try
			{
				if (targetSettings.OpenGL10BitPixelFormat.Get(settingGet).has_value())
				{
					//Get value
					auto newValue = targetSettings.OpenGL10BitPixelFormat.Get(settingGet).value();

					//Check application type
					if (targetSettings.Global())
					{
						//Enumeration index correction
						int setValue = 1;
						if (newValue)
						{
							setValue = 1;
						}
						else
						{
							setValue = 2;
						}

						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "", "KMD_10BitMode", setValue);
						AdlRegistrySettingSet(gpuAdapterIndex, "", "Gmx_Enable10BitMode", setValue);
					}
				}
			}
			catch (...) {}

			//Update properties for ADL application
			if (!targetSettings.Global())
			{
				//Set setting
				return AdlAppPropertyUpdate(adlApp, adlAppProperties, false);
			}

			//Return result
			return true;
		}
		catch (...)
		{
			//Return result
			return false;
		}
	}
}