#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::PowerBoost_Applications_List()
	{
		try
		{
			//Get combobox items
			ItemCollection itemCollection = combobox_PowerBoost_Applications().Items();

			//Remove applications
			int collectionSize = itemCollection.Size();
			for (int i = 0; i < collectionSize; i++)
			{
				itemCollection.RemoveAt(0);
			}

			//Add applications to combobox
			for (std::wstring powerBoostApp : powerBoostAppsCache)
			{
				itemCollection.Append(box_value(powerBoostApp));
			}

			//Select first index
			combobox_PowerBoost_Applications().SelectedIndex(0);

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
			std::wstring pathSettingFileW = PathMerge(PathGetExecutableDirectory(), L"Profiles\\PowerBoostApps.json");
			std::string pathSettingFileA = wstring_to_string(pathSettingFileW);

			//Open power boost apps file
			std::string jsonString = file_to_string(pathSettingFileA);

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
			std::string jsonString = struct_to_jsonstring(powerBoostAppsCache, true);

			//Get power boost apps file path
			std::wstring pathSettingFileW = PathMerge(PathGetExecutableDirectory(), L"Profiles\\PowerBoostApps.json");
			std::string pathSettingFileA = wstring_to_string(pathSettingFileW);

			//Save application json file
			string_to_file(pathSettingFileA, jsonString);

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