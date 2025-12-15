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
				combobox_TextureFilteringQuality().IsEnabled(false);
				toggleswitch_SurfaceFormatOptimization().IsEnabled(false);
				toggleswitch_OpenGLTripleBuffering().IsEnabled(false);
				toggleswitch_OpenGL10Bit().IsEnabled(false);
				toggleswitch_HagsSupport().IsEnabled(false);
				toggleswitch_Shortcut_ContextMenu().IsEnabled(false);
				toggleswitch_FsrOverrideUpscaling().IsEnabled(false);
				toggleswitch_FsrOverrideFrameGen().IsEnabled(false);
			}
			else
			{
				//Fix hide administrator shield icons
			}

			AVDebugWriteLine("Application admin settings checked.");
		}
		catch (...)
		{
			AVDebugWriteLine("Failed checking admin settings.");
		}
	}
}