#pragma once
#include "pch.h"
#include "MainPage.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::toggleswitch_Shortcut_Startup_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving_settings) { return; }

			//Create or delete startup shortcut
			StartupShortcutManage(L"RadeonTuner", false, StartupShortcutType::Startup);
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_Shortcut_StartMenu_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving_settings) { return; }

			//Create or delete start menu shortcut
			StartupShortcutManage(L"RadeonTuner", false, StartupShortcutType::StartMenu);
		}
		catch (...) {}
	}

	void MainPage::toggleswitch_Shortcut_ContextMenu_Toggled(IInspectable const& sender, RoutedEventArgs const& e)
	{
		try
		{
			//Check if saving is disabled
			if (disable_saving_settings) { return; }

			//Create or delete context menu shortcut
			bool contextShortcut = RegistryCheck(HKEY_CLASSES_ROOT, L"Directory\\background\\shell\\RadeonTuner");
			if (contextShortcut)
			{
				//Delete shortcut from registry
				RegistryDelete(HKEY_CLASSES_ROOT, L"Directory\\background\\shell\\RadeonTuner");
			}
			else
			{
				//Set shortcut details
				std::wstring targetFilePath = PathGetExecutableFile();

				//Create shortcut in registry
				RegistrySet(HKEY_CLASSES_ROOT, L"Directory\\background\\shell\\RadeonTuner", L"", L"Open RadeonTuner");
				RegistrySet(HKEY_CLASSES_ROOT, L"Directory\\background\\shell\\RadeonTuner", L"Icon", targetFilePath);
				RegistrySet(HKEY_CLASSES_ROOT, L"Directory\\background\\shell\\RadeonTuner\\command", L"", targetFilePath);
			}
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
				AVDebugWriteLine(L"Set window on top");
			}
			else
			{
				AppVariables::Settings.Set("SetTopMost", false);
				AppVariables::App.SetTopMost(false);
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