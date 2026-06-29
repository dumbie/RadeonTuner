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
			//Fix find way to check if setting is supported and disable interface. (ADL2_Adapter_Feature_Caps)

			//Set interface limits
			slider_RadeonBoost_MinRes().Minimum(50);
			slider_RadeonBoost_MinRes().Maximum(84);
			slider_RadeonBoost_MinRes().StepFrequency(17);
			slider_RadeonBoost_MinRes().SmallChange(17);

			slider_RadeonChill_Min().Minimum(30);
			slider_RadeonChill_Min().Maximum(300);
			slider_RadeonChill_Min().StepFrequency(1);
			slider_RadeonChill_Min().SmallChange(1);

			slider_RadeonChill_Max().Minimum(30);
			slider_RadeonChill_Max().Maximum(300);
			slider_RadeonChill_Max().StepFrequency(1);
			slider_RadeonChill_Max().SmallChange(1);

			slider_RadeonImageSharpening1_Sharpening().Minimum(10);
			slider_RadeonImageSharpening1_Sharpening().Maximum(100);
			slider_RadeonImageSharpening1_Sharpening().StepFrequency(10);
			slider_RadeonImageSharpening1_Sharpening().SmallChange(10);

			slider_RadeonImageSharpening2_Sharpening().Minimum(10);
			slider_RadeonImageSharpening2_Sharpening().Maximum(100);
			slider_RadeonImageSharpening2_Sharpening().StepFrequency(10);
			slider_RadeonImageSharpening2_Sharpening().SmallChange(10);

			slider_Frtc_Fps().Minimum(15);
			slider_Frtc_Fps().Maximum(1000);
			slider_Frtc_Fps().StepFrequency(1);
			slider_Frtc_Fps().SmallChange(1);

			//FSR Upscaling Override
			{
				toggleswitch_FsrOverrideUpscaling().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "FsrOverride", true);
				if (adlRegistry.has_value())
				{
					//Set current
					bool convertedValue = (bool)wstring_to_int(adlRegistry.value());
					toggleswitch_FsrOverrideUpscaling().IsOn(convertedValue);
				}
				else
				{
					//Set defaults
					toggleswitch_FsrOverrideUpscaling().IsOn(true);
				}
			}

			//FSR Frame Generation Override
			{
				toggleswitch_FsrOverrideFrameGeneration().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "MlfiOverride", true);
				if (adlRegistry.has_value())
				{
					//Set current
					bool convertedValue = (bool)wstring_to_int(adlRegistry.value());
					toggleswitch_FsrOverrideFrameGeneration().IsOn(convertedValue);
				}
				else
				{
					//Set defaults
					toggleswitch_FsrOverrideFrameGeneration().IsOn(true);
				}
			}

			//FSR Multi Frame Generation Override
			{
				toggleswitch_FsrOverrideMultiFrameGeneration().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "MfgOverride", true);
				if (adlRegistry.has_value())
				{
					//Set current
					bool convertedValue = (bool)wstring_to_int(adlRegistry.value());
					toggleswitch_FsrOverrideMultiFrameGeneration().IsOn(convertedValue);
				}
				else
				{
					//Set defaults
					toggleswitch_FsrOverrideMultiFrameGeneration().IsOn(false);
				}
			}

			//FSR Ray Regeneration Denoiser Override
			{
				toggleswitch_FsrOverrideRayRegeneration().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "MldOverride", true);
				if (adlRegistry.has_value())
				{
					//Set current
					bool convertedValue = (bool)wstring_to_int(adlRegistry.value());
					toggleswitch_FsrOverrideRayRegeneration().IsOn(convertedValue);
				}
				else
				{
					//Set defaults
					toggleswitch_FsrOverrideRayRegeneration().IsOn(false);
				}
			}

			//FSR Neural Radiance Caching Override
			{
				toggleswitch_FsrOverrideNeuralRadianceCaching().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "NrcOverride", true);
				if (adlRegistry.has_value())
				{
					//Set current
					bool convertedValue = (bool)wstring_to_int(adlRegistry.value());
					toggleswitch_FsrOverrideNeuralRadianceCaching().IsOn(convertedValue);
				}
				else
				{
					//Set defaults
					toggleswitch_FsrOverrideNeuralRadianceCaching().IsOn(false);
				}
			}

			//FSR Multi Frame Generation Ratio
			{
				combobox_MultiFrameGenerationRatio().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "MfgRatio", true);
				if (adlRegistry.has_value())
				{
					//Set current
					int convertedValue = wstring_to_int(adlRegistry.value());
					combobox_MultiFrameGenerationRatio().SelectedIndex(convertedValue);
				}
				else
				{
					//Set defaults
					combobox_MultiFrameGenerationRatio().SelectedIndex(0);
				}
			}

			//FSR Override Library
			{
				button_FsrDllLoadPath_Default().IsEnabled(true);
				button_FsrDllLoadPath_Set().IsEnabled(true);

				//Update FSR library version text
				std::wstring dllPath = FsrOverrideDllGetPathSet(true);
				FsrOverrideDllUpdateTextVersion(dllPath);
				FsrOverrideDllUpdateTextPath(dllPath);
			}

			//FSR Over-The-Air Updates
			{
				combobox_FsrOtaUpdates().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "FsrOtaIndex", true);
				if (adlRegistry.has_value())
				{
					//Set current
					int convertedValue = wstring_to_int(adlRegistry.value());
					combobox_FsrOtaUpdates().SelectedIndex(convertedValue);
				}
				else
				{
					//Set defaults
					combobox_FsrOtaUpdates().SelectedIndex(1);
				}
			}

			//FSR Latency Reduction
			try
			{
				toggleswitch_FsrLatencyReduction().IsEnabled(true);
				ADL_DELAG_SETTINGS adlSettings;
				adl_Res0 = _ADL2_DELAG_SettingsX2_Get(adl_Context, adl_Gpu_AdapterIndex, &adlSettings);
				if (adl_Res0 == ADL_OK)
				{
					//Set current
					toggleswitch_FsrLatencyReduction().IsOn(adlSettings.GlobalEnable);
				}
				else
				{
					//Set defaults
					toggleswitch_FsrLatencyReduction().IsOn(false);
				}
			}
			catch (...) {}

			//Radeon Boost
			try
			{
				toggleswitch_RadeonBoost().IsEnabled(true);
				ADL_BOOST_SETTINGS adlSettings;
				adl_Res0 = _ADL2_BOOST_Settings_GetX2(adl_Context, adl_Gpu_AdapterIndex, &adlSettings);
				if (adl_Res0 == ADL_OK)
				{
					//Set current
					toggleswitch_RadeonBoost().IsOn(adlSettings.GlobalEnable);
					slider_RadeonBoost_MinRes().Value(adlSettings.GlobalMinRes);
					slider_RadeonBoost_MinRes().IsEnabled(adlSettings.GlobalEnable);
				}
				else
				{
					//Set defaults
					toggleswitch_RadeonBoost().IsOn(false);
					slider_RadeonBoost_MinRes().Value(60);
					slider_RadeonBoost_MinRes().IsEnabled(false);
				}
			}
			catch (...) {}

			//Radeon Chill
			try
			{
				toggleswitch_RadeonChill().IsEnabled(true);
				ADL_CHILL_SETTINGS adlSettings;
				adl_Res0 = _ADL2_CHILL_SettingsX2_Get(adl_Context, adl_Gpu_AdapterIndex, &adlSettings);
				if (adl_Res0 == ADL_OK)
				{
					//Set current
					toggleswitch_RadeonChill().IsOn(adlSettings.GlobalEnable);
					slider_RadeonChill_Min().Value(adlSettings.GlobalMinFPS);
					slider_RadeonChill_Max().Value(adlSettings.GlobalMaxFPS);
					slider_RadeonChill_Min().IsEnabled(adlSettings.GlobalEnable);
					slider_RadeonChill_Max().IsEnabled(adlSettings.GlobalEnable);
					button_RadeonChill_Link().IsEnabled(adlSettings.GlobalEnable);
					if (adlSettings.GlobalEnable)
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
				}
				else
				{
					//Set defaults
					toggleswitch_RadeonChill().IsOn(false);
					slider_RadeonChill_Min().Value(75);
					slider_RadeonChill_Max().Value(140);
					slider_RadeonChill_Min().IsEnabled(false);
					slider_RadeonChill_Max().IsEnabled(false);
					button_RadeonChill_Link().IsEnabled(false);
				}
			}
			catch (...) {}

			//Radeon Image Sharpening 1
			try
			{
				toggleswitch_RadeonImageSharpening1().IsEnabled(true);
				ADL_RIS_SETTINGS adlSettings;
				adl_Res0 = _ADL2_RIS_Settings_Get(adl_Context, adl_Gpu_AdapterIndex, &adlSettings);
				if (adl_Res0 == ADL_OK)
				{
					//Set current
					toggleswitch_RadeonImageSharpening1().IsOn(adlSettings.GlobalEnable);
					slider_RadeonImageSharpening1_Sharpening().Value(adlSettings.GlobalSharpeningDegree);
					slider_RadeonImageSharpening1_Sharpening().IsEnabled(adlSettings.GlobalEnable);
				}
				else
				{
					//Set defaults
					toggleswitch_RadeonImageSharpening1().IsOn(false);
					slider_RadeonImageSharpening1_Sharpening().Value(80);
					slider_RadeonImageSharpening1_Sharpening().IsEnabled(false);
				}
			}
			catch (...) {}

			//Radeon Image Sharpening 2
			try
			{
				toggleswitch_RadeonImageSharpening2().IsEnabled(true);
				ADL_RIS2_SETTINGS adlSettings;
				adl_Res0 = _ADL2_RIS_SettingsX2_Get(adl_Context, adl_Gpu_AdapterIndex, &adlSettings);
				if (adl_Res0 == ADL_OK)
				{
					//Set current
					toggleswitch_RadeonImageSharpening2().IsOn(adlSettings.GlobalEnable);
					toggleswitch_RadeonImageSharpening2_Desktop().IsOn(adlSettings.GlobalDesktop);
					toggleswitch_RadeonImageSharpening2_Desktop().IsEnabled(adlSettings.GlobalEnable);
					slider_RadeonImageSharpening2_Sharpening().Value(adlSettings.GlobalSharpeningDegree);
					slider_RadeonImageSharpening2_Sharpening().IsEnabled(adlSettings.GlobalEnable);
				}
				else
				{
					//Set defaults
					toggleswitch_RadeonImageSharpening2().IsOn(false);
					toggleswitch_RadeonImageSharpening2_Desktop().IsOn(false);
					toggleswitch_RadeonImageSharpening2_Desktop().IsEnabled(false);
					slider_RadeonImageSharpening2_Sharpening().Value(50);
					slider_RadeonImageSharpening2_Sharpening().IsEnabled(false);
				}
			}
			catch (...)
			{
				toggleswitch_RadeonImageSharpening2().IsEnabled(false);
				toggleswitch_RadeonImageSharpening2_Desktop().IsEnabled(false);
				slider_RadeonImageSharpening2_Sharpening().IsEnabled(false);
			}

			//Enhanced Sync
			{
				toggleswitch_RadeonEnhancedSync().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "TurboSync", true);
				if (adlRegistry.has_value())
				{
					//Set current
					bool convertedValue = (bool)wstring_to_int(adlRegistry.value());
					toggleswitch_RadeonEnhancedSync().IsOn(convertedValue);
				}
				else
				{
					//Set defaults
					toggleswitch_RadeonEnhancedSync().IsOn(false);
				}
			}

			//Vertical Refresh
			{
				combobox_VerticalRefresh().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "VSyncControl", true);
				if (adlRegistry.has_value())
				{
					//Set current
					int convertedValue = wstring_to_int(adlRegistry.value());
					combobox_VerticalRefresh().SelectedIndex(convertedValue);
				}
				else
				{
					//Set defaults
					combobox_VerticalRefresh().SelectedIndex(1);
				}
			}

			//Radeon Frame Rate Target Control
			try
			{
				toggleswitch_Frtc().IsEnabled(true);
				ADLFPSSettingsOutput adlSettings;
				adl_Res0 = _ADL2_FPS_Settings_Get(adl_Context, adl_Gpu_AdapterIndex, &adlSettings);
				if (adl_Res0 == ADL_OK)
				{
					//Set current
					toggleswitch_Frtc().IsOn(adlSettings.bACFPSEnabled);
					slider_Frtc_Fps().Value(adlSettings.ulACFPSCurrent);
					slider_Frtc_Fps().IsEnabled(adlSettings.bACFPSEnabled);
				}
				else
				{
					//Set defaults
					toggleswitch_Frtc().IsOn(false);
					slider_Frtc_Fps().Value(60);
					slider_Frtc_Fps().IsEnabled(false);
				}
			}
			catch (...) {}

			//Anti-Aliasing Override
			{
				toggleswitch_AntiAliasingOverride().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "AntiAlias", true);
				if (adlRegistry.has_value())
				{
					//Set current
					bool convertedValue = adlRegistry.value() == L"2";
					toggleswitch_AntiAliasingOverride().IsOn(convertedValue);
					combobox_AntiAliasingMethod().IsEnabled(convertedValue);
					combobox_AntiAliasingLevel().IsEnabled(convertedValue);
					toggleswitch_EnhancedQualityAntiAliasing().IsEnabled(convertedValue);
				}
				else
				{
					//Set defaults
					toggleswitch_AntiAliasingOverride().IsOn(false);
					combobox_AntiAliasingMethod().IsEnabled(false);
					combobox_AntiAliasingLevel().IsEnabled(false);
					toggleswitch_EnhancedQualityAntiAliasing().IsEnabled(false);
				}
			}

			//Anti-Aliasing Method
			{
				auto adlRegistryASD = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "ASD", true);
				auto adlRegistryASE = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "ASE", true);
				auto adlRegistryASTT = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "ASTT", true);
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
				else
				{
					//Set defaults
					combobox_AntiAliasingMethod().SelectedIndex(0);
				}
			}

			//Anti-Aliasing Level
			{
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "AntiAliasSamples", true);
				if (adlRegistry.has_value())
				{
					//Set current
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
				else
				{
					//Set defaults
					combobox_AntiAliasingLevel().SelectedIndex(0);
				}
			}

			//Enhanced Quality Anti-Aliasing
			{
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "EQAA", true);
				if (adlRegistry.has_value())
				{
					//Set current
					bool convertedValue = (bool)wstring_to_int(adlRegistry.value());
					toggleswitch_EnhancedQualityAntiAliasing().IsOn(convertedValue);
				}
				else
				{
					//Set defaults
					toggleswitch_EnhancedQualityAntiAliasing().IsOn(false);
				}
			}

			//Morphological Anti-Aliasing
			{
				toggleswitch_MorphologicalAntiAliasing().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "MLF", true);
				if (adlRegistry.has_value())
				{
					//Set current
					bool convertedValue = (bool)wstring_to_int(adlRegistry.value());
					toggleswitch_MorphologicalAntiAliasing().IsOn(convertedValue);
				}
				else
				{
					//Set defaults
					toggleswitch_MorphologicalAntiAliasing().IsOn(false);
				}
			}

			//Anisotropic Texture Filtering Override
			{
				combobox_AnisotropicTextureFiltering_Level().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "AnisoDegree", true);
				if (adlRegistry.has_value())
				{
					//Set current
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
				else
				{
					//Set defaults
					combobox_AnisotropicTextureFiltering_Level().SelectedIndex(0);
				}
			}

			//Texture Filtering Quality
			{
				combobox_TextureFilteringQuality().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "TFQ", true);
				if (adlRegistry.has_value())
				{
					//Set current
					int convertedValue = wstring_to_int(adlRegistry.value());
					combobox_TextureFilteringQuality().SelectedIndex(convertedValue);
				}
				else
				{
					//Set defaults
					combobox_TextureFilteringQuality().SelectedIndex(1);
				}
			}

			//Surface Format Optimization
			{
				toggleswitch_SurfaceFormatOptimization().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "SurfaceFormatReplacements", true);
				if (adlRegistry.has_value())
				{
					//Set current
					bool convertedValue = (bool)wstring_to_int(adlRegistry.value());
					toggleswitch_SurfaceFormatOptimization().IsOn(convertedValue);
				}
				else
				{
					//Set defaults
					toggleswitch_SurfaceFormatOptimization().IsOn(false);
				}
			}

			//Tessellation Mode
			{
				combobox_Tessellation_Mode().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "Tessellation_OPTION", true);
				if (adlRegistry.has_value())
				{
					//Set current
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
				else
				{
					//Set defaults
					combobox_Tessellation_Mode().SelectedIndex(0);
					combobox_Tessellation_Level().IsEnabled(false);
				}
			}

			//Tessellation Level
			{
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "Tessellation", true);
				if (adlRegistry.has_value())
				{
					//Set current
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
				else
				{
					//Set defaults
					combobox_Tessellation_Level().SelectedIndex(7);
				}
			}

			//OpenGL Triple Buffering
			{
				toggleswitch_OpenGLTripleBuffering().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "UMD", "EnableTripleBuffering", true);
				if (adlRegistry.has_value())
				{
					//Set current
					bool convertedValue = (bool)wstring_to_int(adlRegistry.value());
					toggleswitch_OpenGLTripleBuffering().IsOn(convertedValue);
				}
				else
				{
					//Set defaults
					toggleswitch_OpenGLTripleBuffering().IsOn(false);
				}
			}

			//OpenGL 10-Bit Pixel Format
			{
				toggleswitch_OpenGL10BitPixelFormat().IsEnabled(true);
				auto adlRegistry = AdlRegistrySettingGetString(adl_Gpu_AdapterIndex, "", "KMD_10BitMode", true);
				if (adlRegistry.has_value())
				{
					//Set current
					int convertedValue = wstring_to_int(adlRegistry.value());

					//Enumeration index correction
					if (convertedValue == 1)
					{
						toggleswitch_OpenGL10BitPixelFormat().IsOn(true);
					}
					else if (convertedValue == 2)
					{
						toggleswitch_OpenGL10BitPixelFormat().IsOn(false);
					}
				}
				else
				{
					//Set defaults
					toggleswitch_OpenGL10BitPixelFormat().IsOn(false);
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