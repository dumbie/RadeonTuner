#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::AdlGraphicsSettingsApply(int gpuAdapterIndex, std::wstring gpuUniqueIdentifierHex, AdlApplication adlApp, GraphicsSettings targetSettings, AdlSettingGet settingGet)
	{
		try
		{
			//FSR Upscaling Override
			try
			{
				if (targetSettings.FsrOverride.Get(settingGet).has_value())
				{
					//Get value
					auto newValue = targetSettings.FsrOverride.Get(settingGet).value();

					//Check application type
					if (adlApp.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "FsrOverride", number_to_wstring(newValue));
					}
					else
					{
						//Set setting
						AdlAppPropertyUpdate(adlApp, gpuUniqueIdentifierHex, L"FsrOverride", number_to_wstring(newValue));
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
					if (adlApp.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "MlfiOverride", number_to_wstring(newValue));
					}
					else
					{
						//Set setting
						AdlAppPropertyUpdate(adlApp, gpuUniqueIdentifierHex, L"MlfiOverride", number_to_wstring(newValue));
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
					if (adlApp.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "MfgOverride", number_to_wstring(newValue));
					}
					else
					{
						//Set setting
						AdlAppPropertyUpdate(adlApp, gpuUniqueIdentifierHex, L"MfgOverride", number_to_wstring(newValue));
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
					if (adlApp.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "MldOverride", number_to_wstring(newValue));
					}
					else
					{
						//Set setting
						AdlAppPropertyUpdate(adlApp, gpuUniqueIdentifierHex, L"MldOverride", number_to_wstring(newValue));
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
					if (adlApp.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "NrcOverride", number_to_wstring(newValue));
					}
					else
					{
						//Set setting
						AdlAppPropertyUpdate(adlApp, gpuUniqueIdentifierHex, L"NrcOverride", number_to_wstring(newValue));
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
					if (adlApp.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "MfgRatio", setValue);
					}
					else
					{
						//Set setting
						AdlAppPropertyUpdate(adlApp, gpuUniqueIdentifierHex, L"MfgRatio", setValue);
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
					if (adlApp.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "FsrOvrDLLPath", newValue);
					}
					else
					{
						//Set setting
						//AdlAppPropertyUpdate(adlApp, gpuUniqueIdentifierHex, L"FfxDllPath", targetSettings.FsrOvrDLLPath.Get(settingGet).value());
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
					if (adlApp.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "FsrOtaIndex", number_to_wstring(newValue));
					}
					else
					{
						//Set setting
						AdlAppPropertyUpdate(adlApp, gpuUniqueIdentifierHex, L"FsrOtaIndex", number_to_wstring(newValue));
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
					if (adlApp.Global())
					{
						//Set setting
						ADL_DELAG_SETTINGS adlSettings{};
						adlSettings.GlobalEnable = newValue;

						ADL_DELAG_NOTFICATION_REASON adlNotificationReason{};
						adlNotificationReason.GlobalEnableChanged = true;

						ADL_ERROR_REASON2 adlErrorReason;
						adl_Res0 = _ADL2_DELAG_SettingsX2_Set(adl_Context, gpuAdapterIndex, adlSettings, adlNotificationReason, &adlErrorReason);

						//Notify change
						_ADL2_User_Settings_Notify(adl_Context, gpuAdapterIndex, ADL_USER_SETTINGS_DELAG_PROFILE, ADL_TRUE);
					}
					else
					{
						//Set setting
						AdlAppPropertyUpdate(adlApp, gpuUniqueIdentifierHex, L"Dlg_PFEnable", number_to_wstring(newValue));
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
					if (adlApp.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "TurboSync", number_to_wstring(newValue));

						//Notify change
						_ADL2_User_Settings_Notify(adl_Context, gpuAdapterIndex, ADL_USER_SETTINGS_ENHANCEDSYNC, ADL_TRUE);
					}
					else
					{
						//Set setting
						AdlAppPropertyUpdate(adlApp, gpuUniqueIdentifierHex, L"TurboSync", number_to_wstring(newValue));
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
					if (adlApp.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "VSyncControl", number_to_wstring(newValue));
					}
					else
					{
						//Set setting
						AdlAppPropertyUpdate(adlApp, gpuUniqueIdentifierHex, L"VSyncControl", number_to_wstring(newValue));
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
					if (adlApp.Global())
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
					if (adlApp.Global())
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
					if (adlApp.Global())
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
					if (adlApp.Global())
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
					if (adlApp.Global())
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
					if (adlApp.Global())
					{
						//Set setting
						ADL_CHILL_SETTINGS adlSettings{};
						adlSettings.GlobalEnable = newValue;

						ADL_CHILL_NOTFICATION_REASON adlNotificationReason{};
						adlNotificationReason.GlobalEnableChanged = true;

						ADL_ERROR_REASON adlErrorReason;
						adl_Res0 = _ADL2_CHILL_SettingsX2_Set(adl_Context, gpuAdapterIndex, adlSettings, adlNotificationReason, &adlErrorReason);

						//Notify change
						_ADL2_User_Settings_Notify(adl_Context, gpuAdapterIndex, ADL_USER_SETTINGS_CHILL_PROFILE, ADL_TRUE);
					}
					else
					{
						//Set setting
						AdlAppPropertyUpdate(adlApp, gpuUniqueIdentifierHex, L"Chil_PFEnable", number_to_wstring(newValue));
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
					if (adlApp.Global())
					{
						//Set setting
						ADL_CHILL_SETTINGS adlSettings{};
						adlSettings.GlobalMinFPS = newValue;

						ADL_CHILL_NOTFICATION_REASON adlNotificationReason{};
						adlNotificationReason.GlobalMinFPSChanged = true;

						ADL_ERROR_REASON adlErrorReason;
						adl_Res0 = _ADL2_CHILL_SettingsX2_Set(adl_Context, gpuAdapterIndex, adlSettings, adlNotificationReason, &adlErrorReason);

						//Notify change
						_ADL2_User_Settings_Notify(adl_Context, gpuAdapterIndex, ADL_USER_SETTINGS_CHILL_PROFILE, ADL_TRUE);
					}
					else
					{
						//Set setting
						AdlAppPropertyUpdate(adlApp, gpuUniqueIdentifierHex, L"Chil_MinFRate", number_to_wstring(newValue));
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
					if (adlApp.Global())
					{
						//Set setting
						ADL_CHILL_SETTINGS adlSettings{};
						adlSettings.GlobalMaxFPS = newValue;

						ADL_CHILL_NOTFICATION_REASON adlNotificationReason{};
						adlNotificationReason.GlobalMaxFPSChanged = true;

						ADL_ERROR_REASON adlErrorReason;
						adl_Res0 = _ADL2_CHILL_SettingsX2_Set(adl_Context, gpuAdapterIndex, adlSettings, adlNotificationReason, &adlErrorReason);

						//Notify change
						_ADL2_User_Settings_Notify(adl_Context, gpuAdapterIndex, ADL_USER_SETTINGS_CHILL_PROFILE, ADL_TRUE);
					}
					else
					{
						//Set setting
						AdlAppPropertyUpdate(adlApp, gpuUniqueIdentifierHex, L"Chil_MaxFRate", number_to_wstring(newValue));
					}
				}
			}
			catch (...) {}

			//Radeon Boost
			try
			{
				if (targetSettings.BoostEnabled.Get(settingGet).has_value())
				{
					//Get value
					auto newValue = targetSettings.BoostEnabled.Get(settingGet).value();

					//Check application type
					if (adlApp.Global())
					{
						//Set setting
						ADL_BOOST_SETTINGS adlSettings{};
						adlSettings.GlobalEnable = newValue;

						ADL_BOOST_NOTFICATION_REASON adlNotificationReason{};
						adlNotificationReason.GlobalEnableChanged = true;

						ADL_ERROR_REASON2 adlErrorReason;
						adl_Res0 = _ADL2_BOOST_SettingsX2_Set(adl_Context, gpuAdapterIndex, adlSettings, adlNotificationReason, &adlErrorReason);

						//Notify change
						_ADL2_User_Settings_Notify(adl_Context, gpuAdapterIndex, ADL_USER_SETTINGS_BOOST_PROFILE, ADL_TRUE);
					}
					else
					{
						//Set setting
						AdlAppPropertyUpdate(adlApp, gpuUniqueIdentifierHex, L"Bst_PFEnable", number_to_wstring(newValue));
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
					if (adlApp.Global())
					{
						//Set setting
						ADL_BOOST_SETTINGS adlSettings{};
						adlSettings.GlobalMinRes = newValue;

						ADL_BOOST_NOTFICATION_REASON adlNotificationReason{};
						adlNotificationReason.GlobalMinResChanged = true;

						ADL_ERROR_REASON2 adlErrorReason;
						adl_Res0 = _ADL2_BOOST_SettingsX2_Set(adl_Context, gpuAdapterIndex, adlSettings, adlNotificationReason, &adlErrorReason);

						//Notify change
						_ADL2_User_Settings_Notify(adl_Context, gpuAdapterIndex, ADL_USER_SETTINGS_BOOST_PROFILE, ADL_TRUE);
					}
					else
					{
						//Set setting
						AdlAppPropertyUpdate(adlApp, gpuUniqueIdentifierHex, L"Bst_MaxScale", number_to_wstring(newValue));
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
					auto newValue = targetSettings.RisEnabled.Get(settingGet).value();
					auto sharpeningValueGlobal = targetSettings.RisSharpeningDegree.Get(settingGet).value();
					float sharpeningValueApp = (float)sharpeningValueGlobal / 100.0F;

					//Check application type
					if (adlApp.Global())
					{
						//Set setting
						ADL_RIS_SETTINGS adlSettings{};
						adlSettings.GlobalEnable = newValue;
						adlSettings.GlobalSharpeningDegree = sharpeningValueGlobal;

						ADL_RIS_NOTFICATION_REASON adlNotificationReason{};
						adlNotificationReason.GlobalEnableChanged = true;
						adlNotificationReason.GlobalSharpeningDegreeChanged = true;

						adl_Res0 = _ADL2_RIS_Settings_Set(adl_Context, gpuAdapterIndex, adlSettings, adlNotificationReason);

						//Notify change
						_ADL2_User_Settings_Notify(adl_Context, gpuAdapterIndex, ADL_USER_SETTINGS_USU_PROFILE, ADL_TRUE);
					}
					else
					{
						//Set setting
						AdlAppPropertyUpdate(adlApp, gpuUniqueIdentifierHex, L"Ris_PFEnable", number_to_wstring(newValue));
						AdlAppPropertyUpdate(adlApp, gpuUniqueIdentifierHex, L"Ris_SHDegree", float_to_wstring(sharpeningValueApp, 1));
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
					auto newValue = targetSettings.Ris2Enabled.Get(settingGet).value();
					auto desktopValue = targetSettings.Ris2DesktopEnabled.Get(settingGet).value();
					auto sharpeningValue = targetSettings.Ris2SharpeningDegree.Get(settingGet).value();

					//Check application type
					if (adlApp.Global())
					{
						//Set setting
						ADL_RIS2_SETTINGS adlSettings{};
						adlSettings.GlobalEnable = newValue;
						adlSettings.GlobalDesktop = desktopValue;
						adlSettings.GlobalSharpeningDegree = sharpeningValue;

						ADL_RIS2_NOTIFICATION_REASON adlNotificationReason{};
						adlNotificationReason.GlobalEnableChanged = true;
						adlNotificationReason.GlobalDesktopChanged = true;
						adlNotificationReason.GlobalSharpeningDegreeChanged = true;

						adl_Res0 = _ADL2_RIS_SettingsX2_Set(adl_Context, gpuAdapterIndex, adlSettings, adlNotificationReason);

						//Notify change
						_ADL2_User_Settings_Notify(adl_Context, gpuAdapterIndex, ADL_USER_SETTINGS_USU2_PROFILE, ADL_TRUE);
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

					//Check application type
					std::wstring setValue = newValue ? L"2" : L"1";
					if (adlApp.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "AntiAlias", setValue);
					}
					else
					{
						//Set setting
						AdlAppPropertyUpdate(adlApp, gpuUniqueIdentifierHex, L"AntiAlias", setValue);
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
					if (adlApp.Global())
					{
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "ASD", setValueAsd);
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "ASE", setValueAse);
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "ASTT", setValueAstt);
					}
					else
					{
						std::vector<AdlAppProperty> adlAppProperties{};

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

						//Set setting
						AdlAppPropertyUpdate(adlApp, adlAppProperties, false);
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
					if (adlApp.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "AntiAliasSamples", setValue);
					}
					else
					{
						//Set setting
						AdlAppPropertyUpdate(adlApp, gpuUniqueIdentifierHex, L"AntiAliasSmpls", setValue);
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
					if (adlApp.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "EQAA", number_to_wstring(newValue));
					}
					else
					{
						//Set setting
						AdlAppPropertyUpdate(adlApp, gpuUniqueIdentifierHex, L"EQAA", number_to_wstring(newValue));
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
					if (adlApp.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "MLF", number_to_wstring(newValue));
					}
					else
					{
						//Set setting
						AdlAppPropertyUpdate(adlApp, gpuUniqueIdentifierHex, L"MLF", number_to_wstring(newValue));
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
					if (adlApp.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "AnisoDegree", setValue);
					}
					else
					{
						//Set setting
						AdlAppPropertyUpdate(adlApp, gpuUniqueIdentifierHex, L"AnisoDegree", setValue);
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
					if (adlApp.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "Tessellation_OPTION", number_to_wstring(newValue));
					}
					else
					{
						//Set setting
						AdlAppPropertyUpdate(adlApp, gpuUniqueIdentifierHex, L"Tessellation_OP", number_to_wstring(newValue));
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
					if (adlApp.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "Tessellation", setValue);
					}
					else
					{
						//Set setting
						AdlAppPropertyUpdate(adlApp, gpuUniqueIdentifierHex, L"Tessellation", setValue);
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

					if (adlApp.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "EnableTripleBuffering", number_to_wstring(newValue));
					}
					else
					{
						//Set setting
						AdlAppPropertyUpdate(adlApp, gpuUniqueIdentifierHex, L"EnableTrplBffr", number_to_wstring(newValue));
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
					if (adlApp.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "TFQ", number_to_wstring(newValue));
					}
					else
					{
						//Set setting
						AdlAppPropertyUpdate(adlApp, gpuUniqueIdentifierHex, L"TFQ", number_to_wstring(newValue));
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
					if (adlApp.Global())
					{
						//Set setting
						AdlRegistrySettingSet(gpuAdapterIndex, "UMD", "SurfaceFormatReplacements", number_to_wstring(newValue));
					}
					else
					{
						//Set setting
						AdlAppPropertyUpdate(adlApp, gpuUniqueIdentifierHex, L"SrfcFrmtRplcmnt", number_to_wstring(newValue));
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
					if (adlApp.Global())
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
					if (adlApp.Global())
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
					if (adlApp.Global())
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