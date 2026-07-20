#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlAppInterfaceAddFile()
	{
		try
		{
			//Show file dialog
			std::wstring importPath = filepicker_open(NULL, L"Select application executable...", { { L"Executable files", L"*.exe" }, { L"Binary files", L"*.bin" } });

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
				AdlxValuesLoadApplicationList(true);
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
				AdlxValuesLoadApplicationList(true);
			}
		}
		catch (...) {}
	}
}