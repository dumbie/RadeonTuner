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
			if (filePath == L"*.*")
			{
				addFileName = L"*.*";
				addFilePath = L"*\\*";
			}
			else
			{
				auto fileSystem = std::filesystem::path(filePath);
				addFileName = fileSystem.filename().wstring();
				addFilePath = fileSystem.parent_path().wstring();
				size_t lastFolderPosition = addFilePath.find_last_of(L"\\");
				addFilePath = L"*" + addFilePath.substr(lastFolderPosition) + L"*";
				//Note: this breaks profile compatibility with Radeon Software but allows user to move app folders.
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
			return AdlAppDefaultProperties(adlApp, true, false);
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("Failed adding application (Exception)");
			return false;
		}
	}
}