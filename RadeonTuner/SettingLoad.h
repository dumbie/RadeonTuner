#pragma once
#include "pch.h"
#include "MainPage.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::SettingLoad()
	{
		try
		{
			std::optional<bool> setTopMost = AppVariables::Settings.Load<bool>("SetTopMost");
			if (setTopMost.has_value())
			{
				toggleswitch_Window_Top().IsOn(setTopMost.value());
			}

			AVDebugWriteLine("Application settings loaded.");
		}
		catch (...)
		{
			AVDebugWriteLine("Failed loading application settings.");
		}
	}
}