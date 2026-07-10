#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::button_Eyefinity_AppAddExe_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Show file dialog
			std::wstring importPath = filepicker_open(NULL, L"Select application executable...", { { L"Executable files", L"*.exe" }, { L"Binary files", L"*.bin" } });

			//Check file path
			if (importPath.empty())
			{
				ShowNotification(L"Application not added, no path set");
				AVDebugWriteLine(L"Application not added, no path set");
				return;
			}

			//Extract file name from path
			std::wstring fileName = PathGetFileName(importPath);

			//Check double application
			if (array_contains(eyefinityAppsCache, fileName))
			{
				ShowNotification(L"Application not added, already exists");
				AVDebugWriteLine(L"Application not added, already exists");
				return;
			}

			//Add application to list
			eyefinityAppsCache.push_back(fileName);

			//Save applications
			Eyefinity_Applications_SaveToFile();

			//List applications
			Eyefinity_Applications_List();

			//Show notification
			ShowNotification(L"Application added");
			AVDebugWriteLine(L"Application added");
		}
		catch (...) {}
	}

	void MainPage::button_Eyefinity_AppRemove_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get selected index
			int selectedIndex = combobox_Eyefinity_Applications().SelectedIndex();

			//Remove application from list
			eyefinityAppsCache.erase(eyefinityAppsCache.begin() + selectedIndex);

			//Save applications
			Eyefinity_Applications_SaveToFile();

			//List applications
			Eyefinity_Applications_List();

			//Show notification
			ShowNotification(L"Application removed");
			AVDebugWriteLine(L"Application removed");
		}
		catch (...) {}
	}

	void MainPage::button_Eyefinity_Remove_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Delete all Eyefinity configurations
			if (Adl_Eyefinity_Delete_All(adl_Display_AdapterIndex))
			{
				ShowNotification(L"Removed Eyefinity");
				AVDebugWriteLine(L"Removed Eyefinity");
			}
			else
			{
				ShowNotification(L"Failed removing Eyefinity");
				AVDebugWriteLine(L"Failed removing Eyefinity");
			}
		}
		catch (...) {}
	}

	void MainPage::button_Eyefinity_Create_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Create custom eyefinity
			if (Adl_Eyefinity_Create_Custom(adl_Display_AdapterIndex))
			{
				ShowNotification(L"Created Eyefinity");
				AVDebugWriteLine(L"Created Eyefinity");
			}
			else
			{
				ShowNotification(L"Failed creating Eyefinity");
				AVDebugWriteLine(L"Failed creating Eyefinity");
			}
		}
		catch (...) {}
	}

	void MainPage::button_Eyefinity_Enable_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Enable Eyefinity
			if (Adl_Eyefinity_Toggle(adl_Display_AdapterIndex, true))
			{
				ShowNotification(L"Enabled Eyefinity");
				AVDebugWriteLine(L"Enabled Eyefinity");
			}
			else
			{
				ShowNotification(L"Failed enabling Eyefinity");
				AVDebugWriteLine(L"Failed enabling Eyefinity");
			}
		}
		catch (...) {}
	}

	void MainPage::button_Eyefinity_Disable_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Disable Eyefinity
			if (Adl_Eyefinity_Toggle(adl_Display_AdapterIndex, false))
			{
				ShowNotification(L"Disabled Eyefinity");
				AVDebugWriteLine(L"Disabled Eyefinity");
			}
			else
			{
				ShowNotification(L"Failed disabling Eyefinity");
				AVDebugWriteLine(L"Failed disabling Eyefinity");
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_Eyefinity_Automatic_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			if (senderElement.IsOn())
			{
				//Update setting
				AppVariables::Settings.Set("EyefinityAutomatic", true);

				//Enable interface
				combobox_Eyefinity_Applications().IsEnabled(true);
				button_Eyefinity_AddExe().IsEnabled(true);
				button_Eyefinity_Remove().IsEnabled(true);

				//Show notification
				ShowNotification(L"Automatic Eyefinity enabled");
				AVDebugWriteLine(L"Automatic Eyefinity enabled");
			}
			else
			{
				//Update setting
				AppVariables::Settings.Set("EyefinityAutomatic", false);

				//Disable interface
				combobox_Eyefinity_Applications().IsEnabled(false);
				button_Eyefinity_AddExe().IsEnabled(false);
				button_Eyefinity_Remove().IsEnabled(false);

				//Show notification
				ShowNotification(L"Automatic Eyefinity disabled");
				AVDebugWriteLine(L"Automatic Eyefinity disabled");
			}
		}
		catch (...) {}
	}
}