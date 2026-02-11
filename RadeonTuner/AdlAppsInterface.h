#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "AdlVariables.h"
#include "AdlxVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::AdlAppInterfaceList()
	{
		try
		{
			//Get combobox items
			ItemCollection itemCollection = combobox_AppSelect().Items();

			//Disable picking
			disable_picking = true;

			//Remove applications
			int collectionSize = itemCollection.Size();
			for (int i = 0; i < collectionSize; i++)
			{
				itemCollection.RemoveAt(0);
			}

			//Load applications
			adl_Apps = AdlAppLoad(L"3D_User");

			//Add apps to combobox
			itemCollection.Append(box_value(L"Global"));
			for (AdlApplication adlApp : adl_Apps)
			{
				itemCollection.Append(box_value(adlApp.FileName));
			}

			//Enable picking
			disable_picking = false;

			//Select first index
			combobox_AppSelect().SelectedIndex(0);

			//Set result
			AVDebugWriteLine("Listed ADL applications in combobox.");
			return true;
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("Failed listing ADL applications in combobox.");
			return false;
		}
	}

	bool MainPage::AdlAppInterfaceAddFile()
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
			std::wstring importPath;
			HRESULT hResult = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, (void**)&pFileDialog);
			if (SUCCEEDED(hResult))
			{
				//Set file dialog
				COMDLG_FILTERSPEC filterSpec[] = { { L"Executable files", L"*.exe" }, { L"Binary files", L"*.bin" } };
				pFileDialog->SetFileTypes(ARRAYSIZE(filterSpec), filterSpec);
				pFileDialog->SetTitle(L"Select application executable...");
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
							importPath = pszFilePath;
						}
					}
				}
			}

			//Check file path
			if (importPath.empty())
			{
				ShowNotification(L"Application not added, no path set");
				AVDebugWriteLine(L"Application not added, no path set");
				return false;
			}

			//Add application
			return AdlAppAdd(importPath, L"3D_User");
		}
		catch (...)
		{
			//Set result
			return false;
		}
	}

	bool MainPage::AdlAppInterfaceAddProcess()
	{
		try
		{
			//Get running processes
			std::vector<ProcessMulti> processSelect{};
			std::vector<std::wstring> processSelectString{};
			std::vector<ProcessMulti> processList = Get_ProcessesMultiAll();
			for (ProcessMulti processMulti : processList)
			{
				try
				{
					//Check if process is valid
					if (!processMulti.Validate())
					{
						continue;
					}

					//Get application main window handle
					HWND windowHandleMain = processMulti.WindowHandleMain();

					//Check if application has valid main window
					if (windowHandleMain == NULL)
					{
						continue;
					}

					//Add process
					std::wstring processString = string_to_wstring(processMulti.ExeName()) + L" (" + number_to_wstring(processMulti.Identifier()) + L")";
					processSelect.push_back(processMulti);
					processSelectString.push_back(processString);
				}
				catch (...) {}
			}

			//Show task dialog
			int selectedIndex = AVTaskDialog(NULL, L"RadeonTuner", L"Which process would you like to add?", L"", processSelectString);

			//Get application file path
			std::wstring importPath = string_to_wstring(processSelect[selectedIndex].ExePath());

			//Check file path
			if (importPath.empty())
			{
				ShowNotification(L"Application not added, no path set");
				AVDebugWriteLine(L"Application not added, no path set");
				return false;
			}

			//Add application
			return AdlAppAdd(importPath, L"3D_User");
		}
		catch (...)
		{
			//Set result
			return false;
		}
	}
}