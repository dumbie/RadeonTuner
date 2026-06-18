#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlValuesLoadGraphicsApp()
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

			//Get FSR Upscaling Override
			{
				toggleswitch_FsrOverrideUpscaling().IsEnabled(true);
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(selectedApp.value(), L"FsrOverride");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							toggleswitch_FsrOverrideUpscaling().IsOn(convertedValue);
							break;
						}
					}
				}
				else
				{
					//Set defaults
					toggleswitch_FsrOverrideUpscaling().IsOn(false);
				}
			}

			//Get FSR Interpolation Frame Generation Override
			{
				toggleswitch_FsrOverrideInterpolationFrameGeneration().IsEnabled(true);
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(selectedApp.value(), L"MlfiOverride");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							toggleswitch_FsrOverrideInterpolationFrameGeneration().IsOn(convertedValue);
							break;
						}
					}
				}
				else
				{
					//Set defaults
					toggleswitch_FsrOverrideInterpolationFrameGeneration().IsOn(false);
				}
			}

			//Get FSR Multi Frame Generation Override
			{
				toggleswitch_FsrOverrideMultiFrameGeneration().IsEnabled(true);
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(selectedApp.value(), L"MfgOverride");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							toggleswitch_FsrOverrideMultiFrameGeneration().IsOn(convertedValue);
							break;
						}
					}
				}
				else
				{
					//Set defaults
					toggleswitch_FsrOverrideMultiFrameGeneration().IsOn(false);
				}
			}

			//Get FSR Ray Regeneration Denoiser Override
			{
				toggleswitch_FsrOverrideRayRegeneration().IsEnabled(true);
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(selectedApp.value(), L"MldOverride");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							toggleswitch_FsrOverrideRayRegeneration().IsOn(convertedValue);
							break;
						}
					}
				}
				else
				{
					//Set defaults
					toggleswitch_FsrOverrideRayRegeneration().IsOn(false);
				}
			}

			//Get FSR Neural Radiance Caching Override
			{
				toggleswitch_FsrOverrideNeuralRadianceCaching().IsEnabled(true);
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(selectedApp.value(), L"NrcOverride");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							toggleswitch_FsrOverrideNeuralRadianceCaching().IsOn(convertedValue);
							break;
						}
					}
				}
				else
				{
					//Set defaults
					toggleswitch_FsrOverrideNeuralRadianceCaching().IsOn(false);
				}
			}

			//Get FSR Multi Frame Generation Ratio
			{
				combobox_MultiFrameGenerationRatio().IsEnabled(true);
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(selectedApp.value(), L"MfgRatio");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							int convertedValue = wstring_to_int(value.Value);

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
							break;
						}
					}
				}
				else
				{
					//Set defaults
					combobox_MultiFrameGenerationRatio().SelectedIndex(0);
				}
			}

			//Get FSR Override DLL Path
			{
				//Not supported
				button_FsrDllLoadPath_Default().IsEnabled(false);
				button_FsrDllLoadPath_Set().IsEnabled(false);
				textblock_FsrDllVersion().Text(L"?.?.?.?");
				textblock_FsrDllLoadPath().Text(L"Not supported in application profile.");
			}

			//Get FSR Over-The-Air Updates
			{
				//Not supported
			}

			//Get FSR Latency Reduction
			{
				toggleswitch_FsrLatencyReduction().IsEnabled(true);
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(selectedApp.value(), L"Dlg_PFEnable");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							toggleswitch_FsrLatencyReduction().IsOn(convertedValue);
							break;
						}
					}
				}
				else
				{
					//Set defaults
					toggleswitch_FsrLatencyReduction().IsOn(false);
				}
			}

			//Get Radeon Boost
			{
				toggleswitch_RadeonBoost().IsEnabled(true);
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(selectedApp.value(), L"Bst_PFEnable");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							toggleswitch_RadeonBoost().IsOn(convertedValue);
							slider_RadeonBoost_MinRes().IsEnabled(convertedValue);
							break;
						}
					}
				}
				else
				{
					//Set defaults
					toggleswitch_RadeonBoost().IsOn(false);
					slider_RadeonBoost_MinRes().Value(60);
					slider_RadeonBoost_MinRes().IsEnabled(false);
				}
			}

			//Get Radeon Boost Minimum Resolution
			{
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(selectedApp.value(), L"Bst_MaxScale");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							int convertedValue = wstring_to_int(value.Value);
							slider_RadeonBoost_MinRes().Value(convertedValue);
							break;
						}
					}
				}
				else
				{
					//Set defaults
					slider_RadeonBoost_MinRes().Value(60);
				}
			}

			//Get Radeon Frame Rate Target Control
			{
				//Not supported
				toggleswitch_Frtc().IsEnabled(false);
				slider_Frtc_Fps().IsEnabled(false);
			}

			//Get Radeon Chill
			{
				toggleswitch_RadeonChill().IsEnabled(true);
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(selectedApp.value(), L"Chil_PFEnable");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							toggleswitch_RadeonChill().IsOn(convertedValue);
							slider_RadeonChill_Min().IsEnabled(convertedValue);
							slider_RadeonChill_Max().IsEnabled(convertedValue);
							button_RadeonChill_Link().IsEnabled(convertedValue);
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
							break;
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

			//Get Radeon Chill Minimum Frame Rate
			{
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(selectedApp.value(), L"Chil_MinFRate");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							int convertedValue = wstring_to_int(value.Value);
							slider_RadeonChill_Min().Value(convertedValue);
							break;
						}
					}
				}
				else
				{
					//Set defaults
					slider_RadeonChill_Min().Value(75);
				}
			}

			//Get Radeon Chill Maximum Frame Rate
			{
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(selectedApp.value(), L"Chil_MaxFRate");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							int convertedValue = wstring_to_int(value.Value);
							slider_RadeonChill_Max().Value(convertedValue);
							break;
						}
					}
				}
				else
				{
					//Set defaults
					slider_RadeonChill_Max().Value(140);
				}
			}

			//Get Radeon Image Sharpening 1
			{
				toggleswitch_RadeonImageSharpening1().IsEnabled(true);
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(selectedApp.value(), L"Ris_PFEnable");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							toggleswitch_RadeonImageSharpening1().IsOn(convertedValue);
							slider_RadeonImageSharpening1_Sharpening().IsEnabled(convertedValue);
							break;
						}
					}
				}
				else
				{
					//Set defaults
					toggleswitch_RadeonImageSharpening1().IsOn(false);
					slider_RadeonImageSharpening1_Sharpening().Value(80);
					slider_RadeonImageSharpening1_Sharpening().IsEnabled(false);
				}
			}

			//Get Radeon Image Sharpening 1 Sharpness
			{
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(selectedApp.value(), L"Ris_SHDegree");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							float convertedValue = wstring_to_float(value.Value) * 100;
							slider_RadeonImageSharpening1_Sharpening().Value(convertedValue);
							break;
						}
					}
				}
				else
				{
					//Set defaults
					slider_RadeonImageSharpening1_Sharpening().Value(80);
				}
			}

			//Get Radeon Image Sharpening 2
			{
				//Not supported
				toggleswitch_RadeonImageSharpening2().IsEnabled(false);
				slider_RadeonImageSharpening2_Sharpening().IsEnabled(false);
			}

			//Get Enhanced Sync
			{
				toggleswitch_RadeonEnhancedSync().IsEnabled(true);
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(selectedApp.value(), L"TurboSync");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							toggleswitch_RadeonEnhancedSync().IsOn(convertedValue);
							break;
						}
					}
				}
				else
				{
					//Set defaults
					toggleswitch_RadeonEnhancedSync().IsOn(false);
				}
			}

			//Get Vertical Refresh
			{
				combobox_VerticalRefresh().IsEnabled(true);
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(selectedApp.value(), L"VSyncControl");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							int convertedValue = wstring_to_int(value.Value);
							combobox_VerticalRefresh().SelectedIndex(convertedValue);
							break;
						}
					}
				}
				else
				{
					//Set defaults
					combobox_VerticalRefresh().SelectedIndex(1);
				}
			}

			//Get Anti-Aliasing Override
			{
				toggleswitch_AntiAliasingOverride().IsEnabled(true);
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(selectedApp.value(), L"AntiAlias");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							bool convertedValue = value.Value == L"2";
							toggleswitch_AntiAliasingOverride().IsOn(convertedValue);
							combobox_AntiAliasingMethod().IsEnabled(convertedValue);
							combobox_AntiAliasingLevel().IsEnabled(convertedValue);
							toggleswitch_EQAA().IsEnabled(convertedValue);
							break;
						}
					}
				}
				else
				{
					//Set defaults
					toggleswitch_AntiAliasingOverride().IsOn(false);
					combobox_AntiAliasingMethod().IsEnabled(false);
					combobox_AntiAliasingLevel().IsEnabled(false);
					toggleswitch_EQAA().IsEnabled(false);
				}
			}

			//Get Anti-Aliasing Method
			{
				std::optional<AdlAppProperty> adlPropertyASD = AdlAppPropertyGet(selectedApp.value(), L"ASD");
				std::optional<AdlAppProperty> adlPropertyASE = AdlAppPropertyGet(selectedApp.value(), L"ASE");
				std::optional<AdlAppProperty> adlPropertyASTT = AdlAppPropertyGet(selectedApp.value(), L"ASTT");
				if (adlPropertyASD.has_value() && adlPropertyASE.has_value() && adlPropertyASTT.has_value())
				{
					//Set current
					int asdValue = -1;
					for (AdlAppPropertyValue value : adlPropertyASD.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							asdValue = wstring_to_int(value.Value);
							break;
						}
					}

					int aseValue = 0;
					for (AdlAppPropertyValue value : adlPropertyASE.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							aseValue = wstring_to_int(value.Value);
							break;
						}
					}

					int asttValue = 0;
					for (AdlAppPropertyValue value : adlPropertyASTT.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							asttValue = wstring_to_int(value.Value);
							break;
						}
					}

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

			//Get Anti-Aliasing Level
			{
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(selectedApp.value(), L"AntiAliasSmpls");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							int convertedValue = wstring_to_int(value.Value);

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
							break;
						}
					}
				}
				else
				{
					//Set defaults
					combobox_AntiAliasingLevel().SelectedIndex(0);
				}
			}

			//Get Enhanced Quality Anti-Aliasing
			{
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(selectedApp.value(), L"EQAA");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							toggleswitch_EQAA().IsOn(convertedValue);
							break;
						}
					}
				}
				else
				{
					//Set defaults
					toggleswitch_EQAA().IsOn(false);
				}
			}

			//Get Morphological Anti-Aliasing
			{
				toggleswitch_MorphologicalAntiAliasing().IsEnabled(true);
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(selectedApp.value(), L"MLF");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							toggleswitch_MorphologicalAntiAliasing().IsOn(convertedValue);
							break;
						}
					}
				}
				else
				{
					//Set defaults
					toggleswitch_MorphologicalAntiAliasing().IsOn(false);
				}
			}

			//Get Anisotropic Texture Filtering Override
			{
				combobox_AnisotropicTextureFiltering_Level().IsEnabled(true);
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(selectedApp.value(), L"AnisoDegree");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							int convertedValue = wstring_to_int(value.Value);

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
							break;
						}
					}
				}
				else
				{
					//Set defaults
					combobox_AnisotropicTextureFiltering_Level().SelectedIndex(0);
				}
			}

			//Get Texture Filtering Quality
			{
				combobox_TextureFilteringQuality().IsEnabled(true);
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(selectedApp.value(), L"TFQ");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							int convertedValue = wstring_to_int(value.Value);
							combobox_TextureFilteringQuality().SelectedIndex(convertedValue);
							break;
						}
					}
				}
				else
				{
					//Set defaults
					combobox_TextureFilteringQuality().SelectedIndex(1);
				}
			}

			//Get Surface Format Optimization
			{
				toggleswitch_SurfaceFormatOptimization().IsEnabled(true);
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(selectedApp.value(), L"SrfcFrmtRplcmnt");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							toggleswitch_SurfaceFormatOptimization().IsOn(convertedValue);
							break;
						}
					}
				}
				else
				{
					//Set defaults
					toggleswitch_SurfaceFormatOptimization().IsOn(false);
				}
			}

			//Get Tessellation Mode
			{
				combobox_Tessellation_Mode().IsEnabled(true);
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(selectedApp.value(), L"Tessellation_OP");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							int convertedValue = wstring_to_int(value.Value);
							combobox_Tessellation_Mode().SelectedIndex(convertedValue);
							if (convertedValue != 2)
							{
								combobox_Tessellation_Level().IsEnabled(false);
							}
							else
							{
								combobox_Tessellation_Level().IsEnabled(true);
							}
							break;
						}
					}
				}
				else
				{
					//Set defaults
					combobox_Tessellation_Mode().SelectedIndex(0);
					combobox_Tessellation_Level().IsEnabled(false);
				}
			}

			//Get Tessellation Level
			{
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(selectedApp.value(), L"Tessellation");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							int convertedValue = wstring_to_int(value.Value);

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
							break;
						}
					}
				}
				else
				{
					//Set defaults
					combobox_Tessellation_Level().SelectedIndex(7);
				}
			}

			//Get OpenGL Triple Buffering
			{
				toggleswitch_OpenGLTripleBuffering().IsEnabled(true);
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(selectedApp.value(), L"EnableTrplBffr");
				if (adlProperty.has_value())
				{
					//Set current
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							toggleswitch_OpenGLTripleBuffering().IsOn(convertedValue);
							break;
						}
					}
				}
				else
				{
					//Set defaults
					toggleswitch_OpenGLTripleBuffering().IsOn(false);
				}
			}

			//Get OpenGL 10-Bit Pixel Format
			{
				//Not supported
				toggleswitch_OpenGL10Bit().IsEnabled(false);
			}

			//Set result
			AVDebugWriteLine("ADL graphics app values loaded.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADL failed loading graphics app values.");
		}
	}
}