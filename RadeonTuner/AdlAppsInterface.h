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
			adlAppsCache = AdlAppsLoad(L"3D_User");

			//Sort applications by file name
			std::sort(adlAppsCache.begin(), adlAppsCache.end(), [](const AdlApplication& a, const AdlApplication& b) { return a.FileName.size() < b.FileName.size(); });

			//Add apps to combobox
			for (AdlApplication adlApp : adlAppsCache)
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
			//Show file dialog
			std::wstring importPath = filepicker_open(L"Select application executable...", { { L"Executable files", L"*.exe" }, { L"Binary files", L"*.bin" } });

			//Check file path
			if (importPath.empty())
			{
				ShowNotification(L"Application not added, no path set");
				AVDebugWriteLine(L"Application not added, no path set");
				return;
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
			std::vector<AVProcess> processSelect{};
			std::vector<std::wstring> processSelectString{};
			std::vector<AVProcess> processList = Get_ProcessAll();
			for (AVProcess process : processList)
			{
				try
				{
					//Check if process is valid
					if (!process.Validate())
					{
						continue;
					}

					//Get application main window handle
					HWND windowHandleMain = process.WindowHandleMain();

					//Check if application has valid main window
					if (windowHandleMain == NULL)
					{
						continue;
					}

					//Add process
					std::wstring processString = string_to_wstring(process.ExeName()) + L" (" + number_to_wstring(process.Identifier()) + L")";
					processSelect.push_back(process);
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