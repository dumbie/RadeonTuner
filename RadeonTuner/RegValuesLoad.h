#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlRegistry.h"

namespace winrt::RadeonTuner::implementation
{
	//Note: setting names can be found in amdadlx64.dll and amdkmdag.sys
	void MainPage::RegValuesLoad()
	{
		try
		{
			//Fix find a way to see if setting is supported by selected gpu.

			//Variables
			std::optional<DWORD> resultDword;
			std::string resultString = "";
			int resultInt = -1;

			//OpenGL Triple Buffering
			//EnableTripleBuffering (Binary (string) 3000 = 0 (Off) / 3100 = 1 (On))
			resultString = AdlRegistrySettingGetString(adl_AdapterIndex, "UMD", "EnableTripleBuffering");
			if (!resultString.empty())
			{
				if (resultString == "0")
				{
					toggleswitch_OpenGLTripleBuffering().IsOn(false);
				}
				else
				{
					toggleswitch_OpenGLTripleBuffering().IsOn(true);
				}
			}
			else
			{
				toggleswitch_OpenGLTripleBuffering().IsOn(false);
			}

			//OpenGL 10-Bit Pixel Format
			//KMD_10BitMode (Dword (int) 1 = On / 2 = Off)
			resultInt = AdlRegistrySettingGetInt(adl_AdapterIndex, "", "KMD_10BitMode");
			if (resultInt > 0)
			{
				if (resultInt == 1)
				{
					toggleswitch_OpenGL10Bit().IsOn(true);
				}
				else
				{
					toggleswitch_OpenGL10Bit().IsOn(false);
				}
			}
			else
			{
				toggleswitch_OpenGL10Bit().IsOn(false);
			}

			//Microsoft HAGS Support
			//KMD_EnableMSHWS (Dword (int) 2 = On / 0 = Off)
			//KMD_DisableNv2x3DCGWithMSHWS / KMD_EnableMSHWSQESSupport
			resultInt = AdlRegistrySettingGetInt(adl_AdapterIndex, "", "KMD_EnableMSHWS");
			if (resultInt > 0)
			{
				if (resultInt == 2)
				{
					toggleswitch_HagsSupport().IsOn(true);
				}
				else
				{
					toggleswitch_HagsSupport().IsOn(false);
				}
			}
			else
			{
				toggleswitch_HagsSupport().IsOn(false);
			}

			//Texture Filtering Quality
			//TFQ (Binary (string) 3000 = 0 (High) / 3100 = 1 (Standard) / 3200 = 2 (Performance))
			resultString = AdlRegistrySettingGetString(adl_AdapterIndex, "UMD", "TFQ");
			if (!resultString.empty())
			{
				if (resultString == "0")
				{
					combobox_TextureFilteringQuality().SelectedIndex(0);
				}
				else if (resultString == "1")
				{
					combobox_TextureFilteringQuality().SelectedIndex(1);
				}
				else if (resultString == "2")
				{
					combobox_TextureFilteringQuality().SelectedIndex(2);
				}
			}
			else
			{
				combobox_TextureFilteringQuality().SelectedIndex(1);
			}

			//Surface Format Optimization
			//SurfaceFormatReplacements (Binary (string) 3000 = 0 (Off) / 3100 = 1 (On))
			resultString = AdlRegistrySettingGetString(adl_AdapterIndex, "UMD", "SurfaceFormatReplacements");
			if (!resultString.empty())
			{
				if (resultString == "0")
				{
					toggleswitch_SurfaceFormatOptimization().IsOn(false);
				}
				else
				{
					toggleswitch_SurfaceFormatOptimization().IsOn(true);
				}
			}
			else
			{
				toggleswitch_SurfaceFormatOptimization().IsOn(false);
			}

			//Fluid Motion Search Mode
			//FrameGenSearchMode (Dword (int) 0 = Auto / 1 = Standard / 2 = High)
			resultDword = RegistryGetDword(HKEY_CURRENT_USER, L"Software\\AMD\\DVR", L"FrameGenSearchMode");
			if (resultDword.has_value())
			{
				combobox_FrameGenSearchMode().SelectedIndex(resultDword.value());
			}
			else
			{
				combobox_FrameGenSearchMode().SelectedIndex(0);
			}

			//Fluid Motion Performance Mode
			//FrameGenPerfMode (Dword (int) 0 = Auto / 1 = Quality / 2 = Performance)
			resultDword = RegistryGetDword(HKEY_CURRENT_USER, L"Software\\AMD\\DVR", L"FrameGenPerfMode");
			if (resultDword.has_value())
			{
				combobox_FrameGenPerfMode().SelectedIndex(resultDword.value());
			}
			else
			{
				combobox_FrameGenPerfMode().SelectedIndex(0);
			}

			//Fluid Motion Response Mode
			//FrameGenFallbackMode (Dword (int) 0 = Blended Frame / 1 = Repeat Frame)
			resultDword = RegistryGetDword(HKEY_CURRENT_USER, L"Software\\AMD\\DVR", L"FrameGenFallbackMode");
			if (resultDword.has_value())
			{
				combobox_FrameGenResponseMode().SelectedIndex(resultDword.value());
			}
			else
			{
				combobox_FrameGenResponseMode().SelectedIndex(0);
			}

			//Fluid Motion Algorithm
			//FrameGenAlgorithm

			//FSR Override Upscaling
			//FsrOverride (Binary (string) 3000 = 0 (Off) / 3100 = 1 (On))
			resultString = AdlRegistrySettingGetString(adl_AdapterIndex, "UMD", "FsrOverride");
			if (!resultString.empty())
			{
				if (resultString == "0")
				{
					toggleswitch_FsrOverrideUpscaling().IsOn(false);
				}
				else
				{
					toggleswitch_FsrOverrideUpscaling().IsOn(true);
				}
			}
			else
			{
				toggleswitch_FsrOverrideUpscaling().IsOn(false);
			}

			//FSR Override Frame Generation
			//NRC = Neural Radiance Cache
			//MLD = Machine Learning Ray Regeneration Denoiser
			//MlfiOverride = Machine Learning Frame Interpolation
			//MfgOverride = Machine Learning Multi Frame Generation
			//MlfiOverride (Binary (string) 3000 = 0 (Off) / 3100 = 1 (On))
			resultString = AdlRegistrySettingGetString(adl_AdapterIndex, "UMD", "MlfiOverride");
			if (!resultString.empty())
			{
				if (resultString == "0")
				{
					toggleswitch_FsrOverrideFrameGen().IsOn(false);
				}
				else
				{
					toggleswitch_FsrOverrideFrameGen().IsOn(true);
				}
			}
			else
			{
				toggleswitch_FsrOverrideFrameGen().IsOn(false);
			}

			//Set result
			AVDebugWriteLine("Registry values loaded.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("Registry failed loading values.");
		}
	}
}