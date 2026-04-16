#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesImportTuning()
	{
		try
		{
			//Show file dialog
			std::wstring importPath = filepicker_open(L"Import tuning and fans settings...", { { L"Setting files", L"*.radt" } });

			//Check file path
			if (importPath.empty())
			{
				ShowNotification(L"Tuning and fans not imported, no path set");
				AVDebugWriteLine(L"Tuning and fans not imported, no path set");
				return;
			}

			AVDebugWriteLine("Importing tuning and fans settings: " << importPath.c_str());

			//Load settings from file
			std::string importPathA = wstring_to_string(importPath);
			TuningFanSettings tuningFanSettings = TuningFanSettings_Profile_LoadFromFile(importPathA).value();

			//Check device identifier
			std::string device_id_import_a = tuningFanSettings.DeviceId.value();
			std::wstring device_id_import_w = string_to_wstring(device_id_import_a);
			std::wstring device_id_current_w = AdlxGetGpuIdentifier(ppGpuInfo);
			if (!device_id_import_w.empty() && !device_id_current_w.empty())
			{
				if (device_id_import_w != device_id_current_w)
				{
					std::wstring messageResult = AVTaskDialogStr(NULL, L"RadeonTuner", L"Tuning and fans settings do not match current gpu, continue import?", L"", { L"Yes", L"No" }, false);
					if (messageResult == L"No")
					{
						//Set result
						ShowNotification(L"Tuning and fans gpu does not match");
						AVDebugWriteLine(L"Tuning and fans gpu does not match");
						return;
					}
				}
			}

			//Set settings values to interface
			TuningFanSettings_Profile_Convert_ToUI(tuningFanSettings);

			//Set result
			ShowNotification(L"Tuning and fans imported");
			AVDebugWriteLine(L"Tuning and fans imported");
		}
		catch (...)
		{
			//Set result
			ShowNotification(L"Tuning and fans not imported, exception");
			AVDebugWriteLine(L"Tuning and fans not imported, exception");
		}
	}
}