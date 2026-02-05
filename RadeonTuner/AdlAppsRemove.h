#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "AdlVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::AdlAppsRemove(AdlApplication adlApp)
	{
		try
		{
			AVDebugWriteLine("Removing application and profile: " << adlApp.FileName << " / " << adlApp.FilePath << " / " << adlApp.ProfileName);

			//Remove application and assigned profile
			adl_Res0 = _ADL2_ApplicationProfiles_RemoveApplication(adl_Context, adlApp.FileName.c_str(), adlApp.FilePath.c_str(), adlApp.Version.c_str(), adlApp.DriverArea.c_str());
			AVDebugWriteLine("Removed application profile: " << adl_Res0);
			//-17 profile not found

			//Set result
			return adl_Res0 == ADL_OK;
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("Failed removing application (Exception)");
			return false;
		}
	}
}