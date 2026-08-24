#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	std::optional<GraphicsSettings> MainPage::GraphicsSettings_Generate_FromADLRegistry(int gpuAdapterIndex, std::wstring application, bool loadDefault)
	{
		try
		{
			AVDebugWriteLine(L"Generating registry graphics settings for: " << gpuAdapterIndex << L" / " << application);
			GraphicsSettings graphicsSettings{};

			//Get graphics settings support
			GraphicsSettings graphicsSettingsSupport = GraphicsSettingsGetSupport(gpuAdapterIndex);

			//Device identifier
			graphicsSettings.DeviceId = AdlxGetGpuIdentifier(gpuAdapterIndex);

			//Device application
			graphicsSettings.Application = application;

			//FSR Upscaling Override
			//Note: When using Driver only software type this setting is disabled, Default type it is enabled by default
			try
			{
				//Set support
				graphicsSettings.FsrOverride.Support = graphicsSettingsSupport.FsrOverride.Support;

				//Set default
				graphicsSettings.FsrOverride.Default = 0;

				auto adlRegistry = AdlRegistrySettingGetString(gpuAdapterIndex, "UMD", "FsrOverride", true);
				if (adlRegistry.has_value())
				{
					//Set current
					int convertedValue = wstring_to_int(adlRegistry.value());
					graphicsSettings.FsrOverride.Current = convertedValue;
				}
			}
			catch (...) {}

			//FSR Frame Generation Override
			try
			{
				//Set support
				graphicsSettings.MlfiOverride.Support = graphicsSettingsSupport.MlfiOverride.Support;

				//Set default
				graphicsSettings.MlfiOverride.Default = 0;

				auto adlRegistry = AdlRegistrySettingGetString(gpuAdapterIndex, "UMD", "MlfiOverride", true);
				if (adlRegistry.has_value())
				{
					//Set current
					int convertedValue = wstring_to_int(adlRegistry.value());
					graphicsSettings.MlfiOverride.Current = convertedValue;
				}
			}
			catch (...) {}

			//FSR Multi Frame Generation Override
			try
			{
				//Set support
				graphicsSettings.MfgOverride.Support = graphicsSettingsSupport.MfgOverride.Support;

				//Set default
				graphicsSettings.MfgOverride.Default = 0;

				auto adlRegistry = AdlRegistrySettingGetString(gpuAdapterIndex, "UMD", "MfgOverride", true);
				if (adlRegistry.has_value())
				{
					//Set current
					int convertedValue = wstring_to_int(adlRegistry.value());
					graphicsSettings.MfgOverride.Current = convertedValue;
				}
			}
			catch (...) {}

			//FSR Ray Regeneration Denoiser Override
			try
			{
				//Set support
				graphicsSettings.MldOverride.Support = graphicsSettingsSupport.MldOverride.Support;

				//Set default
				graphicsSettings.MldOverride.Default = 0;

				auto adlRegistry = AdlRegistrySettingGetString(gpuAdapterIndex, "UMD", "MldOverride", true);
				if (adlRegistry.has_value())
				{
					//Set current
					int convertedValue = wstring_to_int(adlRegistry.value());
					graphicsSettings.MldOverride.Current = convertedValue;
				}
			}
			catch (...) {}

			//FSR Neural Radiance Caching Override
			try
			{
				//Set support
				graphicsSettings.NrcOverride.Support = graphicsSettingsSupport.NrcOverride.Support;

				//Set default
				graphicsSettings.NrcOverride.Default = 0;

				auto adlRegistry = AdlRegistrySettingGetString(gpuAdapterIndex, "UMD", "NrcOverride", true);
				if (adlRegistry.has_value())
				{
					//Set current
					int convertedValue = wstring_to_int(adlRegistry.value());
					graphicsSettings.NrcOverride.Current = convertedValue;
				}
			}
			catch (...) {}

			//FSR Multi Frame Generation Ratio
			try
			{
				//Set support
				graphicsSettings.MfgRatio.Support = graphicsSettingsSupport.MfgRatio.Support;

				//Set default
				graphicsSettings.MfgRatio.Default = 0;

				auto adlRegistry = AdlRegistrySettingGetString(gpuAdapterIndex, "UMD", "MfgRatio", true);
				if (adlRegistry.has_value())
				{
					//Set current
					int convertedValue = wstring_to_int(adlRegistry.value());

					//Enumeration index correction
					if (convertedValue == 0)
					{
						graphicsSettings.MfgRatio.Current = 0;
					}
					else if (convertedValue == 2)
					{
						graphicsSettings.MfgRatio.Current = 1;
					}
					else if (convertedValue == 3)
					{
						graphicsSettings.MfgRatio.Current = 2;
					}
					else if (convertedValue == 4)
					{
						graphicsSettings.MfgRatio.Current = 3;
					}
				}
			}
			catch (...) {}

			//FSR Override Library
			try
			{
				//Set support
				graphicsSettings.FsrOvrDLLPath.Support = graphicsSettingsSupport.FsrOvrDLLPath.Support;

				//Set default
				graphicsSettings.FsrOvrDLLPath.Default = FsrOverrideDllGetPathDefault();

				auto adlRegistry = AdlRegistrySettingGetString(gpuAdapterIndex, "UMD", "FsrOvrDLLPath", true);
				if (adlRegistry.has_value())
				{
					//Set current
					graphicsSettings.FsrOvrDLLPath.Current = adlRegistry.value();
				}
			}
			catch (...) {}

			//FSR Over-The-Air Updates
			try
			{
				//Set support
				graphicsSettings.FsrOtaIndex.Support = graphicsSettingsSupport.FsrOtaIndex.Support;

				//Set default
				graphicsSettings.FsrOtaIndex.Default = 1;

				auto adlRegistry = AdlRegistrySettingGetString(gpuAdapterIndex, "UMD", "FsrOtaIndex", true);
				if (adlRegistry.has_value())
				{
					//Set current
					int convertedValue = wstring_to_int(adlRegistry.value());
					graphicsSettings.FsrOtaIndex.Current = convertedValue;
				}
			}
			catch (...) {}

			//FSR Show Information
			try
			{
				//Set support
				graphicsSettings.FsrShowInformation.Support = graphicsSettingsSupport.FsrShowInformation.Support;

				//Set default
				graphicsSettings.FsrShowInformation.Default = 0;

				//Set current
				graphicsSettings.FsrShowInformation.Current = FsrShowInformationIsEnabled();
			}
			catch (...) {}

			//FSR Latency Reduction
			try
			{
				//Set support
				graphicsSettings.DeLagEnabled.Support = graphicsSettingsSupport.DeLagEnabled.Support;

				ADL_DELAG_SETTINGSX4 adlSettings;
				adl_Res0 = _ADL2_DELAG_SettingsX4_Get(adl_Context, gpuAdapterIndex, &adlSettings);
				if (adl_Res0 == ADL_OK)
				{
					//Set current
					graphicsSettings.DeLagEnabled.Current = adlSettings.GlobalEnable;

					//Set default
					graphicsSettings.DeLagEnabled.Default = 0;
				}
			}
			catch (...) {}

			//Radeon Fluid Motion Frames
			try
			{
				//Set support
				graphicsSettings.FrameGenEnabled.Support = graphicsSettingsSupport.FrameGenEnabled.Support;

				int fmfEnabled = -1;
				adl_Res0 = _ADL2_DriverFrameGeneration_Settings_Get(adl_Context, gpuAdapterIndex, &fmfEnabled);
				if (adl_Res0 == ADL_OK)
				{
					//Set current
					graphicsSettings.FrameGenEnabled.Current = fmfEnabled;

					//Set default
					graphicsSettings.FrameGenEnabled.Default = 0;
				}
			}
			catch (...) {}

			//Radeon Fluid Motion Search Mode setting
			try
			{
				//Set support
				graphicsSettings.FrameGenSearchMode.Support = graphicsSettingsSupport.FrameGenSearchMode.Support;

				//Set default
				graphicsSettings.FrameGenSearchMode.Default = 0;

				auto resultDword = RegistryGetDword(HKEY_ENUM::CURRENT_USER, L"Software\\AMD\\DVR", L"FrameGenSearchMode");
				if (resultDword.has_value())
				{
					//Set current
					graphicsSettings.FrameGenSearchMode.Current = resultDword.value();
				}
			}
			catch (...) {}

			//Radeon Fluid Motion Performance Mode setting
			try
			{
				//Set support
				graphicsSettings.FrameGenPerfMode.Support = graphicsSettingsSupport.FrameGenPerfMode.Support;

				//Set default
				graphicsSettings.FrameGenPerfMode.Default = 0;

				auto resultDword = RegistryGetDword(HKEY_ENUM::CURRENT_USER, L"Software\\AMD\\DVR", L"FrameGenPerfMode");
				if (resultDword.has_value())
				{
					//Set current
					graphicsSettings.FrameGenPerfMode.Current = resultDword.value();
				}
			}
			catch (...) {}

			//Radeon Fluid Motion Response Mode setting
			try
			{
				//Set support
				graphicsSettings.FrameGenResponseMode.Support = graphicsSettingsSupport.FrameGenResponseMode.Support;

				//Set default
				graphicsSettings.FrameGenResponseMode.Default = 0;

				auto resultDword = RegistryGetDword(HKEY_ENUM::CURRENT_USER, L"Software\\AMD\\DVR", L"FrameGenFallbackMode");
				if (resultDword.has_value())
				{
					//Set current
					graphicsSettings.FrameGenResponseMode.Current = resultDword.value();
				}
			}
			catch (...) {}

			//Radeon Fluid Motion Algorithm setting
			try
			{
				//Set support
				graphicsSettings.FrameGenAlgorithm.Support = graphicsSettingsSupport.FrameGenAlgorithm.Support;

				//Set default
				graphicsSettings.FrameGenAlgorithm.Default = 0;

				auto resultDword = RegistryGetDword(HKEY_ENUM::CURRENT_USER, L"Software\\AMD\\DVR", L"FrameGenAlgorithm");
				if (resultDword.has_value())
				{
					//Set current
					graphicsSettings.FrameGenAlgorithm.Current = resultDword.value();
				}
			}
			catch (...) {}

			//Radeon Boost
			try
			{
				//Set support
				graphicsSettings.BoostMode.Support = graphicsSettingsSupport.BoostMode.Support;
				graphicsSettings.BoostMinResolution.Support = graphicsSettingsSupport.BoostMinResolution.Support;

				ADL_BOOST_SETTINGSX4 adlSettings;
				adl_Res0 = _ADL2_BOOST_SettingsX4_Get(adl_Context, gpuAdapterIndex, &adlSettings);
				if (adl_Res0 == ADL_OK)
				{
					//Enumeration index correction
					if (!adlSettings.GlobalEnable && !adlSettings.AdaptiveVrsEnabled)
					{
						//Disabled
						graphicsSettings.BoostMode.Current = 0;
					}
					else if (adlSettings.GlobalEnable && !adlSettings.AdaptiveVrsEnabled)
					{
						//Input-Based
						graphicsSettings.BoostMode.Current = 1;
					}
					else if (!adlSettings.GlobalEnable && adlSettings.AdaptiveVrsEnabled)
					{
						//Scene-Based
						graphicsSettings.BoostMode.Current = 2;
					}
					else if (adlSettings.GlobalEnable && adlSettings.AdaptiveVrsEnabled)
					{
						//Multi-Modal
						graphicsSettings.BoostMode.Current = 3;
					}

					//Set current
					graphicsSettings.BoostMinResolution.Current = adlSettings.GlobalMinRes;

					//Set interface
					graphicsSettings.BoostMinResolution.Minimum = adlSettings.GlobalMinRes_MinLimit;
					graphicsSettings.BoostMinResolution.Maximum = adlSettings.GlobalMinRes_MaxLimit;
					graphicsSettings.BoostMinResolution.Step = adlSettings.GlobalMinRes_Step;

					//Set default
					graphicsSettings.BoostMode.Default = 0;
					graphicsSettings.BoostMinResolution.Default = 84;
				}
			}
			catch (...) {}

			//Radeon Frame Rate Target Control
			try
			{
				//Set support
				graphicsSettings.FrtcEnabled.Support = graphicsSettingsSupport.FrtcEnabled.Support;
				graphicsSettings.FrtcFrameRateTarget.Support = graphicsSettingsSupport.FrtcFrameRateTarget.Support;

				ADLFPSSettingsOutput adlSettings;
				adl_Res0 = _ADL2_FPS_Settings_Get(adl_Context, gpuAdapterIndex, &adlSettings);
				if (adl_Res0 == ADL_OK)
				{
					//Set current
					graphicsSettings.FrtcEnabled.Current = adlSettings.bACFPSEnabled;
					graphicsSettings.FrtcFrameRateTarget.Current = adlSettings.ulACFPSCurrent;

					//Set interface
					graphicsSettings.FrtcFrameRateTarget.Minimum = adlSettings.ulACFPSMinimum;
					graphicsSettings.FrtcFrameRateTarget.Maximum = adlSettings.ulACFPSMaximum;
					graphicsSettings.FrtcFrameRateTarget.Step = 1;

					//Set default
					graphicsSettings.FrtcEnabled.Default = 0;
					graphicsSettings.FrtcFrameRateTarget.Default = 60;
				}
			}
			catch (...) {}

			//Radeon Chill
			try
			{
				//Set support
				graphicsSettings.ChillEnabled.Support = graphicsSettingsSupport.ChillEnabled.Support;
				graphicsSettings.ChillMinFps.Support = graphicsSettingsSupport.ChillMinFps.Support;
				graphicsSettings.ChillMaxFps.Support = graphicsSettingsSupport.ChillMaxFps.Support;

				ADL_CHILL_SETTINGS adlSettings;
				adl_Res0 = _ADL2_CHILL_SettingsX2_Get(adl_Context, gpuAdapterIndex, &adlSettings);
				if (adl_Res0 == ADL_OK)
				{
					//Set current
					graphicsSettings.ChillEnabled.Current = adlSettings.GlobalEnable;
					graphicsSettings.ChillMinFps.Current = adlSettings.GlobalMinFPS;
					graphicsSettings.ChillMaxFps.Current = adlSettings.GlobalMaxFPS;

					//Set interface
					graphicsSettings.ChillMinFps.Minimum = adlSettings.GlobalFPS_MinLimit;
					graphicsSettings.ChillMinFps.Maximum = adlSettings.GlobalFPS_MaxLimit;
					graphicsSettings.ChillMinFps.Step = adlSettings.GlobalFPS_Step;
					graphicsSettings.ChillMaxFps.Minimum = adlSettings.GlobalFPS_MinLimit;
					graphicsSettings.ChillMaxFps.Maximum = adlSettings.GlobalFPS_MaxLimit;
					graphicsSettings.ChillMaxFps.Step = adlSettings.GlobalFPS_Step;

					//Set default
					graphicsSettings.ChillEnabled.Default = 0;
					graphicsSettings.ChillMinFps.Default = 75;
					graphicsSettings.ChillMaxFps.Default = 140;
				}
			}
			catch (...) {}

			//Radeon Image Sharpening 1
			try
			{
				//Set support
				graphicsSettings.RisEnabled.Support = graphicsSettingsSupport.RisEnabled.Support;
				graphicsSettings.RisSharpeningDegree.Support = graphicsSettingsSupport.RisSharpeningDegree.Support;

				ADL_RIS_SETTINGS adlSettings;
				adl_Res0 = _ADL2_RIS_Settings_Get(adl_Context, gpuAdapterIndex, &adlSettings);
				if (adl_Res0 == ADL_OK)
				{
					//Set current
					graphicsSettings.RisEnabled.Current = adlSettings.GlobalEnable;
					graphicsSettings.RisSharpeningDegree.Current = adlSettings.GlobalSharpeningDegree;

					//Set interface
					graphicsSettings.RisSharpeningDegree.Minimum = adlSettings.GlobalSharpeningDegree_MinLimit;
					graphicsSettings.RisSharpeningDegree.Maximum = adlSettings.GlobalSharpeningDegree_MaxLimit;
					graphicsSettings.RisSharpeningDegree.Step = adlSettings.GlobalSharpeningDegree_Step;

					//Set default
					graphicsSettings.RisEnabled.Default = 0;
					graphicsSettings.RisSharpeningDegree.Default = 80;
				}
			}
			catch (...) {}

			//Radeon Image Sharpening 2
			try
			{
				//Set support
				graphicsSettings.Ris2Enabled.Support = graphicsSettingsSupport.Ris2Enabled.Support;
				graphicsSettings.Ris2DesktopEnabled.Support = graphicsSettingsSupport.Ris2DesktopEnabled.Support;
				graphicsSettings.Ris2SharpeningDegree.Support = graphicsSettingsSupport.Ris2SharpeningDegree.Support;

				ADL_RIS2_SETTINGS adlSettings;
				adl_Res0 = _ADL2_RIS_SettingsX2_Get(adl_Context, gpuAdapterIndex, &adlSettings);
				if (adl_Res0 == ADL_OK)
				{
					//Set current
					graphicsSettings.Ris2Enabled.Current = adlSettings.GlobalEnable;
					graphicsSettings.Ris2DesktopEnabled.Current = adlSettings.GlobalDesktop;
					graphicsSettings.Ris2SharpeningDegree.Current = adlSettings.GlobalSharpeningDegree;

					//Set interface
					graphicsSettings.Ris2SharpeningDegree.Minimum = adlSettings.GlobalSharpeningDegree_MinLimit;
					graphicsSettings.Ris2SharpeningDegree.Maximum = adlSettings.GlobalSharpeningDegree_MaxLimit;
					graphicsSettings.Ris2SharpeningDegree.Step = adlSettings.GlobalSharpeningDegree_Step;

					//Set default
					graphicsSettings.Ris2Enabled.Default = 0;
					graphicsSettings.Ris2DesktopEnabled.Default = 0;
					graphicsSettings.Ris2SharpeningDegree.Default = 50;
				}
			}
			catch (...) {}

			//Enhanced Sync
			try
			{
				//Set support
				graphicsSettings.EnhancedSync.Support = graphicsSettingsSupport.EnhancedSync.Support;

				//Set default
				graphicsSettings.EnhancedSync.Default = 0;

				auto adlRegistry = AdlRegistrySettingGetString(gpuAdapterIndex, "UMD", "TurboSync", true);
				if (adlRegistry.has_value())
				{
					//Set current
					int convertedValue = wstring_to_int(adlRegistry.value());
					graphicsSettings.EnhancedSync.Current = convertedValue;
				}
			}
			catch (...) {}

			//Vertical Sync
			try
			{
				//Set support
				graphicsSettings.VerticalSync.Support = graphicsSettingsSupport.VerticalSync.Support;

				//Set default
				graphicsSettings.VerticalSync.Default = 1;

				auto adlRegistry = AdlRegistrySettingGetString(gpuAdapterIndex, "UMD", "VSyncControl", true);
				if (adlRegistry.has_value())
				{
					//Set current
					int convertedValue = wstring_to_int(adlRegistry.value());
					graphicsSettings.VerticalSync.Current = convertedValue;
				}
			}
			catch (...) {}

			//Anti-Aliasing Override
			try
			{
				//Set support
				graphicsSettings.AntiAliasingOverride.Support = graphicsSettingsSupport.AntiAliasingOverride.Support;

				//Set default
				graphicsSettings.AntiAliasingOverride.Default = 0;

				auto adlRegistry = AdlRegistrySettingGetString(gpuAdapterIndex, "UMD", "AntiAlias", true);
				if (adlRegistry.has_value())
				{
					//Set current
					bool convertedValue = adlRegistry.value() == L"2";
					graphicsSettings.AntiAliasingOverride.Current = convertedValue;
				}
			}
			catch (...) {}

			//Anti-Aliasing Method
			try
			{
				//Set support
				graphicsSettings.AntiAliasingMethod.Support = graphicsSettingsSupport.AntiAliasingMethod.Support;

				//Set default
				graphicsSettings.AntiAliasingMethod.Default = 0;

				auto adlRegistryASD = AdlRegistrySettingGetString(gpuAdapterIndex, "UMD", "ASD", true);
				auto adlRegistryASE = AdlRegistrySettingGetString(gpuAdapterIndex, "UMD", "ASE", true);
				auto adlRegistryASTT = AdlRegistrySettingGetString(gpuAdapterIndex, "UMD", "ASTT", true);
				if (adlRegistryASD.has_value() && adlRegistryASE.has_value() && adlRegistryASTT.has_value())
				{
					//Set current
					int asdValue = wstring_to_int(adlRegistryASD.value());
					int aseValue = wstring_to_int(adlRegistryASE.value());
					int asttValue = wstring_to_int(adlRegistryASTT.value());

					//Enumeration index correction
					if (asdValue == -1 && aseValue == 0 && asttValue == 0)
					{
						//Multisampling
						graphicsSettings.AntiAliasingMethod.Current = 0;
					}
					else if (asdValue == 1 && aseValue == 0 && asttValue == 1)
					{
						//Adaptive Multisampling
						graphicsSettings.AntiAliasingMethod.Current = 1;
					}
					else if (asdValue == 1 && aseValue == 1 && asttValue == 1)
					{
						//Supersampling
						graphicsSettings.AntiAliasingMethod.Current = 2;
					}
				}
			}
			catch (...) {}

			//Anti-Aliasing Level
			try
			{
				//Set support
				graphicsSettings.AntiAliasingLevel.Support = graphicsSettingsSupport.AntiAliasingLevel.Support;

				//Set default
				graphicsSettings.AntiAliasingLevel.Default = 0;

				auto adlRegistry = AdlRegistrySettingGetString(gpuAdapterIndex, "UMD", "AntiAliasSamples", true);
				if (adlRegistry.has_value())
				{
					//Set current
					int convertedValue = wstring_to_int(adlRegistry.value());

					//Enumeration index correction
					if (convertedValue == 2)
					{
						graphicsSettings.AntiAliasingLevel.Current = 0;
					}
					else if (convertedValue == 4)
					{
						graphicsSettings.AntiAliasingLevel.Current = 1;
					}
					else if (convertedValue == 8)
					{
						graphicsSettings.AntiAliasingLevel.Current = 2;
					}
				}
			}
			catch (...) {}

			//Enhanced Quality Anti-Aliasing
			try
			{
				//Set support
				graphicsSettings.AntiAliasingEnhancedQuality.Support = graphicsSettingsSupport.AntiAliasingEnhancedQuality.Support;

				//Set default
				graphicsSettings.AntiAliasingEnhancedQuality.Default = 0;

				auto adlRegistry = AdlRegistrySettingGetString(gpuAdapterIndex, "UMD", "EQAA", true);
				if (adlRegistry.has_value())
				{
					//Set current
					int convertedValue = wstring_to_int(adlRegistry.value());
					graphicsSettings.AntiAliasingEnhancedQuality.Current = convertedValue;
				}
			}
			catch (...) {}

			//Morphological Anti-Aliasing
			try
			{
				//Set support
				graphicsSettings.AntiAliasingMorphological.Support = graphicsSettingsSupport.AntiAliasingMorphological.Support;

				//Set default
				graphicsSettings.AntiAliasingMorphological.Default = 0;

				auto adlRegistry = AdlRegistrySettingGetString(gpuAdapterIndex, "UMD", "MLF", true);
				if (adlRegistry.has_value())
				{
					//Set current
					int convertedValue = wstring_to_int(adlRegistry.value());
					graphicsSettings.AntiAliasingMorphological.Current = convertedValue;
				}
			}
			catch (...) {}

			//Anisotropic Texture Filtering Override
			try
			{
				//Set support
				graphicsSettings.AnisotropicOverride.Support = graphicsSettingsSupport.AnisotropicOverride.Support;

				//Set default
				graphicsSettings.AnisotropicOverride.Default = 0;

				auto adlRegistry = AdlRegistrySettingGetString(gpuAdapterIndex, "UMD", "AnisoDegree", true);
				if (adlRegistry.has_value())
				{
					//Set current
					int convertedValue = wstring_to_int(adlRegistry.value());

					//Enumeration index correction
					if (convertedValue == 0)
					{
						graphicsSettings.AnisotropicOverride.Current = 0;
					}
					else if (convertedValue == 2)
					{
						graphicsSettings.AnisotropicOverride.Current = 1;
					}
					else if (convertedValue == 4)
					{
						graphicsSettings.AnisotropicOverride.Current = 2;
					}
					else if (convertedValue == 8)
					{
						graphicsSettings.AnisotropicOverride.Current = 3;
					}
					else if (convertedValue == 16)
					{
						graphicsSettings.AnisotropicOverride.Current = 4;
					}
				}
			}
			catch (...) {}

			//Texture Filtering Quality
			try
			{
				//Set support
				graphicsSettings.TextureFilteringQuality.Support = graphicsSettingsSupport.TextureFilteringQuality.Support;

				//Set default
				graphicsSettings.TextureFilteringQuality.Default = 1;

				auto adlRegistry = AdlRegistrySettingGetString(gpuAdapterIndex, "UMD", "TFQ", true);
				if (adlRegistry.has_value())
				{
					//Set current
					int convertedValue = wstring_to_int(adlRegistry.value());
					graphicsSettings.TextureFilteringQuality.Current = convertedValue;
				}
			}
			catch (...) {}

			//Surface Format Optimization
			try
			{
				//Set support
				graphicsSettings.SurfaceFormatOptimization.Support = graphicsSettingsSupport.SurfaceFormatOptimization.Support;

				//Set default
				graphicsSettings.SurfaceFormatOptimization.Default = 0;

				auto adlRegistry = AdlRegistrySettingGetString(gpuAdapterIndex, "UMD", "SurfaceFormatReplacements", true);
				if (adlRegistry.has_value())
				{
					//Set current
					int convertedValue = wstring_to_int(adlRegistry.value());
					graphicsSettings.SurfaceFormatOptimization.Current = convertedValue;
				}
			}
			catch (...) {}

			//Tessellation Mode
			try
			{
				//Set support
				graphicsSettings.TessellationMode.Support = graphicsSettingsSupport.TessellationMode.Support;

				//Set default
				graphicsSettings.TessellationMode.Default = 0;

				auto adlRegistry = AdlRegistrySettingGetString(gpuAdapterIndex, "UMD", "Tessellation_OPTION", true);
				if (adlRegistry.has_value())
				{
					//Set current
					int convertedValue = wstring_to_int(adlRegistry.value());
					graphicsSettings.TessellationMode.Current = convertedValue;
				}
			}
			catch (...) {}

			//Tessellation Level
			try
			{
				//Set support
				graphicsSettings.TessellationLevel.Support = graphicsSettingsSupport.TessellationLevel.Support;

				//Set default
				graphicsSettings.TessellationLevel.Default = 7;

				auto adlRegistry = AdlRegistrySettingGetString(gpuAdapterIndex, "UMD", "Tessellation", true);
				if (adlRegistry.has_value())
				{
					//Set current
					int convertedValue = wstring_to_int(adlRegistry.value());

					//Enumeration index correction
					if (convertedValue == 1)
					{
						graphicsSettings.TessellationLevel.Current = 0;
					}
					else if (convertedValue == 2)
					{
						graphicsSettings.TessellationLevel.Current = 1;
					}
					else if (convertedValue == 4)
					{
						graphicsSettings.TessellationLevel.Current = 2;
					}
					else if (convertedValue == 6)
					{
						graphicsSettings.TessellationLevel.Current = 3;
					}
					else if (convertedValue == 8)
					{
						graphicsSettings.TessellationLevel.Current = 4;
					}
					else if (convertedValue == 16)
					{
						graphicsSettings.TessellationLevel.Current = 5;
					}
					else if (convertedValue == 32)
					{
						graphicsSettings.TessellationLevel.Current = 6;
					}
					else if (convertedValue == 64)
					{
						graphicsSettings.TessellationLevel.Current = 7;
					}
				}
			}
			catch (...) {}

			//OpenGL Triple Buffering
			try
			{
				//Set support
				graphicsSettings.OpenGLTripleBuffering.Support = graphicsSettingsSupport.OpenGLTripleBuffering.Support;

				//Set default
				graphicsSettings.OpenGLTripleBuffering.Default = 0;

				auto adlRegistry = AdlRegistrySettingGetString(gpuAdapterIndex, "UMD", "EnableTripleBuffering", true);
				if (adlRegistry.has_value())
				{
					//Set current
					int convertedValue = wstring_to_int(adlRegistry.value());
					graphicsSettings.OpenGLTripleBuffering.Current = convertedValue;
				}
			}
			catch (...) {}

			//OpenGL 10-Bit Pixel Format
			try
			{
				//Set support
				graphicsSettings.OpenGL10BitPixelFormat.Support = graphicsSettingsSupport.OpenGL10BitPixelFormat.Support;

				//Set default
				graphicsSettings.OpenGL10BitPixelFormat.Default = 0;

				auto adlRegistry = AdlRegistrySettingGetString(gpuAdapterIndex, "", "KMD_10BitMode", true);
				if (adlRegistry.has_value())
				{
					//Set current
					int convertedValue = wstring_to_int(adlRegistry.value());

					//Enumeration index correction
					if (convertedValue == 1)
					{
						graphicsSettings.OpenGL10BitPixelFormat.Current = 1;
					}
					else if (convertedValue == 2)
					{
						graphicsSettings.OpenGL10BitPixelFormat.Current = 0;
					}
				}
			}
			catch (...) {}

			//Set current value to default value
			if (loadDefault)
			{
				graphicsSettings.SetCurrentToDefault();
			}

			//Return result
			return graphicsSettings;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("Failed to generate graphics settings from ADL registry.");
			return std::nullopt;
		}
	}
}