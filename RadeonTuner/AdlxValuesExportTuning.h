#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesExportTuning()
	{
		try
		{
			//Show file dialog
			std::wstring exportPath = filepicker_save(L"Export tuning and fans settings...", { { L"Setting files", L"*.radt"} });

			//Check file path
			if (exportPath.empty())
			{
				ShowNotification(L"Tuning and fans not exported, no path set");
				AVDebugWriteLine(L"Tuning and fans not exported, no path set");
				return;
			}

			//Generate settings
			TuningFanSettings tuningFanSettings = TuningFanSettings_Generate_FromUI(false).value();

			//Save settings to file
			std::string exportPathA = wstring_to_string(exportPath);
			bool saveResult = TuningFanSettings_Profile_SaveToFile(tuningFanSettings, exportPathA);

			//Set result
			if (saveResult)
			{
				ShowNotification(L"Tuning and fans exported");
				AVDebugWriteLine(L"Tuning and fans exported");
			}
			else
			{
				ShowNotification(L"Tuning and fans export failed");
				AVDebugWriteLine(L"Tuning and fans export failed");
			}
		}
		catch (...)
		{
			//Set result
			ShowNotification(L"Tuning and fans not exported, exception");
			AVDebugWriteLine(L"Tuning and fans not exported, exception");
		}
	}
}