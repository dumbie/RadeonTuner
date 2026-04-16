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
			AdlApplication adlApplication = GraphicsSettings_FileLoad(importPathA).value();

			//DriverBug#2
			adlApplication.FilePath = L"*\\*";

			//Check if application already exists
			if (AdlAppExists(adlApplication.FileName, adlApplication.FilePath, adlApplication.DriverArea))
			{
				std::wstring messageResult = AVTaskDialogStr(NULL, L"RadeonTuner", L"Application already exists and settings will be overwritten, continue import?", L"", { L"Yes", L"No" }, false);
				if (messageResult == L"No")
				{
					//Set result
					ShowNotification(L"Application already exists");
					AVDebugWriteLine(L"Application already exists");
					return;
				}
			}

			//Save application settings
			AdlAppPropertySave(adlApplication);

			//Reload applications
			AdlAppInterfaceListLoad();

			//Select application
			combobox_AppSelect().SelectedIndex(0);

			//Set result
			ShowNotification(L"Graphics imported " + adlApplication.FileName);
			AVDebugWriteLine(L"Graphics imported " << adlApplication.FileName);
		}
		catch (...)
		{
			//Set result
			ShowNotification(L"Graphics import failed, exception");
			AVDebugWriteLine(L"Graphics import failed, exception");
		}
	}
}