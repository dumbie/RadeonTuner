#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesResetSelectDisplay()
	{
		try
		{
			//Update button text
			textblock_DisplaySelect().Text(L"Select display");

			//Update access status
			stackpanel_Display_AccessOverlay().Visibility(Visibility::Visible);
			button_AppSelect_Display().IsEnabled(false);
			button_AppAdd_Display().IsEnabled(false);
			button_AppRemove_Display().IsEnabled(false);
			button_Display_Apply().IsEnabled(false);
			button_Display_Reset().IsEnabled(false);
			button_Display_Import().IsEnabled(false);
			button_Display_Export().IsEnabled(false);
		}
		catch (...) {}
	}

	void MainPage::AdlxValuesResetSelectGpu()
	{
		try
		{
			//Update button text
			textblock_GpuSelect().Text(L"Select graphics card");

			//Update access status
			stackpanel_Tuning_AccessOverlay().Visibility(Visibility::Visible);
			button_AppSelect_Tuning().IsEnabled(false);
			button_AppAdd_Tuning().IsEnabled(false);
			button_AppRemove_Tuning().IsEnabled(false);
			button_Tuning_Apply().IsEnabled(false);
			button_Tuning_Reset().IsEnabled(false);
			button_Tuning_Import().IsEnabled(false);
			button_Tuning_Export().IsEnabled(false);

			stackpanel_Fans_AccessOverlay().Visibility(Visibility::Visible);
			button_Fan_Apply().IsEnabled(false);
			button_Fan_Reset().IsEnabled(false);
			button_Fan_Import().IsEnabled(false);
			button_Fan_Export().IsEnabled(false);

			stackpanel_Graphics_AccessOverlay().Visibility(Visibility::Visible);
			button_AppSelect_Graphics().IsEnabled(false);
			button_AppAdd_Graphics().IsEnabled(false);
			button_AppRemove_Graphics().IsEnabled(false);
			button_Graphics_Apply().IsEnabled(false);
			button_Graphics_Reset().IsEnabled(false);
			button_Graphics_Import().IsEnabled(false);
			button_Graphics_Export().IsEnabled(false);

			stackpanel_Multimedia_AccessOverlay().Visibility(Visibility::Visible);
			button_AppSelect_Multimedia().IsEnabled(false);
			button_Multimedia_Apply().IsEnabled(false);
			button_Multimedia_Reset().IsEnabled(false);
		}
		catch (...) {}
	}

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

			//Update access status
			stackpanel_Display_AccessOverlay().Visibility(Visibility::Collapsed);

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

			//Update access status
			stackpanel_Tuning_AccessOverlay().Visibility(Visibility::Collapsed);
			stackpanel_Fans_AccessOverlay().Visibility(Visibility::Collapsed);
			stackpanel_Graphics_AccessOverlay().Visibility(Visibility::Collapsed);
			stackpanel_Multimedia_AccessOverlay().Visibility(Visibility::Collapsed);

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