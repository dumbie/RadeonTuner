#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::AdlxValuesLoadApplicationList(bool selectFirst)
	{
		try
		{
			//Get combobox items
			ItemCollection itemCollection = combobox_AppSelect().Items();

			//Clear combobox items
			itemCollection.Clear();

			//Load applications
			adl_Apps_Cache = AdlAppsLoad(L"3D_User");

			//Add global application
			AdlApplication globalApp{};
			globalApp.Global = true;
			globalApp.FileName = L"Global";
			globalApp.FilePath = L"Registry";
			adl_Apps_Cache.push_back(globalApp);

			//Sort applications by file name
			std::sort(adl_Apps_Cache.begin(), adl_Apps_Cache.end(), [](const AdlApplication& a, const AdlApplication& b) { return a.FileName.size() < b.FileName.size(); });

			//Add apps to combobox
			for (AdlApplication adlApp : adl_Apps_Cache)
			{
				itemCollection.Append(box_value(adlApp.FileName));
			}

			//Select first index
			if (selectFirst)
			{
				combobox_AppSelect().SelectedIndex(0);
			}

			//Set result
			AVDebugWriteLine("Listed ADL applications in combobox.");
			return true;
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("Failed listing ADL applications in combobox.");
			return false;
		}
	}

	void MainPage::AdlValuesLoadGraphicsApp()
	{
		try
		{
			//Get selected application
			auto selectedApp = AdlAppSelectedGet();

			//Check selected application
			if (!selectedApp.has_value())
			{
				AVDebugWriteLine("ADL application is not selected.");
				return;
			}

			//Get current and default settings
			graphicsSettingsCurrent = GraphicsSettings_Generate_FromADLApp(selectedApp.value()).value();

			//Convert settings values to interface
			GraphicsSettings_Convert_ToUI_ADL(graphicsSettingsCurrent);

			//Set result
			AVDebugWriteLine("ADL graphics app values loaded.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADL failed loading graphics app values.");
		}
	}
}