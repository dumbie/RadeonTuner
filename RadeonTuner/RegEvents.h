#pragma once
#include "pch.h"
#include "MainPage.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::toggleswitch_OpenGLTripleBuffering_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			if (senderElement.IsOn())
			{
				std::vector<BYTE> settingBinary = { 49, 00 };
				if (!RegistrySet(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Class\\{4d36e968-e325-11ce-bfc1-08002be10318}\\0000\\UMD", L"EnableTripleBuffering", settingBinary))
				{
					textblock_Status().Text(L"Failed enabling triple buffering");
					AVDebugWriteLine(L"Failed enabling triple buffering");
					disable_saving = true;
					senderElement.IsOn(false);
					disable_saving = false;
				}
				else
				{
					textblock_Status().Text(L"Triple buffering enabled");
					AVDebugWriteLine(L"Triple buffering enabled");
				}
			}
			else
			{
				std::vector<BYTE> settingBinary = { 48, 00 };
				RegistrySet(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Class\\{4d36e968-e325-11ce-bfc1-08002be10318}\\0000\\UMD", L"EnableTripleBuffering", settingBinary);

				textblock_Status().Text(L"Triple buffering disabled");
				AVDebugWriteLine(L"Triple buffering disabled");
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_OpenGL10Bit_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			if (senderElement.IsOn())
			{
				DWORD settingDword = 1;
				if (!RegistrySet(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Class\\{4d36e968-e325-11ce-bfc1-08002be10318}\\0000", L"KMD_10BitMode", settingDword))
				{
					textblock_Status().Text(L"Failed enabling 10-Bit pixel format");
					AVDebugWriteLine(L"Failed enabling 10-Bit pixel format");
					disable_saving = true;
					senderElement.IsOn(false);
					disable_saving = false;
				}
				else
				{
					textblock_Status().Text(L"10-Bit pixel format enabled");
					AVDebugWriteLine(L"10-Bit pixel format enabled");
				}
			}
			else
			{
				DWORD settingDword = 2;
				RegistrySet(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Class\\{4d36e968-e325-11ce-bfc1-08002be10318}\\0000", L"KMD_10BitMode", settingDword);

				textblock_Status().Text(L"10-Bit pixel format disabled");
				AVDebugWriteLine(L"10-Bit pixel format disabled");
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_HagsSupport_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			if (senderElement.IsOn())
			{
				DWORD settingDword = 2;
				if (!RegistrySet(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Class\\{4d36e968-e325-11ce-bfc1-08002be10318}\\0000", L"KMD_EnableMSHWS", settingDword))
				{
					textblock_Status().Text(L"Failed enabling HAGS support");
					AVDebugWriteLine(L"Failed enabling HAGS support");
					disable_saving = true;
					senderElement.IsOn(false);
					disable_saving = false;
				}
				else
				{
					textblock_Status().Text(L"HAGS support enabled");
					AVDebugWriteLine(L"HAGS support enabled");
				}
			}
			else
			{
				DWORD settingDword = 0;
				RegistrySet(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Class\\{4d36e968-e325-11ce-bfc1-08002be10318}\\0000", L"KMD_EnableMSHWS", settingDword);

				textblock_Status().Text(L"HAGS support disabled");
				AVDebugWriteLine(L"HAGS support disabled");
			}
		}
		catch (...) {}
	}
}