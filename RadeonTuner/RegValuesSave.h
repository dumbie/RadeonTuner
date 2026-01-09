#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlRegistry.h"

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
				if (!AdlRegistrySettingSet(adl_AdapterIndex, "UMD", "EnableTripleBuffering", "1"))
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
				AdlRegistrySettingSet(adl_AdapterIndex, "UMD", "EnableTripleBuffering", "0");

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
				if (!AdlRegistrySettingSet(adl_AdapterIndex, "", "KMD_10BitMode", 1))
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
				AdlRegistrySettingSet(adl_AdapterIndex, "", "KMD_10BitMode", 2);

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
				if (!AdlRegistrySettingSet(adl_AdapterIndex, "", "KMD_EnableMSHWS", 2))
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
				AdlRegistrySettingSet(adl_AdapterIndex, "", "KMD_EnableMSHWS", 0);

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

			//Set setting value
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

			//Set setting value
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

	void MainPage::combobox_FrameGenResponseMode_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			DWORD newValue = sender.as<ComboBox>().SelectedIndex();

			//Set setting value
			if (!RegistrySet(HKEY_CURRENT_USER, L"Software\\AMD\\DVR", L"FrameGenFallbackMode", newValue))
			{
				//Set result
				textblock_Status().Text(L"Failed setting motion response mode");
				AVDebugWriteLine(L"Failed setting motion response mode");
			}
			else
			{
				//Set result
				textblock_Status().Text(L"Motion response mode set to " + number_to_wstring(newValue));
				AVDebugWriteLine(L"Motion response mode set to " << newValue);
			}
		}
		catch (...) {}
	}

	void MainPage::combobox_TextureFilteringQuality_SelectionChanged(IInspectable const& sender, SelectionChangedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get setting value
			DWORD newValue = sender.as<ComboBox>().SelectedIndex();
			std::string settingBinary = "";
			if (newValue == 0)
			{
				//High
				settingBinary = "0";
			}
			else if (newValue == 1)
			{
				//Standard
				settingBinary = "1";
			}
			else if (newValue == 2)
			{
				//Performance
				settingBinary = "2";
			}

			//Set setting value
			if (!AdlRegistrySettingSet(adl_AdapterIndex, "UMD", "TFQ", settingBinary))
			{
				//Set result
				textblock_Status().Text(L"Failed setting filtering quality");
				AVDebugWriteLine(L"Failed setting filtering quality");
			}
			else
			{
				//Set result
				textblock_Status().Text(L"Filtering quality set to " + number_to_wstring(newValue));
				AVDebugWriteLine(L"Filtering quality set to " << newValue);
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_SurfaceFormatOptimization_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			if (senderElement.IsOn())
			{
				if (!AdlRegistrySettingSet(adl_AdapterIndex, "UMD", "SurfaceFormatReplacements", "1"))
				{
					textblock_Status().Text(L"Failed enabling format optimization");
					AVDebugWriteLine(L"Failed enabling format optimization");
					disable_saving = true;
					senderElement.IsOn(false);
					disable_saving = false;
				}
				else
				{
					textblock_Status().Text(L"Format optimization enabled");
					AVDebugWriteLine(L"Format optimization enabled");
				}
			}
			else
			{
				AdlRegistrySettingSet(adl_AdapterIndex, "UMD", "SurfaceFormatReplacements", "0");

				textblock_Status().Text(L"Format optimization disabled");
				AVDebugWriteLine(L"Format optimization disabled");
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_FsrOverrideUpscaling_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			if (senderElement.IsOn())
			{
				if (!AdlRegistrySettingSet(adl_AdapterIndex, "UMD", "FsrOverride", "1"))
				{
					textblock_Status().Text(L"Failed enabling FSR override");
					AVDebugWriteLine(L"Failed enabling FSR override");
					disable_saving = true;
					senderElement.IsOn(false);
					disable_saving = false;
				}
				else
				{
					textblock_Status().Text(L"FSR override enabled");
					AVDebugWriteLine(L"FSR override enabled");
				}
			}
			else
			{
				if (!AdlRegistrySettingSet(adl_AdapterIndex, "UMD", "FsrOverride", "0"))
				{
					textblock_Status().Text(L"Failed disabling FSR override");
					AVDebugWriteLine(L"Failed disabling FSR override");
					disable_saving = true;
					senderElement.IsOn(true);
					disable_saving = false;
				}
				else
				{
					textblock_Status().Text(L"FSR override disabled");
					AVDebugWriteLine(L"FSR override disabled");
				}
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_FsrOverrideFrameGen_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			if (senderElement.IsOn())
			{
				if (!AdlRegistrySettingSet(adl_AdapterIndex, "UMD", "MlfiOverride", "1"))
				{
					textblock_Status().Text(L"Failed enabling FSR override");
					AVDebugWriteLine(L"Failed enabling FSR override");
					disable_saving = true;
					senderElement.IsOn(false);
					disable_saving = false;
				}
				else
				{
					textblock_Status().Text(L"FSR override enabled");
					AVDebugWriteLine(L"FSR override enabled");
				}
			}
			else
			{
				if (!AdlRegistrySettingSet(adl_AdapterIndex, "UMD", "MlfiOverride", "0"))
				{
					textblock_Status().Text(L"Failed disabling FSR override");
					AVDebugWriteLine(L"Failed disabling FSR override");
					disable_saving = true;
					senderElement.IsOn(true);
					disable_saving = false;
				}
				else
				{
					textblock_Status().Text(L"FSR override disabled");
					AVDebugWriteLine(L"FSR override disabled");
				}
			}
		}
		catch (...) {}
	}
}