#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesImportGraphics()
	{
		try
		{
			std::string importPath;
			auto pFileDialog = AVFin<IFileOpenDialog*>(AVFinMethod::Release);
			HRESULT hResult = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, (void**)&pFileDialog.Get());
			if (SUCCEEDED(hResult))
			{
				//Set file dialog
				COMDLG_FILTERSPEC filterSpec[] = { { L"Setting files", L"*.radg" } };
				pFileDialog.Get()->SetFileTypes(ARRAYSIZE(filterSpec), filterSpec);
				pFileDialog.Get()->SetTitle(L"Import graphics settings...");
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
				ShowNotification(L"Graphics not imported, no path set");
				AVDebugWriteLine(L"Graphics not imported, no path set");
				return;
			}

			AVDebugWriteLine("Importing graphics settings: " << importPath.c_str());

			//Load settings from file
			AdlApplication adlApplication = GraphicsSettings_Load(importPath);

			//Check if application already exists
			if (AdlAppExists(adlApplication.FileName, adlApplication.FilePath, adlApplication.DriverArea))
			{
				std::wstring messageResult = AVTaskDialogStr(NULL, L"RadeonTuner", L"Application already exists and settings will be overwritten, continue import?", L"", { L"Yes", L"No" }, false);
				if (messageResult == L"No")
				{
					//Set result
					ShowNotification(L"Application already exists");
					AVDebugWriteLine(L"Application already exists");
					return;
				}
			}

			//Save application settings
			AdlAppPropertySave(adlApplication);

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