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
			openFileName.lpstrTitle = L"Export setting file...";
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

			//Create json settings
			nlohmann::json jsonData;
			jsonData["CoreMin"] = slider_Core_Min().Value();
			jsonData["CoreMax"] = slider_Core_Max().Value();
			jsonData["MemoryTiming"] = combobox_Memory_Timing().SelectedIndex();
			jsonData["MemoryMax"] = slider_Memory_Max().Value();
			jsonData["PowerLimit"] = slider_Power_Limit().Value();
			jsonData["PowerVoltage"] = slider_Power_Voltage().Value();
			jsonData["PowerTDC"] = slider_Power_TDC().Value();
			jsonData["FanZeroRpm"] = toggleswitch_Fan_Zero_Rpm().IsOn();
			jsonData["FanSpeed0"] = slider_Fan_Speed_0().Value();
			jsonData["FanTemp0"] = slider_Fan_Temp_0().Value();
			jsonData["FanSpeed1"] = slider_Fan_Speed_1().Value();
			jsonData["FanTemp1"] = slider_Fan_Temp_1().Value();
			jsonData["FanSpeed2"] = slider_Fan_Speed_2().Value();
			jsonData["FanTemp2"] = slider_Fan_Temp_2().Value();
			jsonData["FanSpeed3"] = slider_Fan_Speed_3().Value();
			jsonData["FanTemp3"] = slider_Fan_Temp_3().Value();
			jsonData["FanSpeed4"] = slider_Fan_Speed_4().Value();
			jsonData["FanTemp4"] = slider_Fan_Temp_4().Value();

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