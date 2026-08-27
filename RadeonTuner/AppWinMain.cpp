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

void CheckFileAttributes()
{
	try
	{
		//Get path to local application data
		std::wstring pathLocalAppData = PathGetFolderKnown(FOLDERID_LocalAppData);

		//Check setting files
		FileAdjustAttributes(PathMerge(AppVariables::SaveDataPath, L"Settings\\Settings.json"), true, FILE_ATTRIBUTE_READONLY);

		//Check profile files
		FileAdjustAttributes(PathMerge(AppVariables::SaveDataPath, L"Profiles\\DisplayProfiles.json"), true, FILE_ATTRIBUTE_READONLY);
		FileAdjustAttributes(PathMerge(AppVariables::SaveDataPath, L"Profiles\\GraphicsProfiles.json"), true, FILE_ATTRIBUTE_READONLY);
		FileAdjustAttributes(PathMerge(AppVariables::SaveDataPath, L"Profiles\\MultimediaProfiles.json"), true, FILE_ATTRIBUTE_READONLY);
		FileAdjustAttributes(PathMerge(AppVariables::SaveDataPath, L"Profiles\\TuningProfiles.json"), true, FILE_ATTRIBUTE_READONLY);

		//Check user.blb file
		FileAdjustAttributes(PathMerge(pathLocalAppData, L"ATI\\ACE\\APL\\User.blb"), true, FILE_ATTRIBUTE_READONLY);
	}
	catch (...) {}
}

int CALLBACK wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ int nCmdShow)
{
	try
	{
		//Convert command line to string
		std::wstring commandLineString = pCmdLine;

		//Get application root path
		std::wstring applicationRootPath = PathGetAppRoot();

		//Set working directory to application root
		SetCurrentDirectoryW(applicationRootPath.c_str());

		//Check folder write permission
		if (!FolderWritePermission(L""))
		{
			AVDebugWriteLine("No write permission in working directory.");

			//Get path to local application data
			std::wstring pathLocalAppData = PathGetFolderKnown(FOLDERID_LocalAppData);
			std::wstring pathDataFolder = PathMerge(pathLocalAppData, L"RadeonTuner");

			//Set data path to local application data
			AppVariables::SaveDataPath = pathDataFolder;

			//Create RadeonTuner folder
			FolderCreate(AppVariables::SaveDataPath);
		}
		else
		{
			//Set data path to application root
			AppVariables::SaveDataPath = applicationRootPath;
		}

		//Check file attributes
		CheckFileAttributes();

		//Enable debug logging
		if (wstring_contains(commandLineString, L"-debug"))
		{
			std::wstring debugLogPath = PathMerge(AppVariables::SaveDataPath, L"Debug.log");
			FileDelete(debugLogPath);
			AVDebugWriteLineLogFileEnabled = true;
			AVDebugWriteLineLogFilePath = debugLogPath;
		}

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

		//Create default folders
		FolderCreate(PathMerge(AppVariables::SaveDataPath, L"Profiles"));
		FolderCreate(PathMerge(AppVariables::SaveDataPath, L"Settings"));

		//Initialize settings
		AppVariables::Settings = AVSettingsJson(PathMerge(AppVariables::SaveDataPath, L"Settings\\Settings.json"));

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