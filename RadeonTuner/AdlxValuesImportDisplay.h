#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	winrt::fire_and_forget MainPage::AdlxValuesImportDisplay()
	{
		try
		{
			//Show file dialog
			std::wstring importPath = filepicker_open(NULL, L"Import display settings...", { { L"Setting files", L"*.radd" } });

			//Check file path
			if (importPath.empty())
			{
				ShowNotification(L"Display not imported, no path set");
				AVDebugWriteLine(L"Display not imported, no path set");
				co_return;
			}

			AVDebugWriteLine("Importing display settings: " << importPath.c_str());

			//Load settings from file
			DisplaySettings displaySettings = DisplaySettings_FileLoad(importPath).value();

			//Check device identifier
			std::wstring device_id_import_w = displaySettings.DeviceId.value();
			std::wstring device_id_current_w = AdlxGetDisplayIdentifier(adl_Display_AdapterIndex, adl_Display_DisplayIndex);
			if (!device_id_import_w.empty() && !device_id_current_w.empty())
			{
				if (device_id_import_w != device_id_current_w)
				{
					//Show messagebox
					int messageResult = co_await ShowMessageBox(L"Display does not match", L"Display settings do not match your selected display, continue import?", { L"Yes", L"No" });

					//Check messagebox result
					if (messageResult == 1)
					{
						//Set result
						ShowNotification(L"Display does not match");
						AVDebugWriteLine(L"Display does not match");
						co_return;
					}
				}
			}

			//Set settings values
			DisplaySettings_Convert_ToUI_Current(displaySettings);

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