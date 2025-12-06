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

			std::optional<bool> StartWindowVisible = AppVariables::Settings.Load<bool>("StartWindowVisible");
			if (StartWindowVisible.has_value())
			{
				toggleswitch_StartWindowVisible().IsOn(StartWindowVisible.value());
			}

			//Check startup shortcut
			bool startupShortcut = StartupShortcutCheck(L"RadeonTuner", StartupShortcutType::Startup);
			toggleswitch_Shortcut_Startup().IsOn(startupShortcut);

			//Check start menu shortcut
			bool startMenuShortcut = StartupShortcutCheck(L"RadeonTuner", StartupShortcutType::StartMenu);
			toggleswitch_Shortcut_StartMenu().IsOn(startMenuShortcut);

			//Check context menu shortcut
			bool contextShortcut = RegistryCheck(HKEY_CLASSES_ROOT, L"Directory\\background\\shell\\RadeonTuner");
			toggleswitch_Shortcut_ContextMenu().IsOn(contextShortcut);

			//Fix validate shortcut paths if directory moved

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