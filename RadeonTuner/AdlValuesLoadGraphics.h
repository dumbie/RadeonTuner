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
			//Check application
			if (!adl_AppSelected().Initialized())
			{
				AVDebugWriteLine("ADL application is not selected.");
				return;
			}

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

			slider_RadeonImageSharpening_Sharpening().Minimum(10);
			slider_RadeonImageSharpening_Sharpening().Maximum(100);
			slider_RadeonImageSharpening_Sharpening().StepFrequency(10);
			slider_RadeonImageSharpening_Sharpening().SmallChange(10);

			//Get FSR Override Upscaling
			{
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"FsrOverride");
				if (adlProperty.has_value())
				{
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
			}

			//Get FSR Override Frame Generation
			{
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"MlfiOverride");
				if (adlProperty.has_value())
				{
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							toggleswitch_FsrOverrideFrameGen().IsOn(convertedValue);
							break;
						}
					}
				}
			}

			//Get Radeon Anti-Lag
			{
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"Dlg_PFEnable");
				if (adlProperty.has_value())
				{
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							toggleswitch_RadeonAntiLag().IsOn(convertedValue);
							break;
						}
					}
				}
			}

			//Get Radeon Boost
			{
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"Bst_PFEnable");
				if (adlProperty.has_value())
				{
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
			}

			//Get Radeon Boost Minimum Resolution
			{
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"Bst_MaxScale");
				if (adlProperty.has_value())
				{
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
			}

			//Get Radeon Chill
			{
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"Chil_PFEnable");
				if (adlProperty.has_value())
				{
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							toggleswitch_RadeonChill().IsOn(convertedValue);
							slider_RadeonChill_Min().IsEnabled(convertedValue);
							slider_RadeonChill_Max().IsEnabled(convertedValue);
							break;
						}
					}
				}
			}

			//Get Radeon Chill Minimum
			{
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"Chil_MinFRate");
				if (adlProperty.has_value())
				{
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
			}

			//Get Radeon Chill Maximum
			{
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"Chil_MaxFRate");
				if (adlProperty.has_value())
				{
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
			}

			//Get Radeon Image Sharpening
			{
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"Ris_PFEnable");
				if (adlProperty.has_value())
				{
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							toggleswitch_RadeonImageSharpening().IsOn(convertedValue);
							slider_RadeonImageSharpening_Sharpening().IsEnabled(convertedValue);
							break;
						}
					}
				}
			}

			//Get Radeon Image Sharpening Sharpness
			{
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"Ris_SHDegree");
				if (adlProperty.has_value())
				{
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							float convertedValue = wstring_to_float(value.Value) * 100;
							slider_RadeonImageSharpening_Sharpening().Value(convertedValue);
							break;
						}
					}
				}
			}

			//Get Enhanced Sync
			{
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"TurboSync");
				if (adlProperty.has_value())
				{
					for (AdlAppPropertyValue value : adlProperty.value().Values)
					{
						if (value.GpuId == gpuUniqueIdentifierHex)
						{
							bool convertedValue = (bool)wstring_to_int(value.Value);
							toggleswitch_RadeonEnhancedSync().IsOn(convertedValue);
							//combobox_VerticalRefresh().IsEnabled(!convertedValue);
							break;
						}
					}
				}
			}

			//Get Vertical Refresh
			{
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"VSyncControl");
				if (adlProperty.has_value())
				{
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
			}

			//Get Anti-Aliasing Override
			{
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"AntiAlias");
				if (adlProperty.has_value())
				{
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
			}

			//Get Anti-Aliasing Method
			{
				std::optional<AdlAppProperty> adlPropertyASD = AdlAppPropertyGet(adl_AppSelected(), L"ASD");
				std::optional<AdlAppProperty> adlPropertyASE = AdlAppPropertyGet(adl_AppSelected(), L"ASE");
				std::optional<AdlAppProperty> adlPropertyASTT = AdlAppPropertyGet(adl_AppSelected(), L"ASTT");
				if (adlPropertyASD.has_value() && adlPropertyASE.has_value() && adlPropertyASTT.has_value())
				{
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
			}

			//Get Anti-Aliasing Level
			{
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"AntiAliasSmpls");
				if (adlProperty.has_value())
				{
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
			}

			//Get Enhanced Quality Anti-Aliasing
			{
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"EQAA");
				if (adlProperty.has_value())
				{
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
			}

			//Get Morphological Anti-Aliasing
			{
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"MLF");
				if (adlProperty.has_value())
				{
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
			}

			//Get Anisotropic Texture Filtering Override
			{
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"AnisoDegree");
				if (adlProperty.has_value())
				{
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
			}

			//Get Texture Filtering Quality
			{
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"TFQ");
				if (adlProperty.has_value())
				{
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
			}

			//Get Surface Format Optimization
			{
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"SrfcFrmtRplcmnt");
				if (adlProperty.has_value())
				{
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
			}

			//Get Tessellation Mode
			{
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"Tessellation_OP");
				if (adlProperty.has_value())
				{
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
			}

			//Get Tessellation Level
			{
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"Tessellation");
				if (adlProperty.has_value())
				{
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
			}

			//Get OpenGL Triple Buffering
			{
				std::optional<AdlAppProperty> adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"EnableTrplBffr");
				if (adlProperty.has_value())
				{
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
			}

			//Set result
			AVDebugWriteLine("ADL graphics values loaded.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADL failed loading graphics values.");
		}
	}
}