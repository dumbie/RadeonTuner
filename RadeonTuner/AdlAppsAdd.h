#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "MainVariables.h"

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
			std::wstring addFileName;
			std::wstring addFilePath;
			std::wstring addProfileTag;
			if (filePath == L"*.*")
			{
				addFileName = L"*.*";
				addFilePath = L"*";
			}
			else
			{
				auto fileSystem = std::filesystem::path(filePath);
				addFileName = fileSystem.filename().wstring();
				addFilePath = L"*";
			}

			//Check if application exists and skip
			if (AdlAppExists(addFileName, addFilePath, driverArea))
			{
				AVDebugWriteLine("Application already exists: " << filePath);
				return false;
			}

			AVDebugWriteLine("Adding application: " << addFileName << " / " << addFilePath << " / " << driverArea);

			//Create adl application
			AdlApplication adlApp{};
			adlApp.FileName = addFileName;
			adlApp.FilePath = addFilePath;
			adlApp.DriverArea = driverArea;

			//Set default properties
			AdlAppDefaultPropertiesSet(adlApp);

			//Set application settings
			AdlAppPropertySet(adlApp);

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