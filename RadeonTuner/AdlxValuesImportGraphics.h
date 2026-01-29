#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

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
				COMDLG_FILTERSPEC filterSpec[] = { { L"Setting files (radg)", L"*.radg"} };
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
			GraphicsSettings graphicsSettings = GraphicsSettings_Load(importPath);

			//Check device identifier
			std::string app_id_import_a = graphicsSettings.AppId.value();
			std::string app_id_current_a = hstring_to_string(combobox_AppSelect().SelectedValue().as<hstring>());
			if (!app_id_import_a.empty() && !app_id_current_a.empty())
			{
				if (app_id_import_a != app_id_current_a)
				{
					int messageResult = MessageBoxW(NULL, L"Graphics settings do not match current application, continue import?", L"RadeonTuner", MB_YESNO);
					if (messageResult == IDNO)
					{
						//Set result
						ShowNotification(L"Application does not match");
						AVDebugWriteLine(L"Application does not match");
						return;
					}
				}
			}

			//Set settings values
			GraphicsSettings_Convert_ToUI(graphicsSettings);

			//Set result
			ShowNotification(L"Graphics imported");
			AVDebugWriteLine(L"Graphics imported");
		}
		catch (...)
		{
			//Set result
			ShowNotification(L"Graphics not imported, exception");
			AVDebugWriteLine(L"Graphics not imported, exception");
		}
	}
}