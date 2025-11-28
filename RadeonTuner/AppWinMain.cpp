#pragma once
#include "pch.h"
#include "AppVariables.h"
#include "SettingCheck.h"

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	try
	{
		//Check if process is already running
		std::vector<ProcessMulti> processList = Get_ProcessesMultiByName("RadeonTuner.exe");
		if (processList.size() > 1)
		{
			AVDebugWriteLine("Application is already running, exiting.");
			return 0;
		}

		//Set instance handle
		AppVariables::hInstance = hInstance;

		//Initialize settings
		std::wstring pathSettingFileW = PathMerge(PathGetExecutableDirectory(), L"Settings.json");
		std::string pathSettingFileA = wstring_to_string(pathSettingFileW);
		AppVariables::Settings = AVSettingsJson(pathSettingFileA);

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