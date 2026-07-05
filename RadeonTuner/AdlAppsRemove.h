#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	std::wstring MainPage::AdlAppRemove(AdlApplication adlApp)
	{
		try
		{
			AVDebugWriteLine("Removing profiles from application: " << adlApp.FileName << " / " << adlApp.FilePath);

			//Get profile customisations
			auto adlCustomizations = AVFinObj(AVFinObjMethod::Custom, CUSTOMISATIONS{});
			adlCustomizations.SetReleaser([&](auto releaseObject)
				{
					ADL_MemoryFree_Customizations(&releaseObject);
				});
			adl_Res0 = _ADL2_ApplicationProfiles_GetCustomization(adl_Context, ADL_AP_DATABASE__USER, &adlCustomizations.Get());
			if (adl_Res0 != ADL_OK)
			{
				return L"Failed removing application (Customization)";
			}

			//Get customisations area names
			std::vector<std::wstring> areaNames{};
			AREA* headArea = adlCustomizations.Get().HeadArea;
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
			if (removeCount > 0)
			{
				return L"Application removed";
			}
			else
			{
				return L"Application not removed";
			}
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("Failed removing application (Exception)");
			return L"Failed removing application (Exception)";
		}
	}
}