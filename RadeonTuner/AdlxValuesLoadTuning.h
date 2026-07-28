#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesLoadTuning(int gpuAdapterIndex, std::wstring gpuApplication)
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
			if (gpuApplication == L"Global")
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