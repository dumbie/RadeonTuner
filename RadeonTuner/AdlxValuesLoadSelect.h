#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"
#include "AdlValuesLoadGraphicsApp.h"
#include "AdlValuesLoadGraphicsRegistry.h"
#include "AdlxValuesLoadMultimedia.h"
#include "AdlxValuesLoadDisplay.h"
#include "AdlxValuesLoadTuning.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesLoadSelectApp()
	{
		try
		{
			//Disable saving
			disable_saving = true;

			//Set selected index
			adl_AppSelectedIndex = combobox_AppSelect().SelectedIndex();

			//Get selected application
			auto selectedAppWrapper = AdlAppSelectedGet();

			//Check selected application
			if (!selectedAppWrapper.has_value())
			{
				AVDebugWriteLine("ADL application is not selected.");
				return;
			}

			//Get selected application
			AdlApplication& selectedApp = selectedAppWrapper.value();

			//Get application details
			std::wstring applicationFileName = selectedApp.FileName;
			std::wstring applicationFilePath = selectedApp.FilePath;
			textblock_GraphicsOptions_Name().Text(applicationFileName);
			textblock_GraphicsOptions_Details().Text(applicationFilePath);
			AVDebugWriteLine("Selected app: " << applicationFileName);

			//Check application type
			if (applicationFileName == L"Global" && selectedApp.Global)
			{
				//Fix make sure default settings are set before loading settings

				//Update interface
				button_Graphics_Remove().IsEnabled(false);

				//Load application graphics settings
				AdlValuesLoadGraphicsRegistry();
			}
			else
			{
				//Fix check if application executable exists and warn user profile might not work

				//Update interface
				button_Graphics_Remove().IsEnabled(true);

				//Check and set default application properties
				AdlAppsSetDefaults(selectedApp, false, true);

				//Load application graphics settings
				AdlValuesLoadGraphicsApp();
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

	void MainPage::AdlxValuesLoadSelectDisplay()
	{
		try
		{
			//Disable saving
			disable_saving = true;

			//Get selected display
			int selectedDisplayIndex = combobox_DisplaySelect().SelectedIndex();
			ADLDisplayInfo displayInfo = adl_List_Displays[selectedDisplayIndex];

			//Get adapter and display index
			adl_Display_AdapterIndex = displayInfo.displayID.iDisplayLogicalAdapterIndex;
			adl_Display_DisplayIndex = displayInfo.displayID.iDisplayLogicalIndex;
			AVDebugWriteLine("Selected display index: A" << adl_Display_AdapterIndex << " / D" << adl_Display_DisplayIndex);

			//Load display settings
			AdlxValuesLoadDisplay();

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

	void MainPage::AdlxValuesLoadSelectGpu()
	{
		try
		{
			//Disable saving
			disable_saving = true;

			//Get selected gpu
			int selectedGpuIndex = combobox_GpuSelect().SelectedIndex();
			AdapterInfo adapterInfo = adl_List_Gpus[selectedGpuIndex];

			//Get gpu adapter index
			adl_Gpu_AdapterIndex = adapterInfo.iAdapterIndex;
			AVDebugWriteLine("Selected gpu index: " << adl_Gpu_AdapterIndex);

			//Get gpu registry path
			gpuRegistryPath = string_to_wstring(adapterInfo.strDriverPathExt);

			//DriverBug#1
			//Get gpu unique identifier
			//gpuUniqueIdentifierHex = number_to_hexwstring_littleendian(adapterInfo.iBusNumber, 4, true);
			gpuUniqueIdentifierHex = L"0x0001";

			//Load tuning values to interface
			AdlxValuesLoadTuning();

			//Load graphics settings
			AdlxValuesLoadSelectApp();

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