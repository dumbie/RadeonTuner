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

	bool MainPage::AdlAppPropertySave(AdlApplication& adlApp)
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
			//Set application properties
			std::vector<AdlAppProperty> adlAppProperties{};
			AdlAppProperty adlAppProperty0{};
			adlAppProperty0.Name = propertyName;
			AdlAppPropertyValue adlAppPropertyValue0{};
			adlAppPropertyValue0.GpuId = propertyGpuId;
			adlAppPropertyValue0.Value = propertyValue;
			adlAppProperty0.Values = { adlAppPropertyValue0 };
			adlAppProperties.push_back(adlAppProperty0);

			//Update application properties
			return AdlAppPropertyUpdate(adlApp, adlAppProperties);
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("Failed updating application property (Exception)");
			return false;
		}
	}

	bool MainPage::AdlAppPropertyUpdate(AdlApplication& adlApp, std::vector<AdlAppProperty> newProperties)
	{
		try
		{
			//Set properties values
			for (AdlAppProperty newProperty : newProperties)
			{
				try
				{
					//Status variables
					bool propertyExists = false;
					bool propertyUpdated = false;

					//Update property value if it exists
					for (AdlAppProperty& appProperty : adlApp.Properties)
					{
						try
						{
							if (appProperty.Name == newProperty.Name)
							{
								propertyExists = true;
								for (AdlAppPropertyValue& appPropertyValue : appProperty.Values)
								{
									for (AdlAppPropertyValue newPropertyValue : newProperty.Values)
									{
										try
										{
											//Update property value
											if (!newPropertyValue.GpuId.empty())
											{
												if (appPropertyValue.GpuId == newPropertyValue.GpuId)
												{
													appPropertyValue.Value = newPropertyValue.Value;
													propertyUpdated = true;
													AVDebugWriteLine(L"Updated value: " << appProperty.Type << L" / " << newProperty.Name << L" / " << newPropertyValue.Value << L" / " << newPropertyValue.GpuId);
												}
											}
											else
											{
												appPropertyValue.Value = newPropertyValue.Value;
												propertyUpdated = true;
												AVDebugWriteLine(L"Updated value: " << appProperty.Type << L" / " << newProperty.Name << L" / " << newPropertyValue.Value);
											}
										}
										catch (...) {}
									}
								}
							}
						}
						catch (...) {}
					}

					//Add property value if it does not exist
					if (propertyExists && !propertyUpdated)
					{
						for (AdlAppProperty& appProperty : adlApp.Properties)
						{
							for (AdlAppPropertyValue newPropertyValue : newProperty.Values)
							{
								try
								{
									if (appProperty.Name == newProperty.Name)
									{
										//Add property value
										appProperty.Values.insert(appProperty.Values.begin(), newPropertyValue);

										propertyUpdated = true;
										AVDebugWriteLine(L"Added value: " << appProperty.Type << L" / " << newProperty.Name << L" / " << newPropertyValue.Value << L" / " << newPropertyValue.GpuId);
									}
								}
								catch (...) {}
							}
						}
					}

					//Add property if it does not exist
					if (!propertyExists && !propertyUpdated)
					{
						//Check property type
						DATATYPES propertyType = AdlAppPropertyDataTypeGet(newProperty.Name, adlApp.DriverArea);
						if (propertyType == DT_Unknown)
						{
							AVDebugWriteLine(L"Unknown property type, not adding: " << newProperty.Name);
							continue;
						}

						//Set property type
						newProperty.Type = propertyType;

						//Add property
						adlApp.Properties.insert(adlApp.Properties.begin(), newProperty);

						propertyUpdated = true;
						AVDebugWriteLine("Added property: " << newProperty.Type << L" / " << newProperty.Name << L" / " << newProperty.GetValuesString());
					}
				}
				catch (...) {}
			}

			//Save application settings
			return AdlAppPropertySave(adlApp);
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("Failed updating application properties (Exception)");
			return false;
		}
	}
}