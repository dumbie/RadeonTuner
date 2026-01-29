#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesImportDisplay()
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
				COMDLG_FILTERSPEC filterSpec[] = { { L"Setting files (radd)", L"*.radd"} };
				pFileDialog->SetFileTypes(ARRAYSIZE(filterSpec), filterSpec);
				pFileDialog->SetTitle(L"Import display settings...");
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
				ShowNotification(L"Display not imported, no path set");
				AVDebugWriteLine(L"Display not imported, no path set");
				return;
			}

			//Load settings from file
			DisplaySettings displaySettings = DisplaySettings_Load(importPath);

			//Check device identifier
			std::string device_id_import_a = displaySettings.DeviceId.value();
			std::wstring device_id_import_w = string_to_wstring(device_id_import_a);
			std::wstring device_id_current_w = AdlxGetDisplayIdentifier(ppDisplayInfo);
			if (!device_id_import_w.empty() && !device_id_current_w.empty())
			{
				if (device_id_import_w != device_id_current_w)
				{
					int messageResult = MessageBoxW(NULL, L"Display settings do not match current display, continue import?", L"RadeonTuner", MB_YESNO);
					if (messageResult == IDNO)
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