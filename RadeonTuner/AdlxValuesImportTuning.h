#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	winrt::fire_and_forget MainPage::AdlxValuesImportTuning()
	{
		try
		{
			//Show file dialog
			std::wstring importPath = filepicker_open(NULL, L"Import tuning and fans settings...", { { L"Setting files", L"*.radt" } });

			//Check file path
			if (importPath.empty())
			{
				ShowNotification(L"Tuning and fans not imported, no path set");
				AVDebugWriteLine(L"Tuning and fans not imported, no path set");
				co_return;
			}

			AVDebugWriteLine("Importing tuning and fans settings: " << importPath.c_str());

			//Load settings from file
			TuningFanSettings tuningFanSettings = TuningFanSettings_Profile_LoadFromFile(importPath).value();

			//Check device identifier
			std::wstring device_id_import_w = tuningFanSettings.DeviceId.value();
			std::wstring device_id_current_w = AdlxGetGpuIdentifier(adl_Gpu_AdapterIndex);
			if (!device_id_import_w.empty() && !device_id_current_w.empty())
			{
				if (device_id_import_w != device_id_current_w)
				{
					//Show messagebox
					int messageResult = co_await ShowMessageBox(L"GPU does not match", L"Tuning and fans settings do not match your selected GPU, continue import?", { L"Yes", L"No" });

					//Check messagebox result
					if (messageResult == 1)
					{
						//Set result
						ShowNotification(L"GPU does not match");
						AVDebugWriteLine(L"GPU does not match");
						co_return;
					}
				}
			}

			//Set settings values to interface
			TuningFanSettings_Convert_ToUI_Current(tuningFanSettings);

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