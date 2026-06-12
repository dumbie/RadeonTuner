#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlValuesLoadGraphicsRegistry()
	{
		try
		{
			//Get selected application
			auto selectedApp = AdlAppSelectedGet();

			//Check selected application
			if (!selectedApp.has_value())
			{
				AVDebugWriteLine("ADL application is not selected.");
				return;
			}

			//Fix find way to check if setting is supported and disable interface.

			//Set interface limits
			slider_RadeonBoost_MinRes().Minimum(50);
			slider_RadeonBoost_MinRes().Maximum(84);
			slider_RadeonBoost_MinRes().StepFrequency(17);
			slider_RadeonBoost_MinRes().SmallChange(17);

			slider_RadeonChill_Min().Minimum(30);
			slider_RadeonChill_Min().Maximum(1000);
			slider_RadeonChill_Min().StepFrequency(1);
			slider_RadeonChill_Min().SmallChange(1);

			slider_RadeonChill_Max().Minimum(30);
			slider_RadeonChill_Max().Maximum(1000);
			slider_RadeonChill_Max().StepFrequency(1);
			slider_RadeonChill_Max().SmallChange(1);

			slider_RadeonImageSharpening_Sharpening().Minimum(10);
			slider_RadeonImageSharpening_Sharpening().Maximum(100);
			slider_RadeonImageSharpening_Sharpening().StepFrequency(10);
			slider_RadeonImageSharpening_Sharpening().SmallChange(10);

			slider_Frtc_Fps().Minimum(15);
			slider_Frtc_Fps().Maximum(1000);
			slider_Frtc_Fps().StepFrequency(1);
			slider_Frtc_Fps().SmallChange(1);

			//Get FSR Upscaling Override
			{
				toggleswitch_FsrOverrideUpscaling().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "FsrOverride", true);
				if (adlRegistry.has_value())
				{
					bool convertedValue = (bool)wstring_to_int(adlRegistry.value());
					toggleswitch_FsrOverrideUpscaling().IsOn(convertedValue);
				}
				else
				{
					toggleswitch_FsrOverrideUpscaling().IsOn(false);
				}
			}

			//Get FSR Interpolation Frame Generation Override
			{
				toggleswitch_FsrOverrideInterpolationFrameGeneration().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "MlfiOverride", true);
				if (adlRegistry.has_value())
				{
					bool convertedValue = (bool)wstring_to_int(adlRegistry.value());
					toggleswitch_FsrOverrideInterpolationFrameGeneration().IsOn(convertedValue);
				}
				else
				{
					toggleswitch_FsrOverrideInterpolationFrameGeneration().IsOn(false);
				}
			}

			//Get FSR Multi Frame Generation Override
			{
				toggleswitch_FsrOverrideMultiFrameGeneration().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "MfgOverride", true);
				if (adlRegistry.has_value())
				{
					bool convertedValue = (bool)wstring_to_int(adlRegistry.value());
					toggleswitch_FsrOverrideMultiFrameGeneration().IsOn(convertedValue);
				}
				else
				{
					toggleswitch_FsrOverrideMultiFrameGeneration().IsOn(false);
				}
			}

			//Get FSR Ray Regeneration Denoiser Override
			{
				toggleswitch_FsrOverrideRayRegeneration().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "MldOverride", true);
				if (adlRegistry.has_value())
				{
					bool convertedValue = (bool)wstring_to_int(adlRegistry.value());
					toggleswitch_FsrOverrideRayRegeneration().IsOn(convertedValue);
				}
				else
				{
					toggleswitch_FsrOverrideRayRegeneration().IsOn(false);
				}
			}

			//Get FSR Neural Radiance Caching Override
			{
				toggleswitch_FsrOverrideNeuralRadianceCaching().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "NrcOverride", true);
				if (adlRegistry.has_value())
				{
					bool convertedValue = (bool)wstring_to_int(adlRegistry.value());
					toggleswitch_FsrOverrideNeuralRadianceCaching().IsOn(convertedValue);
				}
				else
				{
					toggleswitch_FsrOverrideNeuralRadianceCaching().IsOn(false);
				}
			}

			//Get FSR Multi Frame Generation Ratio
			{
				combobox_MultiFrameGenerationRatio().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "MfgRatio", true);
				if (adlRegistry.has_value())
				{
					int convertedValue = wstring_to_int(adlRegistry.value());

					//Enumeration index correction
					if (convertedValue == 0)
					{
						combobox_MultiFrameGenerationRatio().SelectedIndex(0);
					}
					else if (convertedValue == 1)
					{
						combobox_MultiFrameGenerationRatio().SelectedIndex(1);
					}
					else if (convertedValue == 2)
					{
						combobox_MultiFrameGenerationRatio().SelectedIndex(2);
					}
					else if (convertedValue == 4)
					{
						combobox_MultiFrameGenerationRatio().SelectedIndex(3);
					}
					else if (convertedValue == 6)
					{
						combobox_MultiFrameGenerationRatio().SelectedIndex(4);
					}
					else if (convertedValue == 8)
					{
						combobox_MultiFrameGenerationRatio().SelectedIndex(5);
					}
				}
			}

			//Get FSR Override DLL Path
			{
				button_FsrDllLoadPath_Default().IsEnabled(true);
				button_FsrDllLoadPath_Set().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "FsrOvrDLLPath", true);
				if (adlRegistry.has_value())
				{
					std::wstring dllPath = adlRegistry.value();
					std::wstring system32path = PathGetFolderKnown(FOLDERID_System);
					if (wstring_empty_whitespace(dllPath) || wstring_contains(dllPath, system32path))
					{
						textblock_FsrDllLoadPath().Text(L"Using default driver FSR DLL file.");
					}
					else
					{
						textblock_FsrDllLoadPath().Text(dllPath);
					}
				}
			}

			//Get FSR Over-The-Air Updates
			//Fix

			//Get FSR Latency Reduction
			{
				toggleswitch_FsrLatencyReduction().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "", "KMD_DeLagEnabled", true);
				if (adlRegistry.has_value())
				{
					bool convertedValue = (bool)wstring_to_int(adlRegistry.value());
					toggleswitch_FsrLatencyReduction().IsOn(convertedValue);
				}
				else
				{
					toggleswitch_FsrLatencyReduction().IsOn(false);
				}
			}

			//Get Radeon Boost
			{
				toggleswitch_RadeonBoost().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "", "KMD_RadeonBoostEnabled", true);
				if (adlRegistry.has_value())
				{
					bool convertedValue = (bool)wstring_to_int(adlRegistry.value());
					toggleswitch_RadeonBoost().IsOn(convertedValue);
				}
				else
				{
					toggleswitch_RadeonBoost().IsOn(false);
				}
			}

			//Get Radeon Boost Minimum Resolution
			{
				slider_RadeonBoost_MinRes().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "", "KMD_RadeonBoostMinResolution", true);
				if (adlRegistry.has_value())
				{
					int convertedValue = wstring_to_int(adlRegistry.value());
					slider_RadeonBoost_MinRes().Value(convertedValue);
				}
			}

			//Get Radeon Frame Rate Target Control
			try
			{
				toggleswitch_Frtc().IsEnabled(true);

				bool settingValue = false;
				IADLX3DFrameRateTargetControlPtr pp3DFrameRateTargetControl;
				adlx_Res0 = pp3DSettingsServices->GetFrameRateTargetControl(ppGpuInfo, &pp3DFrameRateTargetControl);
				adlx_Res0 = pp3DFrameRateTargetControl->IsEnabled(&settingValue);
				toggleswitch_Frtc().IsOn(settingValue);
			}
			catch (...) {}

			//Get Radeon Frame Rate Target Control Frame Rate
			try
			{
				slider_Frtc_Fps().IsEnabled(true);

				int settingValue = 0;
				IADLX3DFrameRateTargetControlPtr pp3DFrameRateTargetControl;
				adlx_Res0 = pp3DSettingsServices->GetFrameRateTargetControl(ppGpuInfo, &pp3DFrameRateTargetControl);
				adlx_Res0 = pp3DFrameRateTargetControl->GetFPS(&settingValue);
				slider_Frtc_Fps().Value(settingValue);
			}
			catch (...) {}

			//Get Radeon Chill
			{
				toggleswitch_RadeonChill().IsEnabled(true);
				slider_RadeonChill_Min().IsEnabled(true);
				slider_RadeonChill_Max().IsEnabled(true);
				button_RadeonChill_Link().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "", "KMD_ChillEnabled", true);
				if (adlRegistry.has_value())
				{
					bool convertedValue = (bool)wstring_to_int(adlRegistry.value());
					toggleswitch_RadeonChill().IsOn(convertedValue);
					if (convertedValue)
					{
						if (!radeon_Chill_Linked)
						{
							slider_RadeonChill_Min().IsEnabled(true);
						}
						else
						{
							slider_RadeonChill_Min().IsEnabled(false);
						}
					}
					else
					{
						slider_RadeonChill_Min().IsEnabled(convertedValue);
					}
					slider_RadeonChill_Max().IsEnabled(convertedValue);
					button_RadeonChill_Link().IsEnabled(convertedValue);
				}
			}

			//Get Radeon Chill Minimum Frame Rate
			{
				slider_RadeonChill_Min().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "", "KMD_ChillMinFps", true);
				if (adlRegistry.has_value())
				{
					int convertedValue = wstring_to_int(adlRegistry.value());
					slider_RadeonChill_Min().Value(convertedValue);
				}
			}

			//Get Radeon Chill Maximum Frame Rate
			{
				slider_RadeonChill_Max().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "", "KMD_ChillMaxFps", true);
				if (adlRegistry.has_value())
				{
					int convertedValue = wstring_to_int(adlRegistry.value());
					slider_RadeonChill_Max().Value(convertedValue);
				}
			}

			//Get Radeon Image Sharpening
			try
			{
				toggleswitch_RadeonImageSharpening().IsEnabled(true);

				bool settingValue = false;
				IADLX3DImageSharpeningPtr pp3DImageSharpening;
				adlx_Res0 = pp3DSettingsServices->GetImageSharpening(ppGpuInfo, &pp3DImageSharpening);
				adlx_Res0 = pp3DImageSharpening->IsEnabled(&settingValue);
				toggleswitch_RadeonImageSharpening().IsOn(settingValue);
			}
			catch (...){}

			//Get Radeon Image Sharpening Sharpness
			try
			{
				slider_RadeonImageSharpening_Sharpening().IsEnabled(true);

				int settingValue = 0;
				IADLX3DImageSharpeningPtr pp3DImageSharpening;
				adlx_Res0 = pp3DSettingsServices->GetImageSharpening(ppGpuInfo, &pp3DImageSharpening);
				adlx_Res0 = pp3DImageSharpening->GetSharpness(&settingValue);
				slider_RadeonImageSharpening_Sharpening().Value(settingValue);
			}
			catch (...) {}

			//Get Enhanced Sync
			{
				toggleswitch_RadeonEnhancedSync().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "TurboSync", true);
				if (adlRegistry.has_value())
				{
					bool convertedValue = (bool)wstring_to_int(adlRegistry.value());
					toggleswitch_RadeonEnhancedSync().IsOn(convertedValue);
				}
				else
				{
					toggleswitch_RadeonEnhancedSync().IsOn(false);
				}
			}

			//Get Vertical Refresh
			{
				combobox_VerticalRefresh().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "VSyncControl", true);
				if (adlRegistry.has_value())
				{
					int convertedValue = wstring_to_int(adlRegistry.value());
					combobox_VerticalRefresh().SelectedIndex(convertedValue);
				}
			}

			//Get Anti-Aliasing Override
			{
				toggleswitch_AntiAliasingOverride().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "AntiAlias", true);
				if (adlRegistry.has_value())
				{
					bool convertedValue = adlRegistry.value() == L"2";
					toggleswitch_AntiAliasingOverride().IsOn(convertedValue);
					combobox_AntiAliasingMethod().IsEnabled(convertedValue);
					combobox_AntiAliasingLevel().IsEnabled(convertedValue);
					toggleswitch_EQAA().IsEnabled(convertedValue);
				}
			}

			//Get Anti-Aliasing Method
			{
				auto adlRegistryASD = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "ASD", true);
				auto adlRegistryASE = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "ASE", true);
				auto adlRegistryASTT = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "ASTT", true);
				if (adlRegistryASD.has_value() && adlRegistryASE.has_value() && adlRegistryASTT.has_value())
				{
					int asdValue = wstring_to_int(adlRegistryASD.value());
					int aseValue = wstring_to_int(adlRegistryASE.value());
					int asttValue = wstring_to_int(adlRegistryASTT.value());

					//Enumeration index correction
					if (asdValue == -1 && aseValue == 0 && asttValue == 0)
					{
						//Multisampling
						combobox_AntiAliasingMethod().SelectedIndex(0);
					}
					else if (asdValue == 1 && aseValue == 0 && asttValue == 1)
					{
						//Adaptive Multisampling
						combobox_AntiAliasingMethod().SelectedIndex(1);
					}
					else if (asdValue == 1 && aseValue == 1 && asttValue == 1)
					{
						//Supersampling
						combobox_AntiAliasingMethod().SelectedIndex(2);
					}
				}
			}

			//Get Anti-Aliasing Level
			{
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "AntiAliasSamples", true);
				if (adlRegistry.has_value())
				{
					int convertedValue = wstring_to_int(adlRegistry.value());

					//Enumeration index correction
					if (convertedValue == 2)
					{
						combobox_AntiAliasingLevel().SelectedIndex(0);
					}
					else if (convertedValue == 4)
					{
						combobox_AntiAliasingLevel().SelectedIndex(1);
					}
					else if (convertedValue == 8)
					{
						combobox_AntiAliasingLevel().SelectedIndex(2);
					}
				}
			}

			//Get Enhanced Quality Anti-Aliasing
			{
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "EQAA", true);
				if (adlRegistry.has_value())
				{
					bool convertedValue = (bool)wstring_to_int(adlRegistry.value());
					toggleswitch_EQAA().IsOn(convertedValue);
				}
			}

			//Get Morphological Anti-Aliasing
			{
				toggleswitch_MorphologicalAntiAliasing().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "MLF", true);
				if (adlRegistry.has_value())
				{
					bool convertedValue = (bool)wstring_to_int(adlRegistry.value());
					toggleswitch_MorphologicalAntiAliasing().IsOn(convertedValue);
				}
			}

			//Get Anisotropic Texture Filtering Override
			{
				combobox_AnisotropicTextureFiltering_Level().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "AnisoDegree", true);
				if (adlRegistry.has_value())
				{
					int convertedValue = wstring_to_int(adlRegistry.value());

					//Enumeration index correction
					if (convertedValue == 0)
					{
						combobox_AnisotropicTextureFiltering_Level().SelectedIndex(0);
					}
					else if (convertedValue == 2)
					{
						combobox_AnisotropicTextureFiltering_Level().SelectedIndex(1);
					}
					else if (convertedValue == 4)
					{
						combobox_AnisotropicTextureFiltering_Level().SelectedIndex(2);
					}
					else if (convertedValue == 8)
					{
						combobox_AnisotropicTextureFiltering_Level().SelectedIndex(3);
					}
					else if (convertedValue == 16)
					{
						combobox_AnisotropicTextureFiltering_Level().SelectedIndex(4);
					}
				}
			}

			//Get Texture Filtering Quality
			{
				combobox_TextureFilteringQuality().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "TFQ", true);
				if (adlRegistry.has_value())
				{
					int convertedValue = wstring_to_int(adlRegistry.value());
					combobox_TextureFilteringQuality().SelectedIndex(convertedValue);
				}
			}

			//Get Surface Format Optimization
			{
				toggleswitch_SurfaceFormatOptimization().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "SurfaceFormatReplacements", true);
				if (adlRegistry.has_value())
				{
					bool convertedValue = (bool)wstring_to_int(adlRegistry.value());
					toggleswitch_SurfaceFormatOptimization().IsOn(convertedValue);
				}
			}

			//Get Tessellation Mode
			{
				combobox_Tessellation_Mode().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "Tessellation_OPTION", true);
				if (adlRegistry.has_value())
				{
					int convertedValue = wstring_to_int(adlRegistry.value());
					combobox_Tessellation_Mode().SelectedIndex(convertedValue);
					if (convertedValue != 2)
					{
						combobox_Tessellation_Level().IsEnabled(false);
					}
					else
					{
						combobox_Tessellation_Level().IsEnabled(true);
					}
				}
			}

			//Get Tessellation Level
			{
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "Tessellation", true);
				if (adlRegistry.has_value())
				{
					int convertedValue = wstring_to_int(adlRegistry.value());

					//Enumeration index correction
					if (convertedValue == 1)
					{
						combobox_Tessellation_Level().SelectedIndex(0);
					}
					else if (convertedValue == 2)
					{
						combobox_Tessellation_Level().SelectedIndex(1);
					}
					else if (convertedValue == 4)
					{
						combobox_Tessellation_Level().SelectedIndex(2);
					}
					else if (convertedValue == 6)
					{
						combobox_Tessellation_Level().SelectedIndex(3);
					}
					else if (convertedValue == 8)
					{
						combobox_Tessellation_Level().SelectedIndex(4);
					}
					else if (convertedValue == 16)
					{
						combobox_Tessellation_Level().SelectedIndex(5);
					}
					else if (convertedValue == 32)
					{
						combobox_Tessellation_Level().SelectedIndex(6);
					}
					else if (convertedValue == 64)
					{
						combobox_Tessellation_Level().SelectedIndex(7);
					}
				}
			}

			//Get OpenGL Triple Buffering
			{
				toggleswitch_OpenGLTripleBuffering().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "EnableTripleBuffering", true);
				if (adlRegistry.has_value())
				{
					bool convertedValue = (bool)wstring_to_int(adlRegistry.value());
					toggleswitch_OpenGLTripleBuffering().IsOn(convertedValue);
				}
			}

			//Get OpenGL 10-Bit Pixel Format
			{
				toggleswitch_OpenGL10Bit().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "", "KMD_10BitMode", true);
				if (adlRegistry.has_value())
				{
					int convertedValue = wstring_to_int(adlRegistry.value());

					//Enumeration index correction
					if (convertedValue == 1)
					{
						toggleswitch_OpenGL10Bit().IsOn(true);
					}
					else if (convertedValue == 2)
					{
						toggleswitch_OpenGL10Bit().IsOn(false);
					}
				}
			}

			//Set result
			AVDebugWriteLine("ADL graphics registry values loaded.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADL failed loading graphics registry values.");
		}
	}
}