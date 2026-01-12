#pragma once
#include "pch.h"
#include "MainPage.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::SettingAdmin()
	{
		try
		{
			//Check if process has admin access
			bool adminAccess = IsProcessAdmin();
			if (!adminAccess)
			{
				//Disable registry based settings that require admin
				toggleswitch_Shortcut_ContextMenu().IsEnabled(false);
			}
			else
			{
				//Hide admin shield icons for registry based settings
				toggleswitch_Shortcut_ContextMenu_AdminShield().Visibility(Visibility::Collapsed);
			}

			AVDebugWriteLine("Application admin settings checked.");
		}
		catch (...)
		{
			AVDebugWriteLine("Failed checking admin settings.");
		}
	}
}