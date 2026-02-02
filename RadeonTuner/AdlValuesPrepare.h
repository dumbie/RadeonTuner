#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "AdlVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlValuesPrepare()
	{
		try
		{
			//Get combobox items
			ItemCollection itemCollection = combobox_AppSelect().Items();

			//Load applications
			adl_Apps = AdlAppsLoad(L"3D_User");

			//Add apps to combobox
			itemCollection.Append(box_value(L"Global"));
			for (AdlApps adlApp : adl_Apps)
			{
				itemCollection.Append(box_value(adlApp.FileName));
			}

			//Set result
			AVDebugWriteLine("ADL prepared.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADL preparation failed.");
		}
	}
}