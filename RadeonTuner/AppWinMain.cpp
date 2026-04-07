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
		//Check if process is already running
		std::vector<AVProcess> processList = Get_ProcessByName("RadeonTuner.exe", true);
		if (processList.size() > 1)
		{
			AVDebugWriteLine("Application is already running, exiting and showing window.");
			ShowProcessMainWindow(processList);
			return 0;
		}

		//Set instance handle
		AppVariables::hInstance = hInstance;

		//Initialize settings
		std::wstring pathSettingFileW = PathMerge(PathGetExecutableDirectory(), L"Settings.json");
		std::string pathSettingFileA = wstring_to_string(pathSettingFileW);
		AppVariables::Settings = AVSettingsJson(pathSettingFileA);

		//Create Active folder
		std::wstring pathActiveFolderW = PathMerge(PathGetExecutableDirectory(), L"Active");
		FolderCreate(pathActiveFolderW);

		//Replace updater executable
		ReplaceUpdater();

		//Check settings
		SettingCheck();

		//Load window settings
		bool StartWindowVisibleBool = false;
		std::optional<bool> StartWindowVisibleSetting = AppVariables::Settings.Load<bool>("StartWindowVisible");
		if (StartWindowVisibleSetting.has_value())
		{
			StartWindowVisibleBool = StartWindowVisibleSetting.value();
		}

		bool SetTopMostBool = false;
		std::optional<bool> SetTopMostSetting = AppVariables::Settings.Load<bool>("SetTopMost");
		if (SetTopMostSetting.has_value())
		{
			SetTopMostBool = SetTopMostSetting.value();
		}

		//Create application window
		AppVariables::App.CreateWindowXaml(hInstance, StartWindowVisibleBool, SetTopMostBool);

		//Return result
		return 0;
	}
	catch (...)
	{
		//Return result
		return -1;
	}
}