#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesExport()
	{
		try
		{
			//Select settings file
			wchar_t lpstrFileName[MAX_PATH] = {};
			OPENFILENAMEW openFileName = {};
			openFileName.lStructSize = sizeof(openFileName);
			openFileName.lpstrTitle = L"Export tuning and fans settings...";
			openFileName.lpstrFilter = L"Setting files (radt)\0*.radt\0";
			openFileName.lpstrDefExt = L"radt";
			openFileName.lpstrFile = lpstrFileName;
			openFileName.nMaxFile = MAX_PATH;
			openFileName.Flags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
			if (!GetSaveFileNameW(&openFileName))
			{
				return;
			}

			//Fix add option to export graphics and display settings

			//Generate tuning fan settings
			TuningFanSettings tuningFanSettings = GenerateStruct_TuningFanSettings();

			//Create json settings
			nlohmann::json jsonData{};
			jsonData["DeviceId"] = tuningFanSettings.DeviceId;
			jsonData["CoreMin"] = tuningFanSettings.CoreMin;
			jsonData["CoreMax"] = tuningFanSettings.CoreMax;
			jsonData["MemoryTiming"] = tuningFanSettings.MemoryTiming;
			jsonData["MemoryMax"] = tuningFanSettings.MemoryMax;
			jsonData["PowerLimit"] = tuningFanSettings.PowerLimit;
			jsonData["PowerVoltage"] = tuningFanSettings.PowerVoltage;
			jsonData["PowerTDC"] = tuningFanSettings.PowerTDC;
			jsonData["FanZeroRpm"] = tuningFanSettings.FanZeroRpm;
			jsonData["FanSpeed0"] = tuningFanSettings.FanSpeed0;
			jsonData["FanTemp0"] = tuningFanSettings.FanTemp0;
			jsonData["FanSpeed1"] = tuningFanSettings.FanSpeed1;
			jsonData["FanTemp1"] = tuningFanSettings.FanTemp1;
			jsonData["FanSpeed2"] = tuningFanSettings.FanSpeed2;
			jsonData["FanTemp2"] = tuningFanSettings.FanTemp2;
			jsonData["FanSpeed3"] = tuningFanSettings.FanSpeed3;
			jsonData["FanTemp3"] = tuningFanSettings.FanTemp3;
			jsonData["FanSpeed4"] = tuningFanSettings.FanSpeed4;
			jsonData["FanTemp4"] = tuningFanSettings.FanTemp4;

			//Convert json to string
			std::string jsonString = jsonData.dump();

			//Save settings file
			string_to_file(wchar_to_string(lpstrFileName), jsonString);

			//Set result
			textblock_Status().Text(L"Tuning and fans exported");
			AVDebugWriteLine(L"Tuning and fans exported");
		}
		catch (...)
		{
			//Set result
			textblock_Status().Text(L"Tuning and fans not exported");
			AVDebugWriteLine(L"Tuning and fans not exported");
		}
	}
}