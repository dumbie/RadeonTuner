#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesExport()
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
				COMDLG_FILTERSPEC filterSpec[] = { { L"Setting files (radt)", L"*.radt"} };
				pFileDialog->SetFileTypes(ARRAYSIZE(filterSpec), filterSpec);
				pFileDialog->SetTitle(L"Export tuning and fans settings...");
				pFileDialog->SetOptions(FOS_OVERWRITEPROMPT);
				pFileDialog->SetDefaultExtension(L"radt");

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
				textblock_Status().Text(L"Tuning and fans not exported");
				AVDebugWriteLine(L"File export path is not set.");
				return;
			}

			//Fix add option to export graphics and display settings

			//Generate tuning fan settings
			TuningFanSettings tuningFanSettings = TuningFanSettings_Generate_FromUI(false);

			//Save tuning fan settings to file
			bool saveResult = TuningFanSettings_Save(tuningFanSettings, exportPath);

			//Set result
			if (saveResult)
			{
				textblock_Status().Text(L"Tuning and fans exported");
				AVDebugWriteLine(L"Tuning and fans exported");
			}
			else
			{
				textblock_Status().Text(L"Tuning and fans export failed");
				AVDebugWriteLine(L"Tuning and fans export failed");
			}
		}
		catch (...)
		{
			//Set result
			textblock_Status().Text(L"Tuning and fans not exported");
			AVDebugWriteLine(L"Tuning and fans export error");
		}
	}
}