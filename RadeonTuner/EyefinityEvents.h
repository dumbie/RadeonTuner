#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	winrt::fire_and_forget MainPage::button_Eyefinity_AppAddExe_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { co_return; }

			//Show application picker
			auto selectedApps = co_await AdlAppPickerAdd();
			int selectedAppsCount = selectedApps.Size();

			//Check selected items
			if (selectedAppsCount == 0)
			{
				ShowNotification(L"No applications selected");
				AVDebugWriteLine(L"No applications selected.");
				co_return;
			}

			//Add selected items
			int addCount = 0;
			for (auto const& app : selectedApps)
			{
				//Extract file name from path
				std::wstring fileName = hstring_to_wstring(app.ExeName());

				//Check double application
				if (array_contains(eyefinityAppsCache, fileName))
				{
					continue;
				}

				//Add application to list
				eyefinityAppsCache.push_back(fileName);
				addCount++;
			}

			//Check if applications were added
			if (addCount > 0)
			{
				//Save applications
				Eyefinity_Applications_SaveToFile();

				//List applications
				Eyefinity_Applications_List(true);
			}

			//Show notification
			//Fix show fail and duplicate count
			ShowNotification(L"Applications added: " + number_to_wstring(addCount) + L" / " + number_to_wstring(selectedAppsCount));
			AVDebugWriteLine(L"Applications added: " << addCount << L" / " << selectedAppsCount);
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
			Eyefinity_Applications_List(true);

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
			//Disable Automatic Eyefinity
			toggleswitch_Eyefinity_Automatic().IsOn(false);

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
			//Disable Automatic Eyefinity
			toggleswitch_Eyefinity_Automatic().IsOn(false);

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
			//Disable Automatic Eyefinity
			toggleswitch_Eyefinity_Automatic().IsOn(false);

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
			//Disable Automatic Eyefinity
			toggleswitch_Eyefinity_Automatic().IsOn(false);

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