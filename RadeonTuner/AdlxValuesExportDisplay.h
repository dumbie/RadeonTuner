#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesExportDisplay()
	{
		try
		{
			//Show file dialog
			std::wstring exportPath = filepicker_save(L"Export display settings...", { { L"Setting files", L"*.radd" } });

			//Check file path
			if (exportPath.empty())
			{
				ShowNotification(L"Display not exported, no path set");
				AVDebugWriteLine(L"Display not exported, no path set");
				return;
			}

			//Generate settings
			DisplaySettings displaySettings = DisplaySettings_Generate_FromUI().value();

			//Save settings to file
			std::string exportPathA = wstring_to_string(exportPath);
			bool saveResult = DisplaySettings_FileSave(displaySettings, exportPathA);

			//Set result
			if (saveResult)
			{
				ShowNotification(L"Display exported");
				AVDebugWriteLine(L"Display exported");
			}
			else
			{
				ShowNotification(L"Display export failed");
				AVDebugWriteLine(L"Display export failed");
			}
		}
		catch (...)
		{
			//Set result
			ShowNotification(L"Display not exported, exception");
			AVDebugWriteLine(L"Display not exported, exception");
		}
	}
}