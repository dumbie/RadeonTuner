#pragma once
#include "pch.h"
#include "AppVariables.h"

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	//Fix check if process is already running

	//Set instance handle
	AppVariables::hInstance = hInstance;

	//Initialize settings
	std::wstring pathSettingFileW = PathMerge(PathGetExecutableDirectory(), L"Settings.json");
	std::string pathSettingFileA = wstring_to_string(pathSettingFileW);
	AppVariables::Settings = AVSettingsJson(pathSettingFileA);

	//Create application window
	AppVariables::App.CreateWindowXaml(hInstance);

	//Return result
	return 0;
}