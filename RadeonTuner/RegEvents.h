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
}