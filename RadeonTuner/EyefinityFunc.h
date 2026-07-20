#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::Eyefinity_Applications_List(bool selectFirst)
	{
		try
		{
			//Get combobox items
			ItemCollection itemCollection = combobox_Eyefinity_Applications().Items();

			//Clear combobox items
			itemCollection.Clear();

			//Add applications to combobox
			for (std::wstring EyefinityApp : eyefinityAppsCache)
			{
				itemCollection.Append(box_value(EyefinityApp));
			}

			//Select first index
			if (selectFirst)
			{
				combobox_Eyefinity_Applications().SelectedIndex(0);
			}

			//Return result
			AVDebugWriteLine("Listed Eyefinity applications: " << eyefinityAppsCache.size());
			return true;
		}
		catch (...)
		{
			AVDebugWriteLine("Failed listing Eyefinity applications (Exception)");
			return false;
		}
	}

	bool MainPage::Eyefinity_Applications_LoadFromFile()
	{
		try
		{
			//Get Eyefinity apps file path
			std::wstring pathSettingFileW = PathMerge(PathGetExecutableDirectory(), L"Profiles\\EyefinityApps.json");
			std::string pathSettingFileA = wstring_to_string(pathSettingFileW);

			//Open Eyefinity apps file
			std::string jsonString = file_to_string(pathSettingFileA);

			//Deserialize Eyefinity apps
			eyefinityAppsCache = jsonstring_to_struct<std::vector<std::wstring>>(jsonString);

			//Return result
			AVDebugWriteLine("Loaded Eyefinity applications: " << eyefinityAppsCache.size());
			return true;
		}
		catch (...)
		{
			AVDebugWriteLine("Failed loading Eyefinity applications (Exception)");
			return false;
		}
	}

	bool MainPage::Eyefinity_Applications_SaveToFile()
	{
		try
		{
			//Convert json to string
			std::string jsonString = struct_to_jsonstring(eyefinityAppsCache, true);

			//Get Eyefinity apps file path
			std::wstring pathSettingFileW = PathMerge(PathGetExecutableDirectory(), L"Profiles\\EyefinityApps.json");
			std::string pathSettingFileA = wstring_to_string(pathSettingFileW);

			//Save application json file
			string_to_file(pathSettingFileA, jsonString);

			//Return result
			AVDebugWriteLine("Saved Eyefinity applications: " << eyefinityAppsCache.size());
			return true;
		}
		catch (...)
		{
			AVDebugWriteLine("Failed saving Eyefinity applications (Exception)");
			return false;
		}
	}
}