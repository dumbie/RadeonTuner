#pragma once
#include "pch.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::AdlCheckDriverOnlySoftware()
	{
		try
		{
			//Fix change to registry based solution?

			//Check if Radeon Software process is running
			std::vector<AVProcess> processList = Get_ProcessByName("RadeonSoftware.exe", true);
			if (processList.size() > 0)
			{
				AVDebugWriteLine("Radeon Software is running, software type is minimal or default.");
				return true;
			}
			else
			{
				AVDebugWriteLine("Radeon Software is not running, software type is driver only.");
				return false;
			}
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("Failed to check driver only software (Exception)");
			return false;
		}
	}
}