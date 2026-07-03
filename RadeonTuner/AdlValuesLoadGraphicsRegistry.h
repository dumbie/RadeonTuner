#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlValuesLoadGraphicsRegistry()
	{
		try
		{
			//Get current and default settings
			GraphicsSettings graphicsSettings = GraphicsSettings_Generate_FromADLRegistry(adl_Gpu_AdapterIndex).value();

			//Convert settings values to interface
			GraphicsSettings_ADL_Convert_ToUI(graphicsSettings);

			//Set result
			AVDebugWriteLine("ADL graphics registry values loaded.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADL failed loading graphics registry values.");
		}
	}
}