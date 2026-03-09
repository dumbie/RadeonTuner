#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::AdlAppInterfaceListLoad()
	{
		try
		{
			//Disable picking
			disable_picking = true;

			//Get combobox items
			ItemCollection itemCollection = combobox_AppSelect().Items();

			//Remove applications
			int collectionSize = itemCollection.Size();
			for (int i = 0; i < collectionSize; i++)
			{
				itemCollection.RemoveAt(0);
			}

			//Load applications
			adl_Apps = AdlAppLoad(L"3D_User");

			//Sort applications by file name
			std::sort(adl_Apps.begin(), adl_Apps.end(), [](const AdlApplication& a, const AdlApplication& b) { return a.FileName.size() < b.FileName.size(); });

			//Add apps to combobox
			for (AdlApplication adlApp : adl_Apps)
			{
				if (adlApp.FileName == L"*.*")
				{
					itemCollection.Append(box_value(L"Global"));
				}
				else
				{
					itemCollection.Append(box_value(adlApp.FileName));
				}
			}

			//Enable picking
			disable_picking = false;

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

	void MainPage::AdlAppInterfaceAddFile()
	{
		try
		{
			std::wstring importPath;
			auto pFileDialog = AVFin<IFileOpenDialog*>(AVFinMethod::Release);
			HRESULT hResult = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, (void**)&pFileDialog.Get());
			if (SUCCEEDED(hResult))
			{
				//Set file dialog
				COMDLG_FILTERSPEC filterSpec[] = { { L"Executable files", L"*.exe" }, { L"Binary files", L"*.bin" } };
				pFileDialog.Get()->SetFileTypes(ARRAYSIZE(filterSpec), filterSpec);
				pFileDialog.Get()->SetTitle(L"Select application executable...");
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
							importPath = pszFilePath;
						}
					}
				}
			}

			//Add application
			std::wstring addResult = AdlAppAdd(importPath, L"3D_User");

			//Show notification
			ShowNotification(addResult);
			AVDebugWriteLine(addResult);

			//Check result
			if (addResult == L"Application added")
			{
				//Reload applications
				AdlAppInterfaceListLoad();

				//Select application
				combobox_AppSelect().SelectedIndex(0);
			}
		}
		catch (...) {}
	}

	void MainPage::AdlAppInterfaceAddProcess()
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
			int selectedIndex = AVTaskDialog(NULL, L"RadeonTuner", L"Which process would you like to add?", L"", processSelectString, true);

			//Get application file path
			std::wstring importPath = string_to_wstring(processSelect[selectedIndex].ExePath());

			//Add application
			std::wstring addResult = AdlAppAdd(importPath, L"3D_User");

			//Show notification
			ShowNotification(addResult);
			AVDebugWriteLine(addResult);

			//Check result
			if (addResult == L"Application added")
			{
				//Reload applications
				AdlAppInterfaceListLoad();

				//Select application
				combobox_AppSelect().SelectedIndex(0);
			}
		}
		catch (...) {}
	}
}