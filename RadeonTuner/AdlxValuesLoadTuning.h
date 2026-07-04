#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	void MainPage::AdlxValuesLoadTuning()
	{
		try
		{
			//Get current and default settings
			TuningFanSettings tuningFanSettingsAdl = TuningFanSettings_Generate_FromADL(adl_Gpu_AdapterIndex).value();

			//Add gpu tuning and fans settings profile
			TuningFanSettings_Profile_Add(tuningFanSettingsAdl);

			//Device identifier
			std::wstring device_id_w = string_to_wstring(tuningFanSettingsAdl.DeviceId.value());

			//Get tuning fan settings
			TuningFanSettings& tuningFanSettingsProfile = TuningFanSettings_Profile_Get(device_id_w).value();

			//Convert settings values to interface
			bool adlResult = TuningFanSettings_ADL_Convert_ToUI(tuningFanSettingsAdl);
			bool profileResult = TuningFanSettings_Profile_Convert_ToUI(tuningFanSettingsProfile);

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
			AVDebugWriteLine("ADLX loaded tuning and fans values.");
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine("ADLX failed loading tuning and fans values.");
		}
	}
}