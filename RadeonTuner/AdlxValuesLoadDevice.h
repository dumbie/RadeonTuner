#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	winrt::IAsyncAction MainPage::AdlxValuesLoadSelectDisplay(ADLDisplayInfo displayInfo)
	{
		try
		{
			//Disable saving
			disable_saving = true;

			//Get adapter and display index
			adl_Display_AdapterIndex = displayInfo.displayID.iDisplayLogicalAdapterIndex;
			adl_Display_DisplayIndex = displayInfo.displayID.iDisplayLogicalIndex;
			AVDebugWriteLine("Selected display index: A" << adl_Display_AdapterIndex << " / D" << adl_Display_DisplayIndex);

			//Get display device identifier
			adl_Display_DeviceIdentifier = AdlxGetDisplayIdentifier(adl_Display_AdapterIndex, adl_Display_DisplayIndex);

			//Update button text
			textblock_DisplaySelect().Text(char_to_wstring(displayInfo.strDisplayName));

			//Load display settings
			co_await AdlxValuesLoadSelectDisplayApp(adl_Display_AdapterIndex, adl_Display_DisplayIndex, displaySettingsProfile.Application.value());

			//Load information
			AdlxInfoLoad();

			//Enable saving
			co_await AsyncTaskDelay(100, AppVariables::App.GetDispatcher());
			disable_saving = false;

			//Set result
			AVDebugWriteLine("Loaded selected display values.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("Failed loading selected display values (Exception)");
		}
	}

	winrt::IAsyncAction MainPage::AdlxValuesLoadSelectGpu(AdapterInfo adapterInfo)
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

			//Load tuning and fans settings
			co_await AdlxValuesLoadSelectTuningApp(adl_Gpu_AdapterIndex, tuningFanSettingsProfile.Application.value());

			//Load graphics settings
			co_await AdlxValuesLoadSelectGraphicsApp(adl_Gpu_AdapterIndex, graphicsSettingsProfile.Application.value());

			//Load multimedia settings
			co_await AdlxValuesLoadSelectMultimediaApp(adl_Gpu_AdapterIndex, multimediaSettingsProfile.Application.value());

			//Load information
			AdlxInfoLoad();

			//Enable saving
			co_await AsyncTaskDelay(100, AppVariables::App.GetDispatcher());
			disable_saving = false;

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