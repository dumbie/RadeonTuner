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
				std::vector<BYTE> binary = RegistryGetBinary(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Class\\{4d36e968-e325-11ce-bfc1-08002be10318}\\0000\\UMD", L"EnableTripleBuffering");

				//Enable or disable interface
				toggleswitch_OpenGLTripleBuffering().IsEnabled(true);

				if (binary[0] == 48)
				{
					toggleswitch_OpenGLTripleBuffering().IsOn(false);
					AVDebugWriteLine("OpenGL triple buffering off.");
				}
				else
				{
					toggleswitch_OpenGLTripleBuffering().IsOn(true);
					AVDebugWriteLine("OpenGL triple buffering off.");
				}
			}
			else
			{
				//Enable or disable interface
				toggleswitch_OpenGLTripleBuffering().IsEnabled(false);
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