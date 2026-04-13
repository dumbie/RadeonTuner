#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::PowerBoost_LoadApplications()
	{
		try
		{
			//Get power boost apps file path
			std::wstring pathSettingFileW = PathMerge(PathGetExecutableDirectory(), L"Profiles\\PowerBoostApps.json");
			std::string pathSettingFileA = wstring_to_string(pathSettingFileW);

			//Open power boost apps file
			std::string jsonString = file_to_string(pathSettingFileA);

			//Deserialize power boost apps
			powerBoostApps = jsonstring_to_struct<std::vector<std::wstring>>(jsonString);

			//Get combobox items
			ItemCollection itemCollection = combobox_PowerBoost_Applications().Items();

			//Remove applications
			int collectionSize = itemCollection.Size();
			for (int i = 0; i < collectionSize; i++)
			{
				itemCollection.RemoveAt(0);
			}

			//Add applications to combobox
			for (std::wstring powerBoostApp : powerBoostApps)
			{
				itemCollection.Append(box_value(powerBoostApp));
			}

			//Select first index
			combobox_PowerBoost_Applications().SelectedIndex(0);

			AVDebugWriteLine("Loaded power boost applications: " << powerBoostApps.size());
		}
		catch (...)
		{
			AVDebugWriteLine("Failed loading power boost applications (Exception)");
		}
	}
}