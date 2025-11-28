#pragma once
#include "pch.h"
#include "MainPage.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::toggleswitch_Launch_Startup_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving_settings) { return; }

			//Create or delete startup shortcut
			StartupShortcutManage(L"RadeonTuner", false);
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_StartWindowVisible_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving_settings) { return; }

			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			if (senderElement.IsOn())
			{
				AppVariables::Settings.Set("StartWindowVisible", true);
			}
			else
			{
				AppVariables::Settings.Set("StartWindowVisible", false);
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_Window_Top_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving_settings) { return; }

			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			if (senderElement.IsOn())
			{
				AppVariables::Settings.Set("SetTopMost", true);
				AppVariables::App.SetTopMost(true);
				textblock_Status().Text(L"Set window on top");
				AVDebugWriteLine(L"Set window on top");
			}
			else
			{
				AppVariables::Settings.Set("SetTopMost", false);
				AppVariables::App.SetTopMost(false);
				textblock_Status().Text(L"Set window not on top");
				AVDebugWriteLine(L"Set window not on top");
			}
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_Close_Tray_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving_settings) { return; }

			ToggleSwitch senderElement = sender.as<ToggleSwitch>();
			if (senderElement.IsOn())
			{
				AppVariables::Settings.Set("CloseTray", true);
			}
			else
			{
				AppVariables::Settings.Set("CloseTray", false);
			}
		}
		catch (...) {}
	}
}