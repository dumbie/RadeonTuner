#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::AmdDriverTool::implementation
{
	void MainPage::AdlxValuesImport()
	{
		//Select settings file
		wchar_t lpstrFileName[MAX_PATH];
		OPENFILENAMEW openFileName = {};
		openFileName.lStructSize = sizeof(openFileName);
		openFileName.lpstrTitle = L"Import setting file...";
		openFileName.lpstrFilter = L"Setting files (adtx)\0*.adtx\0";
		openFileName.lpstrFile = lpstrFileName;
		openFileName.nMaxFile = MAX_PATH;
		openFileName.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		if (!GetOpenFileNameW(&openFileName))
		{
			return;
		}

		//Open settings file
		std::string settings = file_to_string(wchar_to_string(lpstrFileName));

		//Parse settings file
		std::vector<std::string> stringVector = string_to_vector(settings);

		//Set settings values
		for (std::string string : stringVector)
		{
			auto stringSplit = string_split(string, '=');
			if (stringSplit[0] == "CoreMin")
			{
				slider_Core_Min().Value(string_to_int(stringSplit[1]));
			}
			else if (stringSplit[0] == "CoreMax")
			{
				slider_Core_Max().Value(string_to_int(stringSplit[1]));
			}
			else if (stringSplit[0] == "MemoryTiming")
			{
				combobox_Memory_Timing().SelectedIndex(string_to_int(stringSplit[1]));
			}
			else if (stringSplit[0] == "MemoryMax")
			{
				slider_Memory_Max().Value(string_to_int(stringSplit[1]));
			}
			else if (stringSplit[0] == "PowerLimit")
			{
				slider_Power_Limit().Value(string_to_int(stringSplit[1]));
			}
			else if (stringSplit[0] == "PowerVoltage")
			{
				slider_Power_Voltage().Value(string_to_int(stringSplit[1]));
			}
			else if (stringSplit[0] == "FanZeroRpm")
			{
				toggleswitch_Fan_Zero_Rpm().IsOn(string_to_int(stringSplit[1]));
			}
			else if (stringSplit[0] == "FanSpeed0")
			{
				slider_Fan_Speed_0().Value(string_to_int(stringSplit[1]));
			}
			else if (stringSplit[0] == "FanTemp0")
			{
				slider_Fan_Temp_0().Value(string_to_int(stringSplit[1]));
			}
			else if (stringSplit[0] == "FanSpeed1")
			{
				slider_Fan_Speed_1().Value(string_to_int(stringSplit[1]));
			}
			else if (stringSplit[0] == "FanTemp1")
			{
				slider_Fan_Temp_1().Value(string_to_int(stringSplit[1]));
			}
			else if (stringSplit[0] == "FanSpeed2")
			{
				slider_Fan_Speed_2().Value(string_to_int(stringSplit[1]));
			}
			else if (stringSplit[0] == "FanTemp2")
			{
				slider_Fan_Temp_2().Value(string_to_int(stringSplit[1]));
			}
			else if (stringSplit[0] == "FanSpeed3")
			{
				slider_Fan_Speed_3().Value(string_to_int(stringSplit[1]));
			}
			else if (stringSplit[0] == "FanTemp3")
			{
				slider_Fan_Temp_3().Value(string_to_int(stringSplit[1]));
			}
			else if (stringSplit[0] == "FanSpeed4")
			{
				slider_Fan_Speed_4().Value(string_to_int(stringSplit[1]));
			}
			else if (stringSplit[0] == "FanTemp4")
			{
				slider_Fan_Temp_4().Value(string_to_int(stringSplit[1]));
			}
		}

		//Update status
		textblock_Status().Text(L"Tuning and fans imported");
		AVDebugWriteLine(L"Tuning and fans imported");
	}
}