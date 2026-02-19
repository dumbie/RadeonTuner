#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	std::optional<AdlAppProperty> MainPage::AdlAppPropertyGet(AdlApplication adlApp, std::wstring propertyName)
	{
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
		return std::nullopt;
	}

	bool MainPage::AdlAppPropertySet(AdlApplication& adlApp)
	{
		try
		{
			//Get record properties
			std::vector<ADLPropertyRecordCreate> recordCreate = AdlAppPropertyRecordCreateGet(adlApp.Properties);

			//Generate profile name
			if (adlApp.ProfileName.empty())
			{
				adlApp.ProfileName = AdlAppProfileGenerateName(L"RADT");
			}

			//Remove profile from application
			adl_Res0 = _ADL2_ApplicationProfiles_RemoveApplication(adl_Context, adlApp.FileName.c_str(), adlApp.FilePath.c_str(), NULL, adlApp.DriverArea.c_str());
			AVDebugWriteLine("Removed application profile: " << adl_Res0);
			//-1 profile not found or invalid
			//-17 profile not found

			//Create application profile
			adl_Res0 = _ADL2_ApplicationProfiles_Profile_Create(adl_Context, adlApp.DriverArea.c_str(), adlApp.ProfileName.c_str(), recordCreate.size(), recordCreate.data());
			AVDebugWriteLine("Created application profile: " << adl_Res0);
			//-3 invalid profile, atleast 1 property needed
			//-16 invalid properties
			//-18 already exists

			//Assign application profile
			adl_Res0 = _ADL2_ApplicationProfiles_ProfileApplicationX2_Assign(adl_Context, adlApp.FileName.c_str(), adlApp.FilePath.c_str(), NULL, NULL, adlApp.DriverArea.c_str(), adlApp.ProfileName.c_str());
			AVDebugWriteLine("Assigned application profile: " << adl_Res0);
			//-15 profile not found or invalid or already assigned

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

	bool MainPage::AdlAppPropertyUpdate(AdlApplication& adlApp, std::wstring propertyGpuId, std::wstring propertyName, std::wstring propertyValue)
	{
		try
		{
			std::vector<AdlAppPropertyValue> adlAppPropertyValues{};
			AdlAppPropertyValue adlAppPropertyValue{};
			adlAppPropertyValue.GpuId = propertyGpuId;
			adlAppPropertyValue.Name = propertyName;
			adlAppPropertyValue.Value = propertyValue;
			adlAppPropertyValues.push_back(adlAppPropertyValue);
			return AdlAppPropertyUpdate(adlApp, adlAppPropertyValues);
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("Failed updating application property (Exception)");
			return false;
		}
	}

	bool MainPage::AdlAppPropertyUpdate(AdlApplication& adlApp, std::vector<AdlAppPropertyValue> properties)
	{
		try
		{
			//Check property types
			for (AdlAppPropertyValue property : properties)
			{
				try
				{
					DATATYPES propertyType = AdlAppPropertyDataTypeGet(property.Name, adlApp.DriverArea);
					if (propertyType == DT_Unknown)
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
										if (!property.GpuId.empty())
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
									if (!property.GpuId.empty())
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
						adlAppProperty.Type = AdlAppPropertyDataTypeGet(property.Name, adlApp.DriverArea);
						adlAppProperty.Name = property.Name;

						AdlAppPropertyValue adlAppPropertyValue{};
						if (!property.GpuId.empty())
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

			//Set application settings
			return AdlAppPropertySet(adlApp);
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("Failed updating application properties (Exception)");
			return false;
		}
	}
}