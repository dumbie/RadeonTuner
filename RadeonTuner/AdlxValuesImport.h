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
			std::string importPath;
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
							importPath = wchar_to_string(pszFilePath);
						}
					}
				}
			}

			//Check file path
			if (importPath.empty())
			{
				ShowNotification(L"Tuning and fans not imported, no path set");
				AVDebugWriteLine(L"Tuning and fans not imported, no path set");
				return;
			}

			//Load tuning fan settings from file
			TuningFanSettings tuningFanSettings = TuningFanSettings_Load(importPath);

			//Check device identifier
			std::string device_id_import_a = tuningFanSettings.DeviceId.value();
			std::wstring device_id_import_w = string_to_wstring(device_id_import_a);
			std::wstring device_id_current = AdlxGetDeviceIdentifier(ppGpuInfo);
			if (!device_id_import_w.empty() && !device_id_current.empty())
			{
				if (device_id_import_w != device_id_current)
				{
					int messageResult = MessageBoxW(NULL, L"Tuning and fans settings do not match current gpu, continue import?", L"RadeonTuner", MB_YESNO);
					if (messageResult == IDNO)
					{
						//Set result
						ShowNotification(L"Tuning and fans gpu does not match");
						AVDebugWriteLine(L"Tuning and fans gpu does not match");
						return;
					}
				}
			}

			//Set settings values
			TuningFanSettings_Convert_ToUI(tuningFanSettings, false);

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