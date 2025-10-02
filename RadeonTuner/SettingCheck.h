#pragma once
#include "pch.h"
#include "MainPage.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::SettingCheck()
	{
		try
		{
			if (!AppVariables::Settings.Check("MenuIndex"))
			{
				AppVariables::Settings.Set("MenuIndex", 0);
			}

			if (!AppVariables::Settings.Check("SetTopMost"))
			{
				AppVariables::Settings.Set("SetTopMost", false);
			}

			if (!AppVariables::Settings.Check("ActiveOverclock"))
			{
				AppVariables::Settings.Set("ActiveOverclock", false);
			}

			if (!AppVariables::Settings.Check("ActiveOverclockFile"))
			{
				AppVariables::Settings.Set("ActiveOverclockFile", "...");
			}

			AVDebugWriteLine("Application settings checked.");
		}
		catch (...)
		{
			AVDebugWriteLine("Failed checking application settings.");
		}
	}
}