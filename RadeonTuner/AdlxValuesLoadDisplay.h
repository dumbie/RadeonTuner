#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesLoadDisplay()
	{
		try
		{
			//Get current and default settings
			displaySettingsCurrent = DisplaySettings_Generate_FromADL(adl_Display_AdapterIndex, adl_Display_DisplayIndex).value();

			//Convert settings values to interface
			DisplaySettings_Convert_ToUI_Adl(displaySettingsCurrent);

			//Set result
			AVDebugWriteLine("ADLX loaded display values.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADLX failed loading display values.");
		}
	}
}