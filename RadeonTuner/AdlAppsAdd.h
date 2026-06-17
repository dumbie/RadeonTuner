#pragma once
#include "pch.h"
#include "MainPage.h"
#include "AdlDefinitions.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	std::wstring MainPage::AdlAppAdd(std::wstring filePath, std::wstring driverArea)
	{
		try
		{
			//Check file path
			if (filePath.empty())
			{
				AVDebugWriteLine("Application file path is empty.");
				return L"File path is empty";
			}

			//Check driver area
			if (driverArea.empty())
			{
				AVDebugWriteLine("Application driver area is empty.");
				return L"Driver area is empty";
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
				addFilePath = L"*\\*";
				//addFilePath = fileSystem.parent_path().wstring();
				//size_t lastFolderPosition = addFilePath.find_last_of(L"\\");
				//addFilePath = L"*" + addFilePath.substr(lastFolderPosition) + L"*";
				//DriverBug#2
			}

			//Check if application exists and skip
			if (AdlAppExists(addFileName, addFilePath, driverArea))
			{
				AVDebugWriteLine("Application already exists: " << filePath);
				return L"Application already exists";
			}

			AVDebugWriteLine("Adding application: " << addFileName << " / " << addFilePath << " / " << driverArea);

			//Create adl application
			AdlApplication adlApp{};
			adlApp.FileName = addFileName;
			adlApp.FilePath = addFilePath;
			adlApp.DriverArea = driverArea;

			//Set default properties
			if (AdlGraphicsResetApp(adlApp, true, false))
			{
				return L"Application added";
			}
			else
			{
				return L"Application not added";
			}
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("Failed adding application (Exception)");
			return L"Failed adding application";
		}
	}
}