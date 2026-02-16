#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlxVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::AdlxValuesResetGraphics()
	{
		try
		{
			//Get selected application
			AdlApplication& adlApplication = adl_AppSelected();

			//Default application settings
			AdlAppDefaultPropertiesSet(adlApplication);

			//Set application settings
			AdlAppPropertySet(adlApplication);

			//Reload application settings
			AdlxValuesLoadSelectApp();

			//Return result
			return true;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("Failed resetting graphics settings.");
			return false;
		}
	}
}