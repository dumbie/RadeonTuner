#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesExportGraphics()
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
				COMDLG_FILTERSPEC filterSpec[] = { { L"Setting files (radg)", L"*.radg"} };
				pFileDialog->SetFileTypes(ARRAYSIZE(filterSpec), filterSpec);
				pFileDialog->SetTitle(L"Export graphics settings...");
				pFileDialog->SetOptions(FOS_OVERWRITEPROMPT);
				pFileDialog->SetDefaultExtension(L"radg");

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
				ShowNotification(L"Graphics not exported, no path set");
				AVDebugWriteLine(L"Graphics not exported, no path set");
				return;
			}

			//Generate settings
			GraphicsSettings graphicsSettings = GraphicsSettings_Generate_FromUI();

			//Save settings to file
			bool saveResult = GraphicsSettings_Save(graphicsSettings, exportPath);

			//Set result
			if (saveResult)
			{
				ShowNotification(L"Graphics exported");
				AVDebugWriteLine(L"Graphics exported");
			}
			else
			{
				ShowNotification(L"Graphics export failed");
				AVDebugWriteLine(L"Graphics export failed");
			}
		}
		catch (...)
		{
			//Set result
			ShowNotification(L"Graphics not exported, exception");
			AVDebugWriteLine(L"Graphics not exported, exception");
		}
	}
}