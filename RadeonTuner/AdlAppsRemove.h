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

			AVDebugWriteLine("Removing profiles from application: " << adlApp.FileName << " / " << adlApp.FilePath);

			//Get profile customisations
			CUSTOMISATIONS customisations{};
			_ADL2_ApplicationProfiles_GetCustomization(adl_Context, ADL_AP_DATABASE__USER, &customisations);

			//Get customisations area names
			std::vector<std::wstring> areaNames{};
			AREA* headArea = customisations.HeadArea;
			while (headArea)
			{
				try
				{
					//Add area name to array
					areaNames.push_back(headArea->DriverComponent->NameOfDriver);

					//Move to next area
					headArea = headArea->NextArea;
				}
				catch (...) {}
			}

			//Remove profiles from application
			int removeCount = 0;
			for (std::wstring areaName : areaNames)
			{
				try
				{
					adl_Res0 = _ADL2_ApplicationProfiles_RemoveApplication(adl_Context, adlApp.FileName.c_str(), adlApp.FilePath.c_str(), NULL, areaName.c_str());
					if (adl_Res0 == ADL_OK) { removeCount++; }
					AVDebugWriteLine("Removed application profile: " << areaName << " / " << adl_Res0);
				}
				catch (...) {}
			}

			//Set result
			return removeCount > 0;
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("Failed removing application (Exception)");
			return false;
		}
	}
}