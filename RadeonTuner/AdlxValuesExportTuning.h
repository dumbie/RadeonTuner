#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesExportTuning()
	{
		try
		{
			std::string exportPath;
			auto pFileDialog = AVFin<IFileOpenDialog*>(AVFinMethod::ReleaseInterface);
			HRESULT hResult = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_ALL, IID_IFileSaveDialog, (void**)&pFileDialog.Get());
			if (SUCCEEDED(hResult))
			{
				//Set file dialog
				COMDLG_FILTERSPEC filterSpec[] = { { L"Setting files", L"*.radt" } };
				pFileDialog.Get()->SetFileTypes(ARRAYSIZE(filterSpec), filterSpec);
				pFileDialog.Get()->SetTitle(L"Export tuning and fans settings...");
				pFileDialog.Get()->SetOptions(FOS_OVERWRITEPROMPT);
				pFileDialog.Get()->SetDefaultExtension(L"radt");

				//Show file dialog
				hResult = pFileDialog.Get()->Show(NULL);

				//Get file dialog result
				if (SUCCEEDED(hResult))
				{
					auto pShellItem = AVFin<IShellItem*>(AVFinMethod::ReleaseInterface);
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
				ShowNotification(L"Tuning and fans not exported, no path set");
				AVDebugWriteLine(L"Tuning and fans not exported, no path set");
				return;
			}

			//Generate settings
			TuningFanSettings tuningFanSettings = TuningFanSettings_Generate_FromUI(false);

			//Save settings to file
			bool saveResult = TuningFanSettings_Save(tuningFanSettings, exportPath);

			//Set result
			if (saveResult)
			{
				ShowNotification(L"Tuning and fans exported");
				AVDebugWriteLine(L"Tuning and fans exported");
			}
			else
			{
				ShowNotification(L"Tuning and fans export failed");
				AVDebugWriteLine(L"Tuning and fans export failed");
			}
		}
		catch (...)
		{
			//Set result
			ShowNotification(L"Tuning and fans not exported, exception");
			AVDebugWriteLine(L"Tuning and fans not exported, exception");
		}
	}
}