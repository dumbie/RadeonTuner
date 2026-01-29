#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesExportDisplay()
	{
		IFileSaveDialog* pFileDialog = NULL;
		IShellItem* pShellItem = NULL;
		AVFinallySafe(
			{
				pFileDialog->Release();
				pShellItem->Release();
			});
		try
		{
			std::string exportPath;
			HRESULT hResult = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_ALL, IID_IFileSaveDialog, (void**)&pFileDialog);
			if (SUCCEEDED(hResult))
			{
				//Set file dialog
				COMDLG_FILTERSPEC filterSpec[] = { { L"Setting files (radd)", L"*.radd"} };
				pFileDialog->SetFileTypes(ARRAYSIZE(filterSpec), filterSpec);
				pFileDialog->SetTitle(L"Export display settings...");
				pFileDialog->SetOptions(FOS_OVERWRITEPROMPT);
				pFileDialog->SetDefaultExtension(L"radd");

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