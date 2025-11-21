#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesImport()
	{
		IFileOpenDialog* pFileDialog = NULL;
		IShellItem* pShellItem = NULL;
		AVFinallySafe(
			{
				pFileDialog->Release();
				pShellItem->Release();
			});
		try
		{
			std::string filePathFinal;
			HRESULT hResult = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, (void**)&pFileDialog);
			if (SUCCEEDED(hResult))
			{
				//Set file dialog
				COMDLG_FILTERSPEC filterSpec[] = { { L"Setting files (radt)", L"*.radt"} };
				pFileDialog->SetFileTypes(ARRAYSIZE(filterSpec), filterSpec);
				pFileDialog->SetTitle(L"Import tuning and fans settings...");
				pFileDialog->SetOptions(FOS_PATHMUSTEXIST | FOS_FILEMUSTEXIST);

				//Show file dialog
				hResult = pFileDialog->Show(NULL);

				//Get file dialog result
				if (SUCCEEDED(hResult))
				{
					hResult = pFileDialog->GetResult(&pShellItem);
					if (SUCCEEDED(hResult))
					{
						PWSTR pszFilePath;
						hResult = pShellItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
						if (SUCCEEDED(hResult))
						{
							filePathFinal = wchar_to_string(pszFilePath);
						}
					}
				}
			}

			//Check file path
			if (filePathFinal.empty())
			{
				textblock_Status().Text(L"Tuning and fans not imported");
				AVDebugWriteLine(L"File import path is not set.");
				return;
			}

			//Open settings file
			std::string settings = file_to_string(filePathFinal);

			//Parse settings file
			nlohmann::json jsonData = nlohmann::json::parse(settings);

			//Check device identifier
			if (jsonData.contains("DeviceId"))
			{
				std::string device_id_importa = jsonData["DeviceId"].get<std::string>();
				std::wstring device_id_importw = string_to_wstring(device_id_importa);
				std::wstring device_id_current = AdlxGetDeviceIdentifier(ppGpuInfo);
				if (!device_id_importw.empty() && !device_id_current.empty())
				{
					if (device_id_importw != device_id_current)
					{
						int messageResult = MessageBoxW(NULL, L"Tuning and fans settings do not match current device, continue import?", L"RadeonTuner", MB_YESNO);
						if (messageResult == IDNO)
						{
							//Set result
							textblock_Status().Text(L"Tuning and fans no match");
							AVDebugWriteLine(L"Tuning and fans no match");
							return;
						}
					}
				}
			}

			//Set settings values
			if (jsonData.contains("CoreMin"))
			{
				slider_Core_Min().Value(jsonData["CoreMin"]);
			}
			if (jsonData.contains("CoreMax"))
			{
				slider_Core_Max().Value(jsonData["CoreMax"]);
			}
			if (jsonData.contains("MemoryMax"))
			{
				slider_Memory_Max().Value(jsonData["MemoryMax"]);
			}
			if (jsonData.contains("MemoryTiming"))
			{
				combobox_Memory_Timing().SelectedIndex(jsonData["MemoryTiming"]);
			}
			if (jsonData.contains("PowerLimit"))
			{
				slider_Power_Limit().Value(jsonData["PowerLimit"]);
			}
			if (jsonData.contains("PowerVoltage"))
			{
				slider_Power_Voltage().Value(jsonData["PowerVoltage"]);
			}
			if (jsonData.contains("PowerTDC"))
			{
				slider_Power_TDC().Value(jsonData["PowerTDC"]);
			}
			if (jsonData.contains("FanZeroRpm"))
			{
				toggleswitch_Fan_Zero_Rpm().IsOn(jsonData["FanZeroRpm"]);
			}
			if (jsonData.contains("FanSpeed0"))
			{
				slider_Fan_Speed_0().Value(jsonData["FanSpeed0"]);
			}
			if (jsonData.contains("FanTemp0"))
			{
				slider_Fan_Temp_0().Value(jsonData["FanTemp0"]);
			}
			if (jsonData.contains("FanSpeed1"))
			{
				slider_Fan_Speed_1().Value(jsonData["FanSpeed1"]);
			}
			if (jsonData.contains("FanTemp1"))
			{
				slider_Fan_Temp_1().Value(jsonData["FanTemp1"]);
			}
			if (jsonData.contains("FanSpeed2"))
			{
				slider_Fan_Speed_2().Value(jsonData["FanSpeed2"]);
			}
			if (jsonData.contains("FanTemp2"))
			{
				slider_Fan_Temp_2().Value(jsonData["FanTemp2"]);
			}
			if (jsonData.contains("FanSpeed3"))
			{
				slider_Fan_Speed_3().Value(jsonData["FanSpeed3"]);
			}
			if (jsonData.contains("FanTemp3"))
			{
				slider_Fan_Temp_3().Value(jsonData["FanTemp3"]);
			}
			if (jsonData.contains("FanSpeed4"))
			{
				slider_Fan_Speed_4().Value(jsonData["FanSpeed4"]);
			}
			if (jsonData.contains("FanTemp4"))
			{
				slider_Fan_Temp_4().Value(jsonData["FanTemp4"]);
			}

			//Set result
			textblock_Status().Text(L"Tuning and fans imported");
			AVDebugWriteLine(L"Tuning and fans imported");
		}
		catch (...)
		{
			//Set result
			textblock_Status().Text(L"Tuning and fans not imported");
			AVDebugWriteLine(L"Tuning and fans import error");
		}
	}
}