#pragma once
#include "pch.h"

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