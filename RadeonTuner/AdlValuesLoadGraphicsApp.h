#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlValuesLoadGraphicsApp(AdlApplication& appInfo)
	{
		try
		{
			//Get current and default settings
			graphicsSettingsCurrent = GraphicsSettings_Generate_FromADLApp(appInfo).value();

			//Convert settings values to interface
			GraphicsSettings_Convert_ToUI_ADL(graphicsSettingsCurrent);

			//Set result
			AVDebugWriteLine("ADL graphics app values loaded.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADL failed loading graphics app values.");
		}
	}
}