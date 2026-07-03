#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesImportDisplay()
	{
		try
		{
			//Show file dialog
			std::wstring importPath = filepicker_open(L"Import display settings...", { { L"Setting files", L"*.radd" } });

			//Check file path
			if (importPath.empty())
			{
				ShowNotification(L"Display not imported, no path set");
				AVDebugWriteLine(L"Display not imported, no path set");
				return;
			}

			AVDebugWriteLine("Importing display settings: " << importPath.c_str());

			//Load settings from file
			std::string importPathA = wstring_to_string(importPath);
			DisplaySettings displaySettings = DisplaySettings_FileLoad(importPathA).value();

			//Set settings values
			DisplaySettings_Profile_Convert_ToUI(displaySettings);

			//Set result
			ShowNotification(L"Display settings imported");
			AVDebugWriteLine(L"Display settings imported");
		}
		catch (...)
		{
			//Set result
			ShowNotification(L"Display not imported, exception");
			AVDebugWriteLine(L"Display not imported, exception");
		}
	}
}