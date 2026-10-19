#pragma once
#include "pch.h"
#include "MainPage.h"

namespace winrt::RadeonTuner::implementation
{
	winrt::IAsyncAction MainPage::SettingLoad()
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

			std::optional<bool> StartCheckUpdate = AppVariables::Settings.Load<bool>("StartCheckUpdate");
			if (StartCheckUpdate.has_value())
			{
				toggleswitch_StartCheckUpdate().IsOn(StartCheckUpdate.value());
			}

			std::optional<bool> ShowExperimental = AppVariables::Settings.Load<bool>("ShowExperimental");
			if (ShowExperimental.has_value())
			{
				toggleswitch_ShowExperimental().IsOn(ShowExperimental.value());
			}

			std::optional<bool> SkipSupportCheckGraphics = AppVariables::Settings.Load<bool>("SkipSupportCheckGraphics");
			if (SkipSupportCheckGraphics.has_value())
			{
				toggleswitch_SkipSupportCheckGraphics().IsOn(SkipSupportCheckGraphics.value());
			}

			//Theme settings
			std::optional<int> ThemeStyle = AppVariables::Settings.Load<int>("ThemeStyle");
			if (ThemeStyle.has_value())
			{
				combobox_ThemeStyle().SelectedIndex(ThemeStyle.value());
			}

			std::optional<bool> ThemeIconMono = AppVariables::Settings.Load<bool>("ThemeIconMono");
			if (ThemeIconMono.has_value())
			{
				toggleswitch_ThemeIconMono().IsOn(ThemeIconMono.value());
			}

			//Check startup shortcut
			bool startupShortcut = StartupShortcutCheck(L"RadeonTuner", StartupShortcutType::Startup);
			toggleswitch_Shortcut_Startup().IsOn(startupShortcut);

			//Check start menu shortcut
			bool startMenuShortcut = StartupShortcutCheck(L"RadeonTuner", StartupShortcutType::StartMenu);
			toggleswitch_Shortcut_StartMenu().IsOn(startMenuShortcut);

			//Check context menu shortcut
			bool contextShortcut = RegistryCheck(HKEY_ENUM::CLASSES_ROOT, L"Directory\\background\\shell\\RadeonTuner");
			toggleswitch_Shortcut_ContextMenu().IsOn(contextShortcut);

			//Check Windows update driver exclude setting
			std::optional<DWORD> updateExcludeDrivers = RegistryGetDword(HKEY_ENUM::LOCAL_MACHINE, L"Software\\Policies\\Microsoft\\Windows\\WindowsUpdate", L"ExcludeWUDriversInQualityUpdate");
			if (updateExcludeDrivers.has_value())
			{
				toggleswitch_UpdateExcludeDrivers().IsOn(updateExcludeDrivers.value() >= 1);
			}

			//Fix validate shortcut paths if directory moved

			//Enable saving
			co_await AsyncTaskDelay(100, AppVariables::App.GetDispatcher());
			disable_saving_settings = false;

			AVDebugWriteLine("Application settings loaded.");
		}
		catch (...)
		{
			AVDebugWriteLine("Failed loading application settings.");
		}
	}
}