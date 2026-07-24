#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::PowerBoost_Applications_List(bool selectFirst)
	{
		try
		{
			//Get combobox items
			ItemCollection itemCollection = combobox_PowerBoost_Applications().Items();

			//Clear combobox items
			itemCollection.Clear();

			//Add applications to combobox
			for (std::wstring powerBoostApp : powerBoostAppsCache)
			{
				itemCollection.Append(box_value(powerBoostApp));
			}

			//Select first index
			if (selectFirst)
			{
				combobox_PowerBoost_Applications().SelectedIndex(0);
			}

			//Return result
			AVDebugWriteLine("Listed power boost applications: " << powerBoostAppsCache.size());
			return true;
		}
		catch (...)
		{
			AVDebugWriteLine("Failed listing power boost applications (Exception)");
			return false;
		}
	}

	bool MainPage::PowerBoost_Applications_LoadFromFile()
	{
		try
		{
			//Get power boost apps file path
			std::wstring pathSettingFileW = PathMerge(PathGetAppRoot(), L"Profiles\\PowerBoostApps.json");

			//Open power boost apps file
			std::wstring jsonString = file_to_string(pathSettingFileW);

			//Deserialize power boost apps
			powerBoostAppsCache = jsonstring_to_struct<std::vector<std::wstring>>(jsonString);

			//Return result
			AVDebugWriteLine("Loaded power boost applications: " << powerBoostAppsCache.size());
			return true;
		}
		catch (...)
		{
			AVDebugWriteLine("Failed loading power boost applications (Exception)");
			return false;
		}
	}

	bool MainPage::PowerBoost_Applications_SaveToFile()
	{
		try
		{
			//Convert json to string
			std::wstring jsonStringW = struct_to_jsonstring(powerBoostAppsCache, true);

			//Get power boost apps file path
			std::wstring pathSettingFileW = PathMerge(PathGetAppRoot(), L"Profiles\\PowerBoostApps.json");

			//Save application json file
			string_to_file(pathSettingFileW, jsonStringW);

			//Return result
			AVDebugWriteLine("Saved power boost applications: " << powerBoostAppsCache.size());
			return true;
		}
		catch (...)
		{
			AVDebugWriteLine("Failed saving power boost applications (Exception)");
			return false;
		}
	}
}