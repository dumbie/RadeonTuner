#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::AmdDriverTool::implementation
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
			openFileName.lpstrFilter = L"Setting files (adtx)\0*.adtx\0";
			openFileName.lpstrDefExt = L"adtx";
			openFileName.lpstrFile = lpstrFileName;
			openFileName.nMaxFile = MAX_PATH;
			openFileName.Flags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
			if (!GetSaveFileNameW(&openFileName))
			{
				return;
			}

			//Fix add option to export graphics and display settings

			//Create export string
			std::vector<std::string> stringVector =
			{
				"CoreMin=" + number_to_string((int)slider_Core_Min().Value()),
				"CoreMax=" + number_to_string((int)slider_Core_Max().Value()),
				"MemoryTiming=" + number_to_string(combobox_Memory_Timing().SelectedIndex()),
				"MemoryMax=" + number_to_string((int)slider_Memory_Max().Value()),
				"PowerLimit=" + number_to_string((int)slider_Power_Limit().Value()),
				"PowerVoltage=" + number_to_string((int)slider_Power_Voltage().Value()),
				"FanZeroRpm=" + number_to_string(toggleswitch_Fan_Zero_Rpm().IsOn()),
				"FanSpeed0=" + hstring_to_string(textbox_Fan_Speed_0().Text()),
				"FanTemp0=" + hstring_to_string(textbox_Fan_Temp_0().Text()),
				"FanSpeed1=" + hstring_to_string(textbox_Fan_Speed_1().Text()),
				"FanTemp1=" + hstring_to_string(textbox_Fan_Temp_1().Text()),
				"FanSpeed2=" + hstring_to_string(textbox_Fan_Speed_2().Text()),
				"FanTemp2=" + hstring_to_string(textbox_Fan_Temp_2().Text()),
				"FanSpeed3=" + hstring_to_string(textbox_Fan_Speed_3().Text()),
				"FanTemp3=" + hstring_to_string(textbox_Fan_Temp_3().Text()),
				"FanSpeed4=" + hstring_to_string(textbox_Fan_Speed_4().Text()),
				"FanTemp4=" + hstring_to_string(textbox_Fan_Temp_4().Text())
			};

			//Save export string
			string_to_file(wchar_to_string(lpstrFileName), vector_to_string(stringVector, "\n"));

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