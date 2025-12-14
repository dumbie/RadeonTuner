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
			//Application profiles location
			//%WINDIR%\System32\atiapfxx.blb
			//%LOCALAPPDATA%\AMD\CN\gmdb.blb
			//%LOCALAPPDATA%\AMD\CN\GExDb.blb
			//%LOCALAPPDATA%\ATI\ACE\APL\User.blb
			//Computer\HKEY_CURRENT_USER\Software\AMD\CN
			//Computer\HKEY_LOCAL_MACHINE\Software\AMD\CN

			//Get application profiles from ADL
			//Fix find way to list all apps not just apps with PXDynamic
			//To allow FSR4 you need to set FSROVR to FsrOvrWhitelistProfile (FsrOvr_WListed = 1 / FsrOverride = 1)
			//To allow Frame Generation you need to set FRAMEGEN to FrameGenWhitelistProfile (WListed = 1 / AFMF3 = 1)
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