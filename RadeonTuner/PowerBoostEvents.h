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
			if (array_contains(powerBoostApps, fileName))
			{
				ShowNotification(L"Application not added, already exists");
				AVDebugWriteLine(L"Application not added, already exists");
				return;
			}

			//Add application to list
			powerBoostApps.push_back(fileName);

			//Convert json to string
			std::string jsonString = struct_to_jsonstring(powerBoostApps, true);

			//Get power boost apps file path
			std::wstring pathSettingFileW = PathMerge(PathGetExecutableDirectory(), L"Profiles\\PowerBoostApps.json");
			std::string pathSettingFileA = wstring_to_string(pathSettingFileW);

			//Save application json file
			string_to_file(pathSettingFileA, jsonString);

			//Reload applications
			PowerBoost_LoadApplications();

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
			powerBoostApps.erase(powerBoostApps.begin() + selectedIndex);

			//Convert json to string
			std::string jsonString = struct_to_jsonstring(powerBoostApps, true);

			//Get power boost apps file path
			std::wstring pathSettingFileW = PathMerge(PathGetExecutableDirectory(), L"Profiles\\PowerBoostApps.json");
			std::string pathSettingFileA = wstring_to_string(pathSettingFileW);

			//Save application json file
			string_to_file(pathSettingFileA, jsonString);

			//Reload applications
			PowerBoost_LoadApplications();

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
			grid_Power_Limit_PB().Visibility(Visibility::Visible);
			grid_Power_Voltage_PB().Visibility(Visibility::Visible);
			grid_Power_TDC_PB().Visibility(Visibility::Visible);
		}
		catch (...) {}
	}
}