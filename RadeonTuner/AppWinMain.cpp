#pragma once
#include "pch.h"
#include "AppVariables.h"
#include "SettingCheck.h"

void ShowProcessMainWindow(std::vector<AVProcess> processList)
{
	try
	{
		//Get current process identifier
		DWORD currentProcessId = GetCurrentProcessId();

		for (AVProcess process : processList)
		{
			try
			{
				//Fix does not work when process is running as administrator, add pipe or socket workaround?

				//Check process identifier
				if (currentProcessId == process.Identifier())
				{
					continue;
				}

				//Show process window
				Show_ProcessByWindowHandle(process.WindowHandleMain(false));
			}
			catch (...) {}
		}
	}
	catch (...) {}
}

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	try
	{
		//Enable debug logging
		//FileDelete(L"Debug.log");
		//AVDebugWriteLineLogFile = true;

		AVDebugWriteLine("Welcome to RadeonTuner.");

		//Check if process is already running
		std::vector<AVProcess> processList = Get_ProcessByName(L"RadeonTuner.exe", true);
		if (processList.size() > 1)
		{
			AVDebugWriteLine("Application is already running, exiting and showing window.");
			ShowProcessMainWindow(processList);
			return 0;
		}

		//Set instance handle
		AppVariables::hInstance = hInstance;

		//Get executable directory
		std::wstring exeDirectory = PathGetAppRoot();

		//Set working directory
		SetCurrentDirectoryW(exeDirectory.c_str());

		//Initialize settings
		std::wstring pathSettingFileW = PathMerge(exeDirectory, L"Settings\\Settings.json");
		AppVariables::Settings = AVSettingsJson(pathSettingFileW);

		//Create Profiles folder
		std::wstring pathProfilesFolderW = PathMerge(exeDirectory, L"Profiles");
		FolderCreate(pathProfilesFolderW);

		//Replace updater executable
		UpdateCleanup();

		//Check settings
		SettingCheck();

		//Load window settings
		bool setFirstLaunchBool = false;
		std::optional<bool> firstLaunchSetting = AppVariables::Settings.Load<bool>("FirstLaunch");
		if (firstLaunchSetting.has_value())
		{
			setFirstLaunchBool = firstLaunchSetting.value();
		}

		bool setStartWindowVisibleBool = false;
		std::optional<bool> startWindowVisibleSetting = AppVariables::Settings.Load<bool>("StartWindowVisible");
		if (startWindowVisibleSetting.has_value())
		{
			setStartWindowVisibleBool = startWindowVisibleSetting.value();
		}

		bool setTopMostBool = false;
		std::optional<bool> setTopMostSetting = AppVariables::Settings.Load<bool>("SetTopMost");
		if (setTopMostSetting.has_value())
		{
			setTopMostBool = setTopMostSetting.value();
		}

		//Create application window
		AVDebugWriteLine("Creating application window.");
		AppVariables::App.CreateWindowXaml(hInstance, setFirstLaunchBool || setStartWindowVisibleBool, setTopMostBool);

		//Return result
		return 0;
	}
	catch (...)
	{
		//Return result
		AVDebugWriteLine("Failed creating application window (Exception)");
		return -1;
	}
}