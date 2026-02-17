#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::AdlAppRemove(AdlApplication adlApp)
	{
		try
		{
			//Check for global application
			if (adlApp.FileName == L"*.*")
			{
				AVDebugWriteLine("Cannot remove Global application.");
				return false;
			}

			AVDebugWriteLine("Removing profile from application: " << adlApp.FileName << " / " << adlApp.FilePath << " / " << adlApp.DriverArea);
			//Fix unassign all profiles without removing them

			//Remove profile from application
			adl_Res0 = _ADL2_ApplicationProfiles_RemoveApplication(adl_Context, adlApp.FileName.c_str(), adlApp.FilePath.c_str(), NULL, adlApp.DriverArea.c_str());
			AVDebugWriteLine("Removed application profile: " << adl_Res0);

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