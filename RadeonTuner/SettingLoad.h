#pragma once
#include "pch.h"
#include "MainPage.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::SettingLoad()
	{
		try
		{
			std::optional<bool> SetTopMost = AppVariables::Settings.Load<bool>("SetTopMost");
			if (SetTopMost.has_value())
			{
				toggleswitch_Window_Top().IsOn(SetTopMost.value());
			}

			std::optional<bool> ActiveOverclock = AppVariables::Settings.Load<bool>("ActiveOverclock");
			if (ActiveOverclock.has_value())
			{
				toggleswitch_ActiveOverclock().IsOn(ActiveOverclock.value());
			}

			AVDebugWriteLine("Application settings loaded.");
		}
		catch (...)
		{
			AVDebugWriteLine("Failed loading application settings.");
		}
	}
}