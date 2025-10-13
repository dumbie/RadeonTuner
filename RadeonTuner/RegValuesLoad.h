#pragma once
#include "pch.h"
#include "MainPage.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::RegValuesLoad()
	{
		try
		{
			//OpenGL Triple Buffering
			if (RegistryCheck(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Class\\{4d36e968-e325-11ce-bfc1-08002be10318}\\0000\\UMD", L"EnableTripleBuffering"))
			{
				//Enable or disable interface
				toggleswitch_OpenGLTripleBuffering().IsEnabled(true);

				//Check value
				std::vector<BYTE> binary = RegistryGetBinary(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Class\\{4d36e968-e325-11ce-bfc1-08002be10318}\\0000\\UMD", L"EnableTripleBuffering");
				if (binary[0] == 48)
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
				//Enable or disable interface
				toggleswitch_OpenGLTripleBuffering().IsEnabled(false);
			}

			//OpenGL 10-Bit Pixel Format
			if (RegistryCheck(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Class\\{4d36e968-e325-11ce-bfc1-08002be10318}\\0000", L"KMD_10BitMode"))
			{
				//Enable or disable interface
				toggleswitch_OpenGL10Bit().IsEnabled(true);

				//Check value
				std::optional<DWORD> dword = RegistryGetDword(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Class\\{4d36e968-e325-11ce-bfc1-08002be10318}\\0000", L"KMD_10BitMode");
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
			}
			else
			{
				//Enable or disable interface
				toggleswitch_OpenGL10Bit().IsEnabled(false);
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