#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::AdlAppUnlock(AdlApplication adlApp, bool unlock)
	{
		try
		{
			AVDebugWriteLine("Unlocking application features: " << adlApp.FileName << " / " << adlApp.FilePath);

			//Note: Renaming an application to SOTTR.exe enables Radeon Boost support, setting BOOST WListed does not work.
			//Area: PXDynamic Profile: HighPerfGPUAffinity
			//Area: FRAMEGEN Property: AFMF3

			//Unlock FFX Super Resolution Override
			{
				std::wstring driverArea = L"FSROVR";
				std::wstring profileName = L"RADU{FSROVR}";

				if (unlock)
				{
					//Set application properties
					std::vector<AdlAppProperty> adlAppProperties{};

					//FFX Super Resolution
					AdlAppProperty adlAppProperty0{};
					adlAppProperty0.Type = AdlAppPropertyDataTypeGet(L"FsrOvr_WListed", driverArea);
					adlAppProperty0.Name = L"FsrOvr_WListed";
					AdlAppPropertyValue adlAppPropertyValue0{};
					adlAppPropertyValue0.Value = L"1";
					adlAppProperty0.Values = { adlAppPropertyValue0 };
					adlAppProperties.push_back(adlAppProperty0);

					//Get record properties
					std::vector<ADLPropertyRecordCreate> recordCreate = AdlAppPropertyRecordCreateGet(adlAppProperties);

					//Create application profile
					adl_Res0 = _ADL2_ApplicationProfiles_Profile_Create(adl_Context, driverArea.c_str(), profileName.c_str(), recordCreate.size(), recordCreate.data());
					AVDebugWriteLine("Created application profile: " << driverArea.c_str() << " / " << profileName.c_str() << " / " << adl_Res0);

					//Assign application profile
					adl_Res0 = _ADL2_ApplicationProfiles_ProfileApplicationX2_Assign(adl_Context, adlApp.FileName.c_str(), adlApp.FilePath.c_str(), NULL, NULL, driverArea.c_str(), profileName.c_str());
					AVDebugWriteLine("Assigned application profile: " << driverArea.c_str() << " / " << profileName.c_str() << " / " << adl_Res0);
				}
				else
				{
					//Remove profile from application
					adl_Res0 = _ADL2_ApplicationProfiles_RemoveApplication(adl_Context, adlApp.FileName.c_str(), adlApp.FilePath.c_str(), NULL, adlApp.DriverArea.c_str());
					AVDebugWriteLine("Removed application profile: " << driverArea.c_str() << " / " << profileName.c_str() << " / " << adl_Res0);
				}
			}

			//Unlock FFX Features
			{
				std::wstring driverArea = L"FFX";
				std::wstring profileName = L"RADU{FFX}";

				if (unlock)
				{
					//Set application properties
					std::vector<AdlAppProperty> adlAppProperties{};

					//FFX Neural Radiance Cache
					AdlAppProperty adlAppProperty0{};
					adlAppProperty0.Type = AdlAppPropertyDataTypeGet(L"Nrc_WListed", driverArea);
					adlAppProperty0.Name = L"Nrc_WListed";
					AdlAppPropertyValue adlAppPropertyValue0{};
					adlAppPropertyValue0.Value = L"1";
					adlAppProperty0.Values = { adlAppPropertyValue0 };
					adlAppProperties.push_back(adlAppProperty0);

					//FFX Interpolation Frame Generation
					AdlAppProperty adlAppProperty1{};
					adlAppProperty1.Type = AdlAppPropertyDataTypeGet(L"Mlfi_WListed", driverArea);
					adlAppProperty1.Name = L"Mlfi_WListed";
					AdlAppPropertyValue adlAppPropertyValue1{};
					adlAppPropertyValue1.Value = L"1";
					adlAppProperty1.Values = { adlAppPropertyValue1 };
					adlAppProperties.push_back(adlAppProperty1);

					//FFX Ray Regeneration Denoiser
					AdlAppProperty adlAppProperty2{};
					adlAppProperty2.Type = AdlAppPropertyDataTypeGet(L"Mld_WListed", driverArea);
					adlAppProperty2.Name = L"Mld_WListed";
					AdlAppPropertyValue adlAppPropertyValue2{};
					adlAppPropertyValue2.Value = L"1";
					adlAppProperty2.Values = { adlAppPropertyValue2 };
					adlAppProperties.push_back(adlAppProperty2);

					//FFX Multi Frame Generation
					AdlAppProperty adlAppProperty3{};
					adlAppProperty3.Type = AdlAppPropertyDataTypeGet(L"Mfg_WListed", driverArea);
					adlAppProperty3.Name = L"Mfg_WListed";
					AdlAppPropertyValue adlAppPropertyValue3{};
					adlAppPropertyValue3.Value = L"1";
					adlAppProperty3.Values = { adlAppPropertyValue3 };
					adlAppProperties.push_back(adlAppProperty3);

					//Get record properties
					std::vector<ADLPropertyRecordCreate> recordCreate = AdlAppPropertyRecordCreateGet(adlAppProperties);

					//Create application profile
					adl_Res0 = _ADL2_ApplicationProfiles_Profile_Create(adl_Context, driverArea.c_str(), profileName.c_str(), recordCreate.size(), recordCreate.data());
					AVDebugWriteLine("Created application profile: " << driverArea.c_str() << " / " << profileName.c_str() << " / " << adl_Res0);

					//Assign application profile
					adl_Res0 = _ADL2_ApplicationProfiles_ProfileApplicationX2_Assign(adl_Context, adlApp.FileName.c_str(), adlApp.FilePath.c_str(), NULL, NULL, driverArea.c_str(), profileName.c_str());
					AVDebugWriteLine("Assigned application profile: " << driverArea.c_str() << " / " << profileName.c_str() << " / " << adl_Res0);
				}
				else
				{
					//Remove profile from application
					adl_Res0 = _ADL2_ApplicationProfiles_RemoveApplication(adl_Context, adlApp.FileName.c_str(), adlApp.FilePath.c_str(), NULL, adlApp.DriverArea.c_str());
					AVDebugWriteLine("Removed application profile: " << driverArea.c_str() << " / " << profileName.c_str() << " / " << adl_Res0);
				}
			}

			//Unlock Radeon Boost
			{
				//Set profile name
				std::wstring driverArea = L"BOOST";
				std::wstring profileName = L"RADU{BOOST}";

				if (unlock)
				{
					//Set application properties
					std::vector<AdlAppProperty> adlAppProperties{};
					AdlAppProperty adlAppProperty0{};
					adlAppProperty0.Type = AdlAppPropertyDataTypeGet(L"Bst_WListed", driverArea);
					adlAppProperty0.Name = L"Bst_WListed";
					AdlAppPropertyValue adlAppPropertyValue0{};
					adlAppPropertyValue0.Value = L"1";
					adlAppProperty0.Values = { adlAppPropertyValue0 };
					adlAppProperties.push_back(adlAppProperty0);

					AdlAppProperty adlAppProperty1{};
					adlAppProperty1.Type = AdlAppPropertyDataTypeGet(L"Bst_WL_NonVRS", driverArea);
					adlAppProperty1.Name = L"Bst_WL_NonVRS";
					AdlAppPropertyValue adlAppPropertyValue1{};
					adlAppPropertyValue1.Value = L"1";
					adlAppProperty1.Values = { adlAppPropertyValue1 };
					adlAppProperties.push_back(adlAppProperty1);

					AdlAppProperty adlAppProperty2{};
					adlAppProperty2.Type = AdlAppPropertyDataTypeGet(L"Bst_AdaWListed", driverArea);
					adlAppProperty2.Name = L"Bst_AdaWListed";
					AdlAppPropertyValue adlAppPropertyValue2{};
					adlAppPropertyValue2.Value = L"1";
					adlAppProperty2.Values = { adlAppPropertyValue2 };
					adlAppProperties.push_back(adlAppProperty2);

					//Get record properties
					std::vector<ADLPropertyRecordCreate> recordCreate = AdlAppPropertyRecordCreateGet(adlAppProperties);

					//Create application profile
					adl_Res0 = _ADL2_ApplicationProfiles_Profile_Create(adl_Context, driverArea.c_str(), profileName.c_str(), recordCreate.size(), recordCreate.data());
					AVDebugWriteLine("Created application profile: " << driverArea.c_str() << " / " << profileName.c_str() << " / " << adl_Res0);

					//Assign application profile
					adl_Res0 = _ADL2_ApplicationProfiles_ProfileApplicationX2_Assign(adl_Context, adlApp.FileName.c_str(), adlApp.FilePath.c_str(), NULL, NULL, driverArea.c_str(), profileName.c_str());
					AVDebugWriteLine("Assigned application profile: " << driverArea.c_str() << " / " << profileName.c_str() << " / " << adl_Res0);
				}
				else
				{
					//Remove profile from application
					adl_Res0 = _ADL2_ApplicationProfiles_RemoveApplication(adl_Context, adlApp.FileName.c_str(), adlApp.FilePath.c_str(), NULL, adlApp.DriverArea.c_str());
					AVDebugWriteLine("Removed application profile: " << driverArea.c_str() << " / " << profileName.c_str() << " / " << adl_Res0);
				}
			}

			//Unlock Radeon Anti-Lag
			{
				//Set profile name
				std::wstring driverArea = L"DELAG";
				std::wstring profileName = L"RADU{DELAG}";

				if (unlock)
				{
					//Set application properties
					std::vector<AdlAppProperty> adlAppProperties{};
					AdlAppProperty adlAppProperty0{};
					adlAppProperty0.Type = AdlAppPropertyDataTypeGet(L"DlgNxt_WListed", driverArea);
					adlAppProperty0.Name = L"DlgNxt_WListed";
					AdlAppPropertyValue adlAppPropertyValue0{};
					adlAppPropertyValue0.Value = L"1";
					adlAppProperty0.Values = { adlAppPropertyValue0 };
					adlAppProperties.push_back(adlAppProperty0);

					//Get record properties
					std::vector<ADLPropertyRecordCreate> recordCreate = AdlAppPropertyRecordCreateGet(adlAppProperties);

					//Create application profile
					adl_Res0 = _ADL2_ApplicationProfiles_Profile_Create(adl_Context, driverArea.c_str(), profileName.c_str(), recordCreate.size(), recordCreate.data());
					AVDebugWriteLine("Created application profile: " << driverArea.c_str() << " / " << profileName.c_str() << " / " << adl_Res0);

					//Assign application profile
					adl_Res0 = _ADL2_ApplicationProfiles_ProfileApplicationX2_Assign(adl_Context, adlApp.FileName.c_str(), adlApp.FilePath.c_str(), NULL, NULL, driverArea.c_str(), profileName.c_str());
					AVDebugWriteLine("Assigned application profile: " << driverArea.c_str() << " / " << profileName.c_str() << " / " << adl_Res0);
				}
				else
				{
					//Remove profile from application
					adl_Res0 = _ADL2_ApplicationProfiles_RemoveApplication(adl_Context, adlApp.FileName.c_str(), adlApp.FilePath.c_str(), NULL, adlApp.DriverArea.c_str());
					AVDebugWriteLine("Removed application profile: " << driverArea.c_str() << " / " << profileName.c_str() << " / " << adl_Res0);
				}
			}

			//Unlock Radeon Chill
			{
				//Set profile name
				std::wstring driverArea = L"CHILL";
				std::wstring profileName = L"RADU{CHILL}";

				if (unlock)
				{
					//Set application properties
					std::vector<AdlAppProperty> adlAppProperties{};
					AdlAppProperty adlAppProperty0{};
					adlAppProperty0.Type = AdlAppPropertyDataTypeGet(L"Chil_WListed", driverArea);
					adlAppProperty0.Name = L"Chil_WListed";
					AdlAppPropertyValue adlAppPropertyValue0{};
					adlAppPropertyValue0.Value = L"1";
					adlAppProperty0.Values = { adlAppPropertyValue0 };
					adlAppProperties.push_back(adlAppProperty0);

					//Get record properties
					std::vector<ADLPropertyRecordCreate> recordCreate = AdlAppPropertyRecordCreateGet(adlAppProperties);

					//Create application profile
					adl_Res0 = _ADL2_ApplicationProfiles_Profile_Create(adl_Context, driverArea.c_str(), profileName.c_str(), recordCreate.size(), recordCreate.data());
					AVDebugWriteLine("Created application profile: " << driverArea.c_str() << " / " << profileName.c_str() << " / " << adl_Res0);

					//Assign application profile
					adl_Res0 = _ADL2_ApplicationProfiles_ProfileApplicationX2_Assign(adl_Context, adlApp.FileName.c_str(), adlApp.FilePath.c_str(), NULL, NULL, driverArea.c_str(), profileName.c_str());
					AVDebugWriteLine("Assigned application profile: " << driverArea.c_str() << " / " << profileName.c_str() << " / " << adl_Res0);
				}
				else
				{
					//Remove profile from application
					adl_Res0 = _ADL2_ApplicationProfiles_RemoveApplication(adl_Context, adlApp.FileName.c_str(), adlApp.FilePath.c_str(), NULL, adlApp.DriverArea.c_str());
					AVDebugWriteLine("Removed application profile: " << driverArea.c_str() << " / " << profileName.c_str() << " / " << adl_Res0);
				}
			}

			//Unlock Ray Tracing Boost
			{
				//Set profile name
				std::wstring driverArea = L"RTBOOST";
				std::wstring profileName = L"RADU{RTBOOST}";

				if (unlock)
				{
					//Set application properties
					std::vector<AdlAppProperty> adlAppProperties{};
					AdlAppProperty adlAppProperty0{};
					adlAppProperty0.Type = AdlAppPropertyDataTypeGet(L"RTBst_WListed", driverArea);
					adlAppProperty0.Name = L"RTBst_WListed";
					AdlAppPropertyValue adlAppPropertyValue0{};
					adlAppPropertyValue0.Value = L"1";
					adlAppProperty0.Values = { adlAppPropertyValue0 };
					adlAppProperties.push_back(adlAppProperty0);

					//Get record properties
					std::vector<ADLPropertyRecordCreate> recordCreate = AdlAppPropertyRecordCreateGet(adlAppProperties);

					//Create application profile
					adl_Res0 = _ADL2_ApplicationProfiles_Profile_Create(adl_Context, driverArea.c_str(), profileName.c_str(), recordCreate.size(), recordCreate.data());
					AVDebugWriteLine("Created application profile: " << driverArea.c_str() << " / " << profileName.c_str() << " / " << adl_Res0);

					//Assign application profile
					adl_Res0 = _ADL2_ApplicationProfiles_ProfileApplicationX2_Assign(adl_Context, adlApp.FileName.c_str(), adlApp.FilePath.c_str(), NULL, NULL, driverArea.c_str(), profileName.c_str());
					AVDebugWriteLine("Assigned application profile: " << driverArea.c_str() << " / " << profileName.c_str() << " / " << adl_Res0);
				}
				else
				{
					//Remove profile from application
					adl_Res0 = _ADL2_ApplicationProfiles_RemoveApplication(adl_Context, adlApp.FileName.c_str(), adlApp.FilePath.c_str(), NULL, adlApp.DriverArea.c_str());
					AVDebugWriteLine("Removed application profile: " << driverArea.c_str() << " / " << profileName.c_str() << " / " << adl_Res0);
				}
			}

			//Set result
			return true;
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("Failed unlocking application (Exception)");
			return false;
		}
	}
}