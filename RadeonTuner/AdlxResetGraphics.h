#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::AdlxValuesResetGraphics()
	{
		try
		{
			//Default application settings
			if (AdlAppDefaultProperties(AdlAppSelectedGet().value(), true, false))
			{
				//Reload application settings
				AdlxValuesLoadSelectApp();

				//Return result
				return true;
			}
			else
			{
				//Return result
				return false;
			}
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("Failed resetting graphics settings.");
			return false;
		}
	}
}