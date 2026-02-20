#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesImportGraphics()
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
				COMDLG_FILTERSPEC filterSpec[] = { { L"Setting files", L"*.radg" } };
				pFileDialog->SetFileTypes(ARRAYSIZE(filterSpec), filterSpec);
				pFileDialog->SetTitle(L"Import graphics settings...");
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
				ShowNotification(L"Graphics not imported, no path set");
				AVDebugWriteLine(L"Graphics not imported, no path set");
				return;
			}

			//Load settings from file
			AdlApplication adlApplication = GraphicsSettings_Load(importPath);

			//Set application settings
			AdlAppPropertySet(adlApplication);

			//Reload applications
			AdlAppInterfaceListLoad();

			//Select application
			combobox_AppSelect().SelectedIndex(0);

			//Set result
			ShowNotification(L"Graphics imported " + adlApplication.FileName);
			AVDebugWriteLine(L"Graphics imported " << adlApplication.FileName);
		}
		catch (...)
		{
			//Set result
			ShowNotification(L"Graphics import failed, exception");
			AVDebugWriteLine(L"Graphics import failed, exception");
		}
	}
}