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
			//Get selected application
			auto selectedApp = AdlAppSelectedGet().value();

			//Check application type
			if (selectedApp.get().Global)
			{
				//Reset registry settings
				if (AdlGraphicsResetRegistry())
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
			else
			{
				//Reset application settings
				if (AdlGraphicsResetApp(selectedApp, true, false))
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
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("Failed resetting graphics settings.");
			return false;
		}
	}
}