#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlVariables.h"

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

			//Get Radeon Super Resolution setting
			//Fix Not stored in 3D_User or registry but gmdb.blb
			//"upscaling_enabled": "TRUE", "upscaling_sharpness": 50 and "has_upscaling_profile": "TRUE"
			toggleswitch_RadeonSuperResolution().IsEnabled(false);
			slider_RadeonSuperResolution_Sharpening().IsEnabled(false);

			//Get Radeon Fluid Motion Frames setting
			//Fix Not stored in 3D_User or registry but gmdb.blb
			//"framegen_enabled": 1 and "has_framegen_profile": "TRUE"
			toggleswitch_RadeonFluidMotionFrames().IsEnabled(false);
			combobox_FrameGenSearchMode().IsEnabled(false);
			combobox_FrameGenPerfMode().IsEnabled(false);
			combobox_FrameGenResponseMode().IsEnabled(false);

			//Get FSR Override Upscaling setting
			try
			{
				AdlAppProperty adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"FsrOverride");
				for (AdlAppPropertyValue value : adlProperty.Values)
				{
					if (value.GpuId == gpuUniqueIdentifierHex)
					{
						bool convertedValue = (bool)wstring_to_int(value.Value);
						toggleswitch_FsrOverrideUpscaling().IsOn(convertedValue);
						break;
					}
				}
			}
			catch (...) {}

			//Get FSR Override Frame Generation setting
			try
			{
				AdlAppProperty adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"MlfiOverride");
				for (AdlAppPropertyValue value : adlProperty.Values)
				{
					if (value.GpuId == gpuUniqueIdentifierHex)
					{
						bool convertedValue = (bool)wstring_to_int(value.Value);
						toggleswitch_FsrOverrideFrameGen().IsOn(convertedValue);
						break;
					}
				}
			}
			catch (...) {}

			//Get Radeon Anti-Lag setting
			try
			{
				AdlAppProperty adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"Dlg_PFEnable");
				for (AdlAppPropertyValue value : adlProperty.Values)
				{
					if (value.GpuId == gpuUniqueIdentifierHex)
					{
						bool convertedValue = (bool)wstring_to_int(value.Value);
						toggleswitch_RadeonAntiLag().IsOn(convertedValue);
						break;
					}
				}
			}
			catch (...) {}

			//Get Radeon Boost setting
			try
			{
				AdlAppProperty adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"Bst_PFEnable");
				for (AdlAppPropertyValue value : adlProperty.Values)
				{
					if (value.GpuId == gpuUniqueIdentifierHex)
					{
						bool convertedValue = (bool)wstring_to_int(value.Value);
						toggleswitch_RadeonBoost().IsOn(convertedValue);
						slider_RadeonBoost_MinRes().IsEnabled(convertedValue);
						break;
					}
				}

				adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"Bst_MaxScale");
				for (AdlAppPropertyValue value : adlProperty.Values)
				{
					if (value.GpuId == gpuUniqueIdentifierHex)
					{
						int convertedValue = wstring_to_int(value.Value);
						slider_RadeonBoost_MinRes().Value(convertedValue);
						break;
					}
				}
			}
			catch (...) {}

			//Get Radeon Chill setting
			try
			{
				AdlAppProperty adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"Chil_PFEnable");
				for (AdlAppPropertyValue value : adlProperty.Values)
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

				adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"Chil_MinFRate");
				for (AdlAppPropertyValue value : adlProperty.Values)
				{
					if (value.GpuId == gpuUniqueIdentifierHex)
					{
						int convertedValue = wstring_to_int(value.Value);
						slider_RadeonChill_Min().Value(convertedValue);
						break;
					}
				}

				adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"Chil_MaxFRate");
				for (AdlAppPropertyValue value : adlProperty.Values)
				{
					if (value.GpuId == gpuUniqueIdentifierHex)
					{
						int convertedValue = wstring_to_int(value.Value);
						slider_RadeonChill_Max().Value(convertedValue);
						break;
					}
				}
			}
			catch (...) {}

			//Get Radeon Image Sharpening setting
			try
			{
				AdlAppProperty adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"Ris_PFEnable");
				for (AdlAppPropertyValue value : adlProperty.Values)
				{
					if (value.GpuId == gpuUniqueIdentifierHex)
					{
						bool convertedValue = (bool)wstring_to_int(value.Value);
						toggleswitch_RadeonImageSharpening().IsOn(convertedValue);
						slider_RadeonImageSharpening_Sharpening().IsEnabled(convertedValue);
						break;
					}
				}

				adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"Ris_SHDegree");
				for (AdlAppPropertyValue value : adlProperty.Values)
				{
					if (value.GpuId == gpuUniqueIdentifierHex)
					{
						float convertedValue = wstring_to_float(value.Value) * 100;
						slider_RadeonImageSharpening_Sharpening().Value(convertedValue);
						break;
					}
				}
			}
			catch (...) {}

			//Get Radeon Sharpen Desktop setting
			//Global only setting
			toggleswitch_RadeonSharpenDesktop().IsEnabled(false);

			//Get vertical refresh setting
			try
			{
				AdlAppProperty adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"VSyncControl");
				for (AdlAppPropertyValue value : adlProperty.Values)
				{
					if (value.GpuId == gpuUniqueIdentifierHex)
					{
						int convertedValue = wstring_to_int(value.Value);
						combobox_VerticalRefresh().SelectedIndex(convertedValue);
						break;
					}
				}
			}
			catch (...) {}

			//Get enhanced sync setting
			try
			{
				AdlAppProperty adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"TurboSync");
				for (AdlAppPropertyValue value : adlProperty.Values)
				{
					if (value.GpuId == gpuUniqueIdentifierHex)
					{
						bool convertedValue = (bool)wstring_to_int(value.Value);
						toggleswitch_RadeonEnhancedSync().IsOn(convertedValue);
						break;
					}
				}
			}
			catch (...) {}

			//Get Frame Rate Target Control (FRTC) setting
			//Global only setting
			toggleswitch_Frtc().IsEnabled(false);
			slider_Frtc_Fps().IsEnabled(false);

			//Get Anti-Aliasing Mode setting
			try
			{
				int antiAliasValue = -1;
				AdlAppProperty adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"AntiAlias");
				for (AdlAppPropertyValue value : adlProperty.Values)
				{
					if (value.GpuId == gpuUniqueIdentifierHex)
					{
						antiAliasValue = wstring_to_int(value.Value);
						break;
					}
				}

				bool eqaaValue = false;
				adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"EQAA");
				for (AdlAppPropertyValue value : adlProperty.Values)
				{
					if (value.GpuId == gpuUniqueIdentifierHex)
					{
						eqaaValue = (bool)wstring_to_int(value.Value);
						break;
					}
				}

				if (antiAliasValue == 1 && !eqaaValue)
				{
					combobox_AntiAliasingMode().SelectedIndex(0);
					combobox_AntiAliasingLevel().IsEnabled(false);
				}
				else if (antiAliasValue == 1 && eqaaValue)
				{
					combobox_AntiAliasingMode().SelectedIndex(1);
					combobox_AntiAliasingLevel().IsEnabled(false);
				}
				else if (antiAliasValue == 2)
				{
					combobox_AntiAliasingMode().SelectedIndex(2);
					combobox_AntiAliasingLevel().IsEnabled(true);
				}
			}
			catch (...) {}

			//Get Anti-Aliasing Method setting
			try
			{
				int asdValue = -1;
				AdlAppProperty adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"ASD");
				for (AdlAppPropertyValue value : adlProperty.Values)
				{
					if (value.GpuId == gpuUniqueIdentifierHex)
					{
						asdValue = wstring_to_int(value.Value);
						break;
					}
				}

				int aseValue = -1;
				adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"ASE");
				for (AdlAppPropertyValue value : adlProperty.Values)
				{
					if (value.GpuId == gpuUniqueIdentifierHex)
					{
						aseValue = wstring_to_int(value.Value);
						break;
					}
				}

				int asttValue = -1;
				adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"ASTT");
				for (AdlAppPropertyValue value : adlProperty.Values)
				{
					if (value.GpuId == gpuUniqueIdentifierHex)
					{
						asttValue = wstring_to_int(value.Value);
						break;
					}
				}

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
			catch (...) {}

			//Get Anti-Aliasing Level setting
			try
			{
				int antiAliasSmplsValue = 0;
				AdlAppProperty adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"AntiAliasSmpls");
				for (AdlAppPropertyValue value : adlProperty.Values)
				{
					if (value.GpuId == gpuUniqueIdentifierHex)
					{
						antiAliasSmplsValue = wstring_to_int(value.Value);
						break;
					}
				}

				bool eqaaValue = false;
				adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"EQAA");
				for (AdlAppPropertyValue value : adlProperty.Values)
				{
					if (value.GpuId == gpuUniqueIdentifierHex)
					{
						eqaaValue = (bool)wstring_to_int(value.Value);
						break;
					}
				}

				//Enumeration index correction
				if (antiAliasSmplsValue == 2 && !eqaaValue)
				{
					combobox_AntiAliasingLevel().SelectedIndex(0);
				}
				else if (antiAliasSmplsValue == 2 && eqaaValue)
				{
					combobox_AntiAliasingLevel().SelectedIndex(1);
				}
				else if (antiAliasSmplsValue == 4 && !eqaaValue)
				{
					combobox_AntiAliasingLevel().SelectedIndex(2);
				}
				else if (antiAliasSmplsValue == 4 && eqaaValue)
				{
					combobox_AntiAliasingLevel().SelectedIndex(3);
				}
				else if (antiAliasSmplsValue == 8 && !eqaaValue)
				{
					combobox_AntiAliasingLevel().SelectedIndex(4);
				}
				else if (antiAliasSmplsValue == 8 && eqaaValue)
				{
					combobox_AntiAliasingLevel().SelectedIndex(5);
				}
				else
				{
					AVDebugWriteLine("No Anti-Aliasing level set.");
				}
			}
			catch (...) {}

			//Get Morphologic Anti-Aliasing setting
			try
			{
				AdlAppProperty adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"MLF");
				for (AdlAppPropertyValue value : adlProperty.Values)
				{
					if (value.GpuId == gpuUniqueIdentifierHex)
					{
						bool convertedValue = (bool)wstring_to_int(value.Value);
						toggleswitch_MorphologicAntiAliasing().IsOn(convertedValue);
						break;
					}
				}
			}
			catch (...) {}

			//Get Anisotropic Texture Filtering setting
			try
			{
				AdlAppProperty adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"AnisoDegree");
				for (AdlAppPropertyValue value : adlProperty.Values)
				{
					if (value.GpuId == gpuUniqueIdentifierHex)
					{
						int convertedValue = wstring_to_int(value.Value);

						//Enumeration index correction
						if (convertedValue == 0)
						{
							toggleswitch_AnisotropicTextureFiltering().IsOn(false);
							combobox_AnisotropicTextureFiltering_Level().IsEnabled(false);
							combobox_AnisotropicTextureFiltering_Level().SelectedIndex(-1);
						}
						else if (convertedValue == 2)
						{
							toggleswitch_AnisotropicTextureFiltering().IsOn(true);
							combobox_AnisotropicTextureFiltering_Level().IsEnabled(true);
							combobox_AnisotropicTextureFiltering_Level().SelectedIndex(0);
						}
						else if (convertedValue == 4)
						{
							toggleswitch_AnisotropicTextureFiltering().IsOn(true);
							combobox_AnisotropicTextureFiltering_Level().IsEnabled(true);
							combobox_AnisotropicTextureFiltering_Level().SelectedIndex(1);
						}
						else if (convertedValue == 8)
						{
							toggleswitch_AnisotropicTextureFiltering().IsOn(true);
							combobox_AnisotropicTextureFiltering_Level().IsEnabled(true);
							combobox_AnisotropicTextureFiltering_Level().SelectedIndex(2);
						}
						else if (convertedValue == 16)
						{
							toggleswitch_AnisotropicTextureFiltering().IsOn(true);
							combobox_AnisotropicTextureFiltering_Level().IsEnabled(true);
							combobox_AnisotropicTextureFiltering_Level().SelectedIndex(3);
						}
						break;
					}
				}
			}
			catch (...) {}

			//Get Texture Filtering Quality setting
			try
			{
				AdlAppProperty adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"TFQ");
				for (AdlAppPropertyValue value : adlProperty.Values)
				{
					if (value.GpuId == gpuUniqueIdentifierHex)
					{
						int convertedValue = wstring_to_int(value.Value);
						combobox_TextureFilteringQuality().SelectedIndex(convertedValue);
						break;
					}
				}
			}
			catch (...) {}

			//Get Surface Format Optimization setting
			try
			{
				AdlAppProperty adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"SrfcFrmtRplcmnt");
				for (AdlAppPropertyValue value : adlProperty.Values)
				{
					if (value.GpuId == gpuUniqueIdentifierHex)
					{
						bool convertedValue = (bool)wstring_to_int(value.Value);
						toggleswitch_SurfaceFormatOptimization().IsOn(convertedValue);
						break;
					}
				}
			}
			catch (...) {}

			//Get Tesselation Mode setting
			try
			{
				AdlAppProperty adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"Tessellation_OP");
				for (AdlAppPropertyValue value : adlProperty.Values)
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
			catch (...) {}

			//Get Tesselation Level setting
			try
			{
				AdlAppProperty adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"Tessellation");
				for (AdlAppPropertyValue value : adlProperty.Values)
				{
					if (value.GpuId == gpuUniqueIdentifierHex)
					{
						int convertedValue = wstring_to_int(value.Value);
						AVDebugWriteLine(value.Value);

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
			catch (...) {}

			//Get OpenGL Triple Buffering setting
			try
			{
				AdlAppProperty adlProperty = AdlAppPropertyGet(adl_AppSelected(), L"EnableTrplBffr");
				for (AdlAppPropertyValue value : adlProperty.Values)
				{
					if (value.GpuId == gpuUniqueIdentifierHex)
					{
						bool convertedValue = (bool)wstring_to_int(value.Value);
						toggleswitch_OpenGLTripleBuffering().IsOn(convertedValue);
						break;
					}
				}
			}
			catch (...) {}

			//Get OpenGL 10-Bit Pixel Format setting
			//Global only setting
			toggleswitch_OpenGL10Bit().IsEnabled(false);

			//Set result
			AVDebugWriteLine("ADL loaded graphics values.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADL failed loading graphics values.");
		}
	}
}