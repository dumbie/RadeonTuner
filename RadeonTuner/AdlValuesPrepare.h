#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlValuesPrepare()
	{
		try
		{
			//Get application profiles from ADL
			//Fix find way to list all apps not just apps with PXDynamic
			//To allow FSR4 you need to set FSROVR to FsrOvrWhitelistProfile
			//To allow Frame Generation you need to set FRAMEGEN to FrameGenWhitelistProfile
			int numApps = 0;
			ADLApplicationRecord* adlApplications = NULL;
			std::wstring driverArea = L"PXDynamic";
			if (_ADL2_ApplicationProfiles_Applications_Get(_ADL2_Context, driverArea.c_str(), &numApps, &adlApplications) != ADL_OK)
			{
				AVDebugWriteLine("Failed getting ADL application profiles.");
			}
			else
			{
				//List all applications
				auto itemCollection = combobox_AppSelect().Items();
				for (int i = 0; i < numApps; i++)
				{
					std::wstring appTitle = adlApplications[i].strTitle;
					itemCollection.Append(box_value(appTitle));
				}

				AVDebugWriteLine("Listed ADL application profiles: " << itemCollection.Size());
			}

			//Set result
			AVDebugWriteLine("ADL prepared.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADL preparation failed.");
		}
	}
}