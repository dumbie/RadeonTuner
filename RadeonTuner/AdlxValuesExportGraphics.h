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

			//Save settings to file
			std::string exportPathA = wstring_to_string(exportPath);
			bool saveResult = GraphicsSettings_FileSave(graphicsSettingsCurrent, exportPathA);

			//Set result
			if (saveResult)
			{
				ShowNotification(L"Graphics settings exported");
				AVDebugWriteLine(L"Graphics settings exported");
			}
			else
			{
				ShowNotification(L"Graphics export failed");
				AVDebugWriteLine(L"Graphics export failed");
			}
		}
		catch (...)
		{
			//Set result
			ShowNotification(L"Graphics not exported, exception");
			AVDebugWriteLine(L"Graphics not exported, exception");
		}
	}
}