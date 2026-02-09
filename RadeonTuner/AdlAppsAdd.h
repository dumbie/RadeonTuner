#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "AdlVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::AdlAppAdd(std::wstring filePath, std::wstring driverArea)
	{
		try
		{
			//Check file path
			if (filePath.empty())
			{
				AVDebugWriteLine("Application file path is empty.");
				return false;
			}

			//Check driver area
			if (driverArea.empty())
			{
				AVDebugWriteLine("Application driver area is empty.");
				return false;
			}

			//Convert file path to name
			auto fileSystem = std::filesystem::path(filePath);
			std::wstring addFileName = fileSystem.filename();
			std::wstring addFilePath = fileSystem.parent_path();
			addFilePath += L"*";

			AVDebugWriteLine("Adding application: " << addFileName << " / " << addFilePath << " / " << driverArea);

			//Generate profile name
			std::wstring profileName = AdlAppProfileGenerateName();

			//Create adl application
			AdlApplication adlApp{};
			adlApp.FileName = addFileName;
			adlApp.FilePath = addFilePath;
			adlApp.DriverArea = driverArea;
			adlApp.ProfileName = profileName;

			//Create adl application property
			AdlAppProperty adlAppProperty{};
			adlAppProperty.Type = AdlAppPropertyTypeGet(L"Main3D", driverArea);
			adlAppProperty.Name = L"Main3D";
			adlAppProperty.DriverArea = driverArea;
			adlApp.Properties.push_back(adlAppProperty);

			//Get record properties
			std::vector<ADLPropertyRecordCreate> recordCreate = AdlAppPropertyRecordCreateGet(adlApp);

			//Check if application exists and skip
			if (AdlAppExists(addFileName, addFilePath, driverArea))
			{
				AVDebugWriteLine("Application already exists: " << filePath);
				return false;
			}

			//Create application profile
			adl_Res0 = _ADL2_ApplicationProfiles_Profile_Create(adl_Context, driverArea.c_str(), profileName.c_str(), recordCreate.size(), recordCreate.data());
			AVDebugWriteLine("Created application profile: " << adl_Res0);
			//-3 invalid profile, atleast 1 property needed
			//-16 invalid properties
			//-18 already exists

			//Assign application profile
			adl_Res0 = _ADL2_ApplicationProfiles_ProfileApplicationX2_Assign(adl_Context, addFileName.c_str(), addFilePath.c_str(), NULL, NULL, driverArea.c_str(), profileName.c_str());
			AVDebugWriteLine("Assigned application profile: " << adl_Res0);
			//-15 profile not found or invalid

			//Set result
			return adl_Res0 == ADL_OK;
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("Failed adding application (Exception)");
			return false;
		}
	}
}