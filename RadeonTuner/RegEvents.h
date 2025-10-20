#pragma once
#include "pch.h"
#include "MainPage.h"

namespace winrt::RadeonTuner::implementation
{
	//Fix second gpu support

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

	void MainPage::combobox_FrameGenSearchMode_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			DWORD newValue = sender.as<ComboBox>().SelectedIndex();
			if (!RegistrySet(HKEY_CURRENT_USER, L"Software\\AMD\\DVR", L"FrameGenSearchMode", newValue))
			{
				//Set result
				textblock_Status().Text(L"Failed setting motion search mode");
				AVDebugWriteLine(L"Failed setting motion search mode");
			}
			else
			{
				//Set result
				textblock_Status().Text(L"Motion search mode set to " + number_to_wstring(newValue));
				AVDebugWriteLine(L"Motion search mode set to " << newValue);
			}
		}
		catch (...) {}
	}

	void MainPage::combobox_FrameGenPerfMode_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			DWORD newValue = sender.as<ComboBox>().SelectedIndex();
			if (!RegistrySet(HKEY_CURRENT_USER, L"Software\\AMD\\DVR", L"FrameGenPerfMode", newValue))
			{
				//Set result
				textblock_Status().Text(L"Failed setting motion performance mode");
				AVDebugWriteLine(L"Failed setting motion performance mode");
			}
			else
			{
				//Set result
				textblock_Status().Text(L"Motion performance mode set to " + number_to_wstring(newValue));
				AVDebugWriteLine(L"Motion performance mode set to " << newValue);
			}
		}
		catch (...) {}
	}
}