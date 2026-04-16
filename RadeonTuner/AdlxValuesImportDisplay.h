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

			//Check device identifier
			std::string device_id_import_a = displaySettings.DeviceId.value();
			std::wstring device_id_import_w = string_to_wstring(device_id_import_a);
			std::wstring device_id_current_w = AdlxGetDisplayIdentifier(ppDisplayInfo);
			if (!device_id_import_w.empty() && !device_id_current_w.empty())
			{
				if (device_id_import_w != device_id_current_w)
				{
					std::wstring messageResult = AVTaskDialogStr(NULL, L"RadeonTuner", L"Display settings do not match current display, continue import?", L"", { L"Yes", L"No" }, false);
					if (messageResult == L"No")
					{
						//Set result
						ShowNotification(L"Display does not match");
						AVDebugWriteLine(L"Display does not match");
						return;
					}
				}
			}

			//Set settings values
			DisplaySettings_Convert_ToUI(displaySettings);

			//Set result
			ShowNotification(L"Display imported");
			AVDebugWriteLine(L"Display imported");
		}
		catch (...)
		{
			//Set result
			ShowNotification(L"Display not imported, exception");
			AVDebugWriteLine(L"Display not imported, exception");
		}
	}
}