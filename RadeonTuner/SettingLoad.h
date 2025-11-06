#pragma once
#include "pch.h"
#include "MainPage.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::SettingLoad()
	{
		try
		{
			//Disable saving
			disable_saving_settings = true;

			std::optional<bool> SetTopMost = AppVariables::Settings.Load<bool>("SetTopMost");
			if (SetTopMost.has_value())
			{
				toggleswitch_Window_Top().IsOn(SetTopMost.value());
			}

			std::optional<bool> CloseTray = AppVariables::Settings.Load<bool>("CloseTray");
			if (CloseTray.has_value())
			{
				toggleswitch_Close_Tray().IsOn(CloseTray.value());
			}

			std::optional<bool> ActiveOverclock = AppVariables::Settings.Load<bool>("ActiveOverclock");
			if (ActiveOverclock.has_value())
			{
				bool settingValue = ActiveOverclock.value();
				toggleswitch_ActiveOverclock().IsOn(settingValue);
				if (settingValue)
				{
					SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
					button_Fan_Keep().Background(colorValid);
					button_Tuning_Keep().Background(colorValid);
				}
				else
				{
					SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
					button_Fan_Keep().Background(colorInvalid);
					button_Tuning_Keep().Background(colorInvalid);
				}
			}

			//Check startup shortcut
			bool startupShortcut = StartupShortcutCheck(L"RadeonTuner");
			toggleswitch_Launch_Startup().IsOn(startupShortcut);

			//Enable saving
			std::thread threadEnableSaving([]()
				{
					Sleep(1000);
					disable_saving_settings = false;
				});
			threadEnableSaving.detach();

			AVDebugWriteLine("Application settings loaded.");
		}
		catch (...)
		{
			AVDebugWriteLine("Failed loading application settings.");
		}
	}
}