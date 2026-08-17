#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	winrt::fire_and_forget MainPage::AdlxValuesLoadSelectTuningApp(int gpuAdapterIndex, std::wstring application)
	{
		try
		{
			//Disable saving
			disable_saving = true;

			//Get current and default settings
			TuningFanSettings tuningFanSettingsAdl = TuningFanSettings_Generate_FromADL(gpuAdapterIndex, application, false).value();

			//Add settings profile
			TuningFanSettings_Profile_Add(tuningFanSettingsAdl);

			//Device identifier
			std::wstring deviceId = tuningFanSettingsAdl.DeviceId.value();

			//Get and set settings
			tuningFanSettingsCurrent = TuningFanSettings_Profile_Get(deviceId, application).value();

			//Convert settings values to interface
			TuningFanSettings_Convert_ToUI_Adl(tuningFanSettingsAdl);
			TuningFanSettings_Convert_ToUI_Profile(tuningFanSettingsCurrent.get(), AdlSettingGet::Current);

			//Update button text
			textblock_AppSelect_Tuning().Text(application);

			//Disable or enable settings
			if (tuningFanSettingsAdl.TuningSupport && tuningFanSettingsAdl.Global())
			{
				toggleswitch_KeepActive().IsEnabled(true);
			}
			else
			{
				toggleswitch_KeepActive().IsEnabled(false);
			}

			//Update button colors
			//Fix check if current settings match profile and set button color accordingly
			SolidColorBrush colorValid = Application::Current().Resources().Lookup(box_value(L"ApplicationValidBrush")).as<SolidColorBrush>();
			button_Tuning_Apply().Background(colorValid);
			button_Fan_Apply().Background(colorValid);

			//Enable saving
			co_await AsyncTaskDelay(300, AppVariables::App.GetDispatcher());
			disable_saving = false;

			//Set result
			AVDebugWriteLine(L"ADLX loaded tuning and fans values: " << deviceId << L" / " << application);
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("Failed loading selected app values (Exception)");
		}
	}
}