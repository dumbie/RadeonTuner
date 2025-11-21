#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesExport(std::string exportPath = "")
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
			//Check file path
			std::string exportPathFinal;
			if (exportPath.empty())
			{
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
								exportPathFinal = wchar_to_string(pszFilePath);
							}
						}
					}
				}
			}
			else
			{
				exportPathFinal = exportPath;
			}

			//Check file path
			if (exportPathFinal.empty())
			{
				textblock_Status().Text(L"Tuning and fans not exported");
				AVDebugWriteLine(L"File export path is not set.");
				return;
			}

			//Fix add option to export graphics and display settings

			//Generate tuning fan settings
			TuningFanSettings tuningFanSettings = Generate_TuningFanSettings();

			//Convert tuning fan settings
			nlohmann::json jsonData = Generate_TuningFanSettings(tuningFanSettings);

			//Convert json to string
			std::string jsonString = jsonData.dump();

			//Save settings file
			string_to_file(exportPathFinal, jsonString);

			//Set result
			textblock_Status().Text(L"Tuning and fans exported");
			AVDebugWriteLine(L"Tuning and fans exported");
		}
		catch (...)
		{
			//Set result
			textblock_Status().Text(L"Tuning and fans not exported");
			AVDebugWriteLine(L"Tuning and fans export error");
		}
	}
}