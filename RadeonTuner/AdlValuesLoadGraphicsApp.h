#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlValuesLoadGraphicsApp()
	{
		try
		{
			//Get selected application
			auto selectedApp = AdlAppSelectedGet();

			//Check selected application
			if (!selectedApp.has_value())
			{
				AVDebugWriteLine("ADL application is not selected.");
				return;
			}

			//Get current and default settings
			GraphicsSettings graphicsSettings = GraphicsSettings_Generate_FromADLApp(selectedApp.value()).value();

			//Convert settings values to interface
			GraphicsSettings_ADL_Convert_ToUI(graphicsSettings);

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