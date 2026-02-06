#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "AdlVariables.h"

namespace winrt::RadeonTuner::implementation
{
	AdlAppProperty MainPage::AdlPropertyGet(AdlApplication adlApp, std::wstring propertyName)
	{
		AdlAppProperty returnProperty{};
		try
		{
			for (AdlAppProperty adlAppProperty : adlApp.Properties)
			{
				try
				{
					if (adlAppProperty.Name == propertyName)
					{
						return adlAppProperty;
					}
				}
				catch (...) {}
			}
		}
		catch (...) {}
		return returnProperty;
	}

	bool MainPage::AdlPropertySet(AdlApplication& adlApp, std::wstring propertyName, std::wstring propertyValue, std::wstring propertyGpuId)
	{
		try
		{
			//Status variables
			bool propertyExists = false;
			bool propertyUpdated = false;
			bool propertyUseGpuId = false;

			//Update property value if it exists
			for (AdlAppProperty& adlAppProperty : adlApp.Properties)
			{
				try
				{
					if (adlAppProperty.Name == propertyName)
					{
						propertyExists = true;
						for (AdlAppPropertyValue& adlAppPropertyValue : adlAppProperty.Values)
						{
							try
							{
								if (adlAppProperty.UseGpuId())
								{
									propertyUseGpuId = true;
									if (adlAppPropertyValue.GpuId == propertyGpuId)
									{
										adlAppPropertyValue.Value = propertyValue;
										propertyUpdated = true;
										AVDebugWriteLine(L"Updated value: " << adlAppProperty.Type << L" / " << propertyName << L" / " << propertyValue << L" / " << propertyGpuId);
									}
								}
								else
								{
									adlAppPropertyValue.Value = propertyValue;
									propertyUpdated = true;
									AVDebugWriteLine(L"Updated value: " << adlAppProperty.Type << L" / " << propertyName << L" / " << propertyValue);
								}
							}
							catch (...) {}
						}
					}
				}
				catch (...) {}
			}

			//Add property value if it does not exist
			if (propertyExists && propertyUseGpuId && !propertyUpdated)
			{
				for (AdlAppProperty& adlAppProperty : adlApp.Properties)
				{
					try
					{
						if (adlAppProperty.Name == propertyName)
						{
							AdlAppPropertyValue adlAppPropertyValue{};
							adlAppPropertyValue.GpuId = propertyGpuId;
							adlAppPropertyValue.Value = propertyValue;
							adlAppProperty.Values.insert(adlAppProperty.Values.begin(), adlAppPropertyValue);

							propertyUpdated = true;
							AVDebugWriteLine(L"Added value: " << adlAppProperty.Type << L" / " << propertyName << L" / " << propertyValue << L" / " << propertyGpuId);
						}
					}
					catch (...) {}
				}
			}

			//Add property if it does not exist
			if (!propertyExists && !propertyUpdated)
			{
				AdlAppProperty adlAppProperty{};
				adlAppProperty.Type = AdlPropertyGetType(propertyName, adlApp.DriverArea);
				adlAppProperty.Name = propertyName;
				adlAppProperty.DriverArea = adlApp.DriverArea;

				AdlAppPropertyValue adlAppPropertyValue{};
				if (adlAppProperty.UseGpuId())
				{
					adlAppPropertyValue.GpuId = propertyGpuId;
				}
				adlAppPropertyValue.Value = propertyValue;
				adlAppProperty.Values.push_back(adlAppPropertyValue);

				adlApp.Properties.push_back(adlAppProperty);
				AVDebugWriteLine("Added property: " << adlAppProperty.Type << L" / " << propertyName << L" / " << propertyValue << L" / " << propertyGpuId);
			}

			//Get record properties
			std::vector<ADLPropertyRecordCreate> recordCreate = adlApp.GetRecordCreate();

			//Generate profile name
			std::wstring profileName = AdlProfileGenerateName();

			//Remove application and assigned profile
			adl_Res0 = _ADL2_ApplicationProfiles_RemoveApplication(adl_Context, adlApp.FileName.c_str(), adlApp.FilePath.c_str(), adlApp.Version.c_str(), adlApp.DriverArea.c_str());
			AVDebugWriteLine("Removed application profile: " << adl_Res0);

			//Create application profile
			adl_Res0 = _ADL2_ApplicationProfiles_Profile_Create(adl_Context, adlApp.DriverArea.c_str(), profileName.c_str(), recordCreate.size(), recordCreate.data());
			AVDebugWriteLine("Created application profile: " << adl_Res0);

			//Assign application profile
			adl_Res0 = _ADL2_ApplicationProfiles_ProfileApplicationX2_Assign(adl_Context, adlApp.FileName.c_str(), adlApp.FilePath.c_str(), adlApp.Version.c_str(), adlApp.AppTitle.c_str(), adlApp.DriverArea.c_str(), profileName.c_str());
			AVDebugWriteLine("Assigned application profile: " << adl_Res0);

			//Set result
			return adl_Res0 == ADL_OK;
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("Failed setting application property (Exception)");
			return false;
		}
	}
}