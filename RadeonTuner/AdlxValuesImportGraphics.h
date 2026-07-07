#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesImportGraphics()
	{
		try
		{
			//Show file dialog
			std::wstring importPath = filepicker_open(L"Import graphics settings...", { { L"Setting files", L"*.radg" } });

			//Check file path
			if (importPath.empty())
			{
				ShowNotification(L"Graphics not imported, no path set");
				AVDebugWriteLine(L"Graphics not imported, no path set");
				return;
			}

			AVDebugWriteLine("Importing graphics settings: " << importPath.c_str());

			//Load settings from file
			std::string importPathA = wstring_to_string(importPath);
			GraphicsSettings graphicsSettings = GraphicsSettings_FileLoad(importPathA).value();

			//Set settings values
			GraphicsSettings_Convert_ToUI_Current(graphicsSettings);

			//Set result
			ShowNotification(L"Graphics settings imported");
			AVDebugWriteLine(L"Graphics settings imported");
		}
		catch (...)
		{
			//Set result
			ShowNotification(L"Graphics not imported, exception");
			AVDebugWriteLine(L"Graphics not imported, exception");
		}
	}
}