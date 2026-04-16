#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::button_PowerBoost_AddExe_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Show file dialog
			std::wstring importPath = filepicker_open(L"Select application executable...", { { L"Executable files", L"*.exe" }, { L"Binary files", L"*.bin" } });

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
			if (array_contains(powerBoostAppsCache, fileName))
			{
				ShowNotification(L"Application not added, already exists");
				AVDebugWriteLine(L"Application not added, already exists");
				return;
			}

			//Add application to list
			powerBoostAppsCache.push_back(fileName);

			//Save applications
			PowerBoost_Applications_SaveToFile();

			//List applications
			PowerBoost_Applications_List();

			//Show notification
			ShowNotification(L"Application added");
			AVDebugWriteLine(L"Application added");
		}
		catch (...) {}
	}

	void MainPage::button_PowerBoost_Remove_Click(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Get selected index
			int selectedIndex = combobox_PowerBoost_Applications().SelectedIndex();

			//Remove application from list
			powerBoostAppsCache.erase(powerBoostAppsCache.begin() + selectedIndex);

			//Save applications
			PowerBoost_Applications_SaveToFile();

			//List applications
			PowerBoost_Applications_List();

			//Show notification
			ShowNotification(L"Application removed");
			AVDebugWriteLine(L"Application removed");
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_PowerBoost_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving) { return; }

			//Get toggle switch value
			bool toggleSwitch = sender.as<ToggleSwitch>().IsOn();

			//Check if Power Boost is enabled
			if (toggleSwitch)
			{
				//Hide or show settings
				grid_Power_Limit_PB().Visibility(Visibility::Visible);
				grid_Power_Voltage_PB().Visibility(Visibility::Visible);
				grid_Power_TDC_PB().Visibility(Visibility::Visible);
			}
			else
			{
				//Hide or show settings
				grid_Power_Limit_PB().Visibility(Visibility::Collapsed);
				grid_Power_Voltage_PB().Visibility(Visibility::Collapsed);
				grid_Power_TDC_PB().Visibility(Visibility::Collapsed);
			}
		}
		catch (...) {}
	}
}