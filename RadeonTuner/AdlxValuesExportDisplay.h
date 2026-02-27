#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesExportDisplay()
	{
		try
		{
			std::string exportPath;
			auto pFileDialog = AVFin<IFileOpenDialog*>(AVFinMethod::Release);
			HRESULT hResult = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_ALL, IID_IFileSaveDialog, (void**)&pFileDialog.Get());
			if (SUCCEEDED(hResult))
			{
				//Set file dialog
				COMDLG_FILTERSPEC filterSpec[] = { { L"Setting files", L"*.radd" } };
				pFileDialog.Get()->SetFileTypes(ARRAYSIZE(filterSpec), filterSpec);
				pFileDialog.Get()->SetTitle(L"Export display settings...");
				pFileDialog.Get()->SetOptions(FOS_OVERWRITEPROMPT);
				pFileDialog.Get()->SetDefaultExtension(L"radd");

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
							exportPath = wchar_to_string(pszFilePath);
						}
					}
				}
			}

			//Check file path
			if (exportPath.empty())
			{
				ShowNotification(L"Display not exported, no path set");
				AVDebugWriteLine(L"Display not exported, no path set");
				return;
			}

			//Generate settings
			DisplaySettings displaySettings = DisplaySettings_Generate_FromUI();

			//Save settings to file
			bool saveResult = DisplaySettings_Save(displaySettings, exportPath);

			//Set result
			if (saveResult)
			{
				ShowNotification(L"Display exported");
				AVDebugWriteLine(L"Display exported");
			}
			else
			{
				ShowNotification(L"Display export failed");
				AVDebugWriteLine(L"Display export failed");
			}
		}
		catch (...)
		{
			//Set result
			ShowNotification(L"Display not exported, exception");
			AVDebugWriteLine(L"Display not exported, exception");
		}
	}
}