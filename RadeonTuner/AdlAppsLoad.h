#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "AdlVariables.h"

//Application profiles location
//%WINDIR%\System32\atiapfxx.blb
//%LOCALAPPDATA%\AMD\CN\gmdb.blb
//%LOCALAPPDATA%\AMD\CN\GExDb.blb
//%LOCALAPPDATA%\ATI\ACE\APL\User.blb
//%PROGRAMFILES%\AMD\CNext\CNext\cn.blb
//%PROGRAMFILES%\AMD\CNext\CNext\optimize_titles_db.blb
//Computer\HKEY_CURRENT_USER\Software\AMD\CN
//Computer\HKEY_LOCAL_MACHINE\Software\AMD\CN

namespace winrt::RadeonTuner::implementation
{
	std::vector<AdlApps> MainPage::AdlAppsLoad(std::wstring driverArea)
	{
		std::vector<AdlApps> adlApps{};
		try
		{
			int adlApplicationsCount = 0;
			ADLApplicationRecord* adlApplications;
			adl_Res0 = _ADL2_ApplicationProfiles_Applications_Get(adl_Context, driverArea.c_str(), &adlApplicationsCount, &adlApplications);
			if (adl_Res0 == ADL_OK)
			{
				for (int i = 0; i < adlApplicationsCount; i++)
				{
					try
					{
						AdlApps adlApp{};
						adlApp.AppTitle = adlApplications[i].strTitle;
						adlApp.FileName = adlApplications[i].strFileName;
						adlApp.FilePath = adlApplications[i].strPathName;
						adlApp.ProfileName = adlApplications[i].strProfileName;
						adlApp.DriverArea = adlApplications[i].strArea;
						adlApp.RecordSource = adlApplications[i].recordSource;

						ADLApplicationProfile* lppProfile;
						adl_Res0 = _ADL2_ApplicationProfiles_ProfileOfAnApplicationX2_Search(adl_Context, adlApplications[i].strFileName, adlApplications[i].strPathName, adlApplications[i].strVersion, adlApplications[i].strArea, &lppProfile);
						if (adl_Res0 == ADL_OK)
						{
							uint32_t propertyOffset = 0;
							for (int index = 0; index < lppProfile->iCount; index++)
							{
								try
								{
									//Get property record
									PropertyRecord* propertyRecord = (PropertyRecord*)((BYTE*)lppProfile->record + propertyOffset);

									//Get property type
									ADLProfilePropertyType propertyType = propertyRecord->eType;

									//Get property name
									std::wstring propertyName = char_to_wstring(propertyRecord->strName);

									//Get property value
									std::wstring propertyValue;
									if (propertyRecord->iDataSize > 0)
									{
										if (propertyType == ADL_PROFILEPROPERTY_TYPE_BINARY)
										{
											propertyValue.resize(propertyRecord->iDataSize / 2);
											memcpy(propertyValue.data(), propertyRecord->uData, propertyRecord->iDataSize);
											if (propertyValue.starts_with(L"0x0300::"))
											{
												propertyValue.erase(propertyValue.size() - 2);
												propertyValue.erase(0, 8);
											}
										}
									}

									//Convert to create record
									ADLPropertyRecordCreate propertyRecordCreate{};
									propertyRecordCreate.eType = AdlPropertyGetType(propertyName, adlApp.DriverArea);
									propertyRecordCreate.strPropertyName = _wcsdup(propertyName.c_str());
									propertyRecordCreate.strPropertyValue = _wcsdup(propertyValue.c_str());
									adlApp.PropertyRecords.push_back(propertyRecordCreate);

									//Move to next property record
									propertyOffset += sizeof(PropertyRecord) + (propertyRecord->iDataSize - 4);
								}
								catch (...) {}
							}
						}

						//Add application to list
						adlApps.push_back(adlApp);
					}
					catch (...) {}
				}

				AVDebugWriteLine("ADL applications loaded: " << adlApps.size());
			}
			else
			{
				AVDebugWriteLine("Failed loading ADL applications: " << adl_Res0);
			}

			//Set result
			return adlApps;
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("Failed loading ADL applications (Exception)");
			return adlApps;
		}
	}
}