#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesExportGraphics()
	{
		try
		{
			std::string exportPath;
			auto pFileDialog = AVFin<IFileOpenDialog*>(AVFinMethod::ReleaseInterface);
			HRESULT hResult = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_ALL, IID_IFileSaveDialog, (void**)&pFileDialog.Get());
			if (SUCCEEDED(hResult))
			{
				//Set file dialog
				COMDLG_FILTERSPEC filterSpec[] = { { L"Setting files", L"*.radg"} };
				pFileDialog.Get()->SetFileTypes(ARRAYSIZE(filterSpec), filterSpec);
				pFileDialog.Get()->SetTitle(L"Export graphics settings...");
				pFileDialog.Get()->SetOptions(FOS_OVERWRITEPROMPT);
				pFileDialog.Get()->SetDefaultExtension(L"radg");

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
				ShowNotification(L"Graphics not exported, no path set");
				AVDebugWriteLine(L"Graphics not exported, no path set");
				return;
			}

			//Save settings to file
			bool saveResult = GraphicsSettings_Save(adl_AppSelected(), exportPath);

			//Set result
			if (saveResult)
			{
				ShowNotification(L"Graphics exported " + adl_AppSelected().FileName);
				AVDebugWriteLine(L"Graphics exported " << adl_AppSelected().FileName);
			}
			else
			{
				ShowNotification(L"Graphics export failed " + adl_AppSelected().FileName);
				AVDebugWriteLine(L"Graphics export failed " << adl_AppSelected().FileName);
			}
		}
		catch (...)
		{
			//Set result
			ShowNotification(L"Graphics export failed, exception");
			AVDebugWriteLine(L"Graphics export failed, exception");
		}
	}
}