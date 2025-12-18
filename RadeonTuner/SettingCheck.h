#pragma once
#include "pch.h"

void ReplaceUpdater()
{
	try
	{
		AVDebugWriteLine(L"Checking application updater.");

		////Close running application updater
		//if (Close_ProcessesByName("Updater.exe", true))
		//{
		//	await Task.Delay(1000);
		//}

		//Move new updater executable file
		FileMove(L"Updater/UpdaterReplace.exe", L"Updater.exe", true);
	}
	catch (...) {}
}

void SettingCheck()
{
	try
	{
		if (!AppVariables::Settings.Check("MenuIndex"))
		{
			AppVariables::Settings.Set("MenuIndex", 0);
		}

		if (!AppVariables::Settings.Check("StartWindowVisible"))
		{
			AppVariables::Settings.Set("StartWindowVisible", true);
		}

		if (!AppVariables::Settings.Check("SetTopMost"))
		{
			AppVariables::Settings.Set("SetTopMost", false);
		}

		if (!AppVariables::Settings.Check("CloseTray"))
		{
			AppVariables::Settings.Set("CloseTray", false);
		}

		AVDebugWriteLine("Application settings checked.");
	}
	catch (...)
	{
		AVDebugWriteLine("Failed checking application settings.");
	}
}