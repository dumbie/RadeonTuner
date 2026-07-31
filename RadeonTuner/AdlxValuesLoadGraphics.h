#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	winrt::fire_and_forget MainPage::AdlxValuesLoadSelectGraphics(AdlApplication& appInfo)
	{
		try
		{
			//Check application
			if (appInfo.FileName.empty() || appInfo.FilePath.empty())
			{
				co_return;
			}

			//Disable saving
			disable_saving = true;

			//Get application details
			std::wstring applicationFileName = appInfo.FileName;
			std::wstring applicationFilePath = appInfo.FilePath;
			AVDebugWriteLine("Selected app: " << applicationFileName << " / G" << appInfo.Global);

			//Update interface text
			textblock_AppSelect_Graphics().Text(applicationFileName);

			//Set current application
			adl_App_Current = appInfo;

			//Check application type
			if (applicationFileName == L"Global" && appInfo.Global)
			{
				//Fix make sure default settings are set before loading settings

				//Get current and default settings
				graphicsSettingsCurrent = GraphicsSettings_Generate_FromADLRegistry(adl_Gpu_AdapterIndex).value();

				//Convert settings values to interface
				GraphicsSettings_Convert_ToUI_ADL(graphicsSettingsCurrent);
			}
			else
			{
				//Fix check if application executable exists and warn user profile might not work

				//Check and set default application properties
				AdlAppsSetDefaults(appInfo, false, true);

				//Get current and default settings
				graphicsSettingsCurrent = GraphicsSettings_Generate_FromADLApp(appInfo).value();

				//Convert settings values to interface
				GraphicsSettings_Convert_ToUI_ADL(graphicsSettingsCurrent);
			}

			//Enable saving
			co_await AsyncTaskDelay(300, AppVariables::App.GetDispatcher());
			disable_saving = false;

			//Set result
			AVDebugWriteLine("Loaded selected app values.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("Failed loading selected app values (Exception)");
		}
	}
}