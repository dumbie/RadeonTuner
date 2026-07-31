#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	winrt::fire_and_forget MainPage::AdlxValuesLoadSelectGpu(AdapterInfo adapterInfo)
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
			AdlxValuesLoadSelectTuning(adl_Gpu_AdapterIndex, tuningFanSettingsCurrent.Application.value());

			//Load graphics settings
			AdlxValuesLoadSelectGraphics(adl_App_Current);

			//Load multimedia settings
			AdlxValuesLoadMultimedia();

			//Load information
			AdlxInfoLoad();

			//Enable saving
			co_await AsyncTaskDelay(300, AppVariables::App.GetDispatcher());
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

	void MainPage::AdlxValuesLoadSelectTuning(int gpuAdapterIndex, std::wstring gpuApplication)
	{
		try
		{
			//Get current and default settings
			TuningFanSettings tuningFanSettingsAdl = TuningFanSettings_Generate_FromADL(gpuAdapterIndex, gpuApplication, false).value();

			//Add gpu tuning and fans settings profile
			TuningFanSettings_Profile_Add(tuningFanSettingsAdl);

			//Device identifier
			std::wstring gpuDeviceId = tuningFanSettingsAdl.DeviceId.value();

			//Get tuning fan settings
			tuningFanSettingsCurrent = TuningFanSettings_Profile_Get(gpuDeviceId, gpuApplication).value();

			//Convert settings values to interface
			bool adlResult = TuningFanSettings_Convert_ToUI_Adl(tuningFanSettingsAdl);
			bool profileResult = TuningFanSettings_Convert_ToUI_Current(tuningFanSettingsCurrent);

			//Update button text
			textblock_AppSelect_Tuning().Text(gpuApplication);

			//Disable or enable keep active
			if (tuningFanSettingsAdl.TuningSupport && gpuApplication == L"Global")
			{
				toggleswitch_KeepActive().IsEnabled(true);
			}
			else
			{
				toggleswitch_KeepActive().IsEnabled(false);
			}

			//Update button colors
			if (adlResult && profileResult)
			{
				SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
				button_Tuning_Apply().Background(colorValid);
				button_Fan_Apply().Background(colorValid);
			}
			else
			{
				SolidColorBrush colorInvalid = Application::Current().Resources().Lookup(box_value(L"ApplicationInvalidBrush")).as<SolidColorBrush>();
				button_Tuning_Apply().Background(colorInvalid);
				button_Fan_Apply().Background(colorInvalid);
			}

			//Set result
			AVDebugWriteLine("ADLX loaded tuning and fans values: " << gpuDeviceId << L" / " << gpuApplication);
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADLX failed loading tuning and fans values.");
		}
	}
}