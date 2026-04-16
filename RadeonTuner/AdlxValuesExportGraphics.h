#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesExportGraphics()
	{
		try
		{
			//Show file dialog
			std::wstring exportPath = filepicker_save(L"Export graphics settings...", { { L"Setting files", L"*.radg"} });

			//Check file path
			if (exportPath.empty())
			{
				ShowNotification(L"Graphics not exported, no path set");
				AVDebugWriteLine(L"Graphics not exported, no path set");
				return;
			}

			//Get selected application
			AdlApplication& selectedApp = AdlAppSelectedGet().value();

			//Save settings to file
			std::string exportPathA = wstring_to_string(exportPath);
			bool saveResult = GraphicsSettings_FileSave(selectedApp, exportPathA);

			//Set result
			if (saveResult)
			{
				ShowNotification(L"Graphics exported " + selectedApp.FileName);
				AVDebugWriteLine(L"Graphics exported " << selectedApp.FileName);
			}
			else
			{
				ShowNotification(L"Graphics export failed " + selectedApp.FileName);
				AVDebugWriteLine(L"Graphics export failed " << selectedApp.FileName);
			}
		}
		catch (...)
		{
			//Set result
			ShowNotification(L"Graphics export failed, exception");
			AVDebugWriteLine(L"Graphics export failed, exception");
		}
	}
}