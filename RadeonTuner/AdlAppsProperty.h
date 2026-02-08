#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "AdlVariables.h"

namespace winrt::RadeonTuner::implementation
{
	AdlAppProperty MainPage::AdlAppPropertyGet(AdlApplication adlApp, std::wstring propertyName)
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

	bool MainPage::AdlAppPropertySet(AdlApplication& adlApp, std::wstring propertyGpuId, std::wstring propertyName, std::wstring propertyValue)
	{
		try
		{
			std::vector<AdlAppPropertyValue> adlAppPropertyValues{};
			AdlAppPropertyValue adlAppPropertyValue{};
			adlAppPropertyValue.GpuId = propertyGpuId;
			adlAppPropertyValue.Name = propertyName;
			adlAppPropertyValue.Value = propertyValue;
			adlAppPropertyValues.push_back(adlAppPropertyValue);
			return AdlAppPropertySet(adlApp, adlAppPropertyValues);
		}
		catch (...)
		{
			return false;
		}
	}

	bool MainPage::AdlAppPropertySet(AdlApplication& adlApp, std::vector<AdlAppPropertyValue> properties)
	{
		try
		{
			//Check property types
			for (AdlAppPropertyValue property : properties)
			{
				try
				{
					AdlAppPropertyType propertyType = AdlAppPropertyTypeGet(property.Name, adlApp.DriverArea);
					if (propertyType == AdlAppPropertyType::ADL_APP_PROPERTY_TYPE_UNKNOWN)
					{
						AVDebugWriteLine(L"Unknown application property type: " << property.Name);
						return false;
					}
				}
				catch (...) {}
			}

			//Set properties values
			for (AdlAppPropertyValue property : properties)
			{
				try
				{
					//Status variables
					bool propertyExists = false;
					bool propertyUpdated = false;

					//Update property value if it exists
					for (AdlAppProperty& adlAppProperty : adlApp.Properties)
					{
						try
						{
							if (adlAppProperty.Name == property.Name)
							{
								propertyExists = true;
								for (AdlAppPropertyValue& adlAppPropertyValue : adlAppProperty.Values)
								{
									try
									{
										if (adlAppProperty.UseGpuId())
										{
											if (adlAppPropertyValue.GpuId == property.GpuId)
											{
												adlAppPropertyValue.Value = property.Value;
												propertyUpdated = true;
												AVDebugWriteLine(L"Updated value: " << adlAppProperty.Type << L" / " << property.Name << L" / " << property.Value << L" / " << property.GpuId);
											}
										}
										else
										{
											adlAppPropertyValue.Value = property.Value;
											propertyUpdated = true;
											AVDebugWriteLine(L"Updated value: " << adlAppProperty.Type << L" / " << property.Name << L" / " << property.Value);
										}
									}
									catch (...) {}
								}
							}
						}
						catch (...) {}
					}

					//Add property value if it does not exist
					if (propertyExists && !propertyUpdated)
					{
						for (AdlAppProperty& adlAppProperty : adlApp.Properties)
						{
							try
							{
								if (adlAppProperty.Name == property.Name)
								{
									AdlAppPropertyValue adlAppPropertyValue{};
									if (adlAppProperty.UseGpuId())
									{
										adlAppPropertyValue.GpuId = property.GpuId;
									}
									adlAppPropertyValue.Value = property.Value;
									adlAppProperty.Values.insert(adlAppProperty.Values.begin(), adlAppPropertyValue);

									propertyUpdated = true;
									AVDebugWriteLine(L"Added value: " << adlAppProperty.Type << L" / " << property.Name << L" / " << property.Value << L" / " << property.GpuId);
								}
							}
							catch (...) {}
						}
					}

					//Add property if it does not exist
					if (!propertyExists && !propertyUpdated)
					{
						AdlAppProperty adlAppProperty{};
						adlAppProperty.Type = AdlAppPropertyTypeGet(property.Name, adlApp.DriverArea);
						adlAppProperty.Name = property.Name;
						adlAppProperty.DriverArea = adlApp.DriverArea;

						AdlAppPropertyValue adlAppPropertyValue{};
						if (adlAppProperty.UseGpuId())
						{
							adlAppPropertyValue.GpuId = property.GpuId;
						}
						adlAppPropertyValue.Value = property.Value;
						adlAppProperty.Values.insert(adlAppProperty.Values.begin(), adlAppPropertyValue);

						adlApp.Properties.push_back(adlAppProperty);

						propertyUpdated = true;
						AVDebugWriteLine("Added property: " << adlAppProperty.Type << L" / " << property.Name << L" / " << property.Value << L" / " << property.GpuId);
					}
				}
				catch (...) {}
			}

			//Get record properties
			std::vector<ADLPropertyRecordCreate> recordCreate = AdlAppPropertyRecordCreateGet(adlApp);

			//Generate profile name
			std::wstring profileName = AdlAppProfileGenerateName();

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