#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"
#include "AdlxValuesLoadMultimedia.h"
#include "AdlxValuesLoadDisplay.h"
#include "AdlxValuesLoadTuning.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesLoadGraphics(AdlApplication& appInfo)
	{
		try
		{
			//Check application
			if (appInfo.FileName.empty() || appInfo.FilePath.empty())
			{
				return;
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
			std::thread threadEnableSaving([]()
				{
					Sleep(500);
					disable_saving = false;
				});
			threadEnableSaving.detach();

			//Set result
			AVDebugWriteLine("Loaded selected app values.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("Failed loading selected app values (Exception)");
		}
	}

	void MainPage::AdlxValuesLoadSelectDisplay(ADLDisplayInfo displayInfo)
	{
		try
		{
			//Disable saving
			disable_saving = true;

			//Get adapter and display index
			adl_Display_AdapterIndex = displayInfo.displayID.iDisplayLogicalAdapterIndex;
			adl_Display_DisplayIndex = displayInfo.displayID.iDisplayLogicalIndex;
			AVDebugWriteLine("Selected display index: A" << adl_Display_AdapterIndex << " / D" << adl_Display_DisplayIndex);

			//Update button text
			textblock_DisplaySelect().Text(char_to_wstring(displayInfo.strDisplayName));

			//Load display settings
			AdlxValuesLoadDisplay();

			//Load eyefinity settings
			AdlxValuesLoadEyefinity();

			//Load information
			AdlxInfoLoad();

			//Enable saving
			std::thread threadEnableSaving([]()
				{
					Sleep(500);
					disable_saving = false;
				});
			threadEnableSaving.detach();

			//Set result
			AVDebugWriteLine("Loaded selected display values.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("Failed loading selected display values (Exception)");
		}
	}

	void MainPage::AdlxValuesLoadSelectGpu(AdapterInfo adapterInfo)
	{
		try
		{
			//Disable saving
			disable_saving = true;

			//Get gpu adapter index
			adl_Gpu_AdapterIndex = adapterInfo.iAdapterIndex;
			AVDebugWriteLine("Selected gpu index: " << adl_Gpu_AdapterIndex);

			//Get gpu registry path
			adl_Gpu_RegistryPath = string_to_wstring(adapterInfo.strDriverPathExt);

			//Get gpu device identifier
			adl_Gpu_DeviceIdentifier = AdlxGetGpuIdentifier(adl_Gpu_AdapterIndex);

			//DriverBug#1
			//Get gpu unique identifier
			//adl_Gpu_UniqueIdentifierHex = number_to_hexwstring_littleendian(adapterInfo.iBusNumber, 4, true);
			adl_Gpu_UniqueIdentifierHex = L"0x0001";

			//Update button text
			textblock_GpuSelect().Text(char_to_wstring(adapterInfo.strAdapterName));

			//Load tuning values to interface
			AdlxValuesLoadTuning(adl_Gpu_AdapterIndex, tuningFanSettingsCurrent.Application.value());

			//Load graphics settings
			AdlxValuesLoadGraphics(adl_App_Current);

			//Load multimedia settings
			AdlxValuesLoadMultimedia();

			//Load information
			AdlxInfoLoad();

			//Enable saving
			std::thread threadEnableSaving([]()
				{
					Sleep(500);
					disable_saving = false;
				});
			threadEnableSaving.detach();

			//Set result
			AVDebugWriteLine("Loaded selected gpu values.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("Failed loading selected gpu values (Exception)");
		}
	}
}