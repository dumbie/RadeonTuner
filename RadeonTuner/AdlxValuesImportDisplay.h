#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesImportDisplay()
	{
		try
		{
			std::string importPath;
			auto pFileDialog = AVFin<IFileOpenDialog*>(AVFinMethod::Release);
			HRESULT hResult = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, (void**)&pFileDialog.Get());
			if (SUCCEEDED(hResult))
			{
				//Set file dialog
				COMDLG_FILTERSPEC filterSpec[] = { { L"Setting files", L"*.radd" } };
				pFileDialog.Get()->SetFileTypes(ARRAYSIZE(filterSpec), filterSpec);
				pFileDialog.Get()->SetTitle(L"Import display settings...");
				pFileDialog.Get()->SetOptions(FOS_PATHMUSTEXIST | FOS_FILEMUSTEXIST);

				//Show file dialog
				hResult = pFileDialog.Get()->Show(NULL);

				//Get file dialog result
				if (SUCCEEDED(hResult))
				{
					auto pShellItem = AVFin<IShellItem*>(AVFinMethod::Release);
					hResult = pFileDialog.Get()->GetResult(&pShellItem.Get());
					if (SUCCEEDED(hResult))
					{
						PWSTR pszFilePath;
						hResult = pShellItem.Get()->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
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
					std::wstring messageResult = AVTaskDialogStr(NULL, L"RadeonTuner", L"Display settings do not match current display, continue import?", L"", { L"Yes", L"No" }, false);
					if (messageResult == L"No")
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