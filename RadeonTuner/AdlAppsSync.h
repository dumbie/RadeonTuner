#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::AdlAppSyncAll()
	{
		try
		{
			AVDebugWriteLine("Syncing graphics profiles to user.blb: " << graphicsSettingsCache.size());

			//Get all applications
			std::vector<AdlApplication> adlApplications = AdlAppLoadAll(L"3D_User", false);

			//Remove non existing applications
			for (AdlApplication& adlApplication : adlApplications)
			{
				try
				{
					//Check if application exists
					bool exists = std::any_of(graphicsSettingsCache.begin(), graphicsSettingsCache.end(),
						[&](const GraphicsSettings& graphicsSetting)
						{
							return adlApplication.FileName == graphicsSetting.Application.value() && adlApplication.FilePath == L"*\\*";
						});

					//Remove application
					if (!exists)
					{
						AdlAppRemove(adlApplication);
						AVDebugWriteLine("Removed non existing application: " << adlApplication.FileName);
					}
				}
				catch (...) {}
			}

			//Add non existing applications
			for (GraphicsSettings& graphicsSetting : graphicsSettingsCache)
			{
				try
				{
					if (!graphicsSetting.Global())
					{
						//Check if application exists
						bool exists = std::any_of(adlApplications.begin(), adlApplications.end(),
							[&](const AdlApplication& adlApplication)
							{
								return adlApplication.FileName == graphicsSetting.Application.value() && adlApplication.FilePath == L"*\\*";
							});

						//Add application
						if (!exists)
						{
							//Create adl application
							AdlApplication adlApplication{};
							adlApplication.FileName = graphicsSetting.Application.value();
							adlApplication.FilePath = L"*\\*";
							adlApplication.DriverArea = L"3D_User";

							//Apply current settings
							AdlGraphicsSettingsApply(adl_Gpu_AdapterIndex, adl_Gpu_UniqueIdentifierHex, adlApplication, graphicsSetting, AdlSettingGet::Current);
							AVDebugWriteLine("Added non existing application: " << adlApplication.FileName);
						}
					}
				}
				catch (...) {}
			}

			//Return result
			return true;
		}
		catch (...)
		{
			//Return result
			return false;
		}
	}
}