#pragma once
#include "pch.h"
#include "MainPage.h"

namespace winrt::RadeonTuner::implementation
{
	//Note: setting names can be found in amdadlx64.dll and amdkmdag.sys
	void MainPage::RegValuesLoad()
	{
		try
		{
			//OpenGL Triple Buffering
			std::vector<BYTE> binary = RegistryGetBinary(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Class\\" + gpuRegistryPath + L"\\UMD", L"EnableTripleBuffering");
			if (!binary.empty())
			{
				if (binary[0] == 48)
				{
					toggleswitch_OpenGLTripleBuffering().IsOn(false);
				}
				else
				{
					toggleswitch_OpenGLTripleBuffering().IsOn(true);
				}
			}

			//OpenGL 10-Bit Pixel Format
			std::optional<DWORD> dword = RegistryGetDword(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Class\\" + gpuRegistryPath, L"KMD_10BitMode");
			if (dword.has_value())
			{
				if (dword.value() == 1)
				{
					toggleswitch_OpenGL10Bit().IsOn(true);
				}
				else
				{
					toggleswitch_OpenGL10Bit().IsOn(false);
				}
			}

			//Microsoft HAGS Support
			//KMD_DisableNv2x3DCGWithMSHWS / KMD_EnableMSHWSQESSupport
			dword = RegistryGetDword(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Class\\" + gpuRegistryPath, L"KMD_EnableMSHWS");
			if (dword.has_value())
			{
				if (dword.value() == 2)
				{
					toggleswitch_HagsSupport().IsOn(true);
				}
				else
				{
					toggleswitch_HagsSupport().IsOn(false);
				}
			}

			//Texture Filtering Quality
			binary = RegistryGetBinary(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Class\\" + gpuRegistryPath + L"\\UMD", L"TFQ");
			if (!binary.empty())
			{
				if (binary[0] == 48)
				{
					//48 High
					combobox_TextureFilteringQuality().SelectedIndex(0);
				}
				else if (binary[0] == 49)
				{
					//49 Standard
					combobox_TextureFilteringQuality().SelectedIndex(1);
				}
				else if (binary[0] == 50)
				{
					//50 Performance
					combobox_TextureFilteringQuality().SelectedIndex(2);
				}
			}

			//Surface Format Optimization
			binary = RegistryGetBinary(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Class\\" + gpuRegistryPath + L"\\UMD", L"SurfaceFormatReplacements");
			if (!binary.empty())
			{
				if (binary[0] == 48)
				{
					toggleswitch_SurfaceFormatOptimization().IsOn(false);
				}
				else
				{
					toggleswitch_SurfaceFormatOptimization().IsOn(true);
				}
			}

			//Fluid Motion Search Mode
			dword = RegistryGetDword(HKEY_CURRENT_USER, L"Software\\AMD\\DVR", L"FrameGenSearchMode");
			if (dword.has_value())
			{
				combobox_FrameGenSearchMode().SelectedIndex(dword.value());
			}

			//Fluid Motion Performance Mode
			dword = RegistryGetDword(HKEY_CURRENT_USER, L"Software\\AMD\\DVR", L"FrameGenPerfMode");
			if (dword.has_value())
			{
				combobox_FrameGenPerfMode().SelectedIndex(dword.value());
			}

			//Fluid Motion Response Mode
			dword = RegistryGetDword(HKEY_CURRENT_USER, L"Software\\AMD\\DVR", L"FrameGenFallbackMode");
			if (dword.has_value())
			{
				combobox_FrameGenResponseMode().SelectedIndex(dword.value());
			}

			//Fluid Motion Algorithm
			//FrameGenAlgorithm

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