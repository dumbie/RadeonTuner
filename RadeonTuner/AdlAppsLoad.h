#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "MainVariables.h"
#include <regex>

//Application profiles location
//%WINDIR%\System32\atiapfxx.blb
//%LOCALAPPDATA%\AMD\CN\gmdb.blb
//%LOCALAPPDATA%\AMD\CN\gmrevert.blb
//%LOCALAPPDATA%\AMD\CN\GExDb.blb
//%LOCALAPPDATA%\ATI\ACE\APL\User.blb
//%PROGRAMFILES%\AMD\CNext\CNext\cn.blb
//%PROGRAMFILES%\AMD\CNext\CNext\optimize_titles_db.blb
//Computer\HKEY_CURRENT_USER\Software\AMD\CN
//Computer\HKEY_LOCAL_MACHINE\Software\AMD\CN

namespace winrt::RadeonTuner::implementation
{
	std::vector<AdlApplication> MainPage::AdlAppLoad(std::wstring driverArea)
	{
		std::vector<AdlApplication> adlApps{};
		try
		{
			//Get applications
			int adlApplicationsCount = 0;
			ADLApplicationRecord* adlApplications;
			adl_Res0 = _ADL2_ApplicationProfiles_Applications_Get(adl_Context, driverArea.c_str(), &adlApplicationsCount, &adlApplications);
			if (adl_Res0 == ADL_OK)
			{
				for (int i = 0; i < adlApplicationsCount; i++)
				{
					try
					{
						//Create adl application
						AdlApplication adlApp{};
						if (adlApplications[i].strFileName != NULL)
						{
							adlApp.FileName = adlApplications[i].strFileName;
						}
						if (adlApplications[i].strPathName != NULL)
						{
							adlApp.FilePath = adlApplications[i].strPathName;
						}
						if (adlApplications[i].strProfileName != NULL)
						{
							adlApp.ProfileName = adlApplications[i].strProfileName;
						}
						if (adlApplications[i].strArea != NULL)
						{
							adlApp.DriverArea = adlApplications[i].strArea;
						}
						adlApp.RecordSource = adlApplications[i].recordSource;

						//Load application profile
						ADLApplicationProfile* lppProfile;
						adl_Res0 = _ADL2_ApplicationProfiles_ProfileOfAnApplicationX2_Search(adl_Context, adlApp.FileName.c_str(), adlApp.FilePath.c_str(), NULL, adlApp.DriverArea.c_str(), &lppProfile);
						if (adl_Res0 == ADL_OK)
						{
							uint32_t propertyOffset = 0;
							for (int index = 0; index < lppProfile->iCount; index++)
							{
								try
								{
									//Get property record
									PropertyRecord* propertyRecord = (PropertyRecord*)((BYTE*)lppProfile->record + propertyOffset);

									//Create adl application property
									AdlAppProperty adlAppProperty{};

									//Get property name
									adlAppProperty.Name = char_to_wstring(propertyRecord->strName);

									//Get property type
									adlAppProperty.Type = AdlAppPropertyDataTypeGet(adlAppProperty.Name, adlApp.DriverArea);

									//Get property value
									if (propertyRecord->iDataSize > 0)
									{
										if (adlAppProperty.Type == DT_Stringed)
										{
											std::wstring convertedValue;
											convertedValue.resize(propertyRecord->iDataSize / 2);
											memcpy(convertedValue.data(), propertyRecord->uData, propertyRecord->iDataSize);
											if (wstring_contains(convertedValue, L"::"))
											{
												//Extract gpuid and values
												std::wsmatch regexMatch;
												std::wstring regexString = convertedValue;
												std::wregex regexPattern(L"(0[xX][0-9a-fA-F]+)::(.*?);;");
												while (std::regex_search(regexString, regexMatch, regexPattern))
												{
													AdlAppPropertyValue adlAppPropertyValue{};
													adlAppPropertyValue.GpuId = regexMatch[1];
													adlAppPropertyValue.Value = regexMatch[2];
													adlAppProperty.Values.push_back(adlAppPropertyValue);
													regexString = regexMatch.suffix().str();
												}
											}
											else
											{
												AdlAppPropertyValue adlAppPropertyValue{};
												adlAppPropertyValue.Value = convertedValue;
												adlAppProperty.Values.push_back(adlAppPropertyValue);
											}
										}
										else if (adlAppProperty.Type == DT_Boolean)
										{
											bool convertedValue = (bool)propertyRecord->uData[0] ? true : false;
											AdlAppPropertyValue adlAppPropertyValue{};
											adlAppPropertyValue.Value = number_to_wstring(convertedValue);
											adlAppProperty.Values.push_back(adlAppPropertyValue);
										}
										else if (adlAppProperty.Type == DT_Dword)
										{
											UCHAR convertedValue = (UCHAR)propertyRecord->uData[0];
											AdlAppPropertyValue adlAppPropertyValue{};
											adlAppPropertyValue.Value = number_to_wstring(convertedValue);
											adlAppProperty.Values.push_back(adlAppPropertyValue);
										}
										else
										{
											AVDebugWriteLine("Property load type not supported: " << adlAppProperty.Type);
										}
									}

									//Add adl application property
									adlApp.Properties.push_back(adlAppProperty);

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