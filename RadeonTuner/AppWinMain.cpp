#pragma once
#include "pch.h"
#include "AppVariables.h"
#include "SettingCheck.h"

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
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

	//Create application window
	std::optional<bool> StartWindowVisible = AppVariables::Settings.Load<bool>("StartWindowVisible");
	if (StartWindowVisible.has_value())
	{
		bool settingValue = StartWindowVisible.value();
		AppVariables::App.CreateWindowXaml(hInstance, settingValue);
	}

	//Return result
	return 0;
}