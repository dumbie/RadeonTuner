#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::TuningFanSettings_Convert_ToUI_Profile(TuningFanSettings tuningFanSettings, AdlSettingGet settingType)
	{
		try
		{
			//Keep Active
			if (tuningFanSettings.KeepActive.Get(settingType).has_value())
			{
				//Get setting
				bool valueBool = tuningFanSettings.KeepActive.Get(settingType).value();

				//Set setting value
				toggleswitch_KeepActive().IsOn(valueBool);

				//Set hint value
				textblock_KeepActive_Value().Text(valueBool ? L"Enabled" : L"Disabled");
			}

			//Fan Control Mode
			if (tuningFanSettings.FanControlMode.Get(settingType).has_value())
			{
				//Get setting
				int valueInt = tuningFanSettings.FanControlMode.Get(settingType).value();

				//Set setting value
				combobox_FanControl_Mode().SelectedIndex(valueInt);

				//Set hint value
				textblock_FanControl_Mode_Value().Text(ADL_FANCONTROL_MODES_STRING[valueInt]);
			}

			//Gpu Core Minimum
			if (tuningFanSettings.CoreMin.Get(settingType).has_value())
			{
				slider_Core_Min().Value(tuningFanSettings.CoreMin.Get(settingType).value());
			}

			//Gpu Core Maximum
			if (tuningFanSettings.CoreMax.Get(settingType).has_value())
			{
				slider_Core_Max().Value(tuningFanSettings.CoreMax.Get(settingType).value());
			}

			//Memory Timing
			if (tuningFanSettings.MemoryTiming.Get(settingType).has_value())
			{
				combobox_Memory_Timing().SelectedIndex(tuningFanSettings.MemoryTiming.Get(settingType).value());
			}

			//Memory ECC / EDC
			if (tuningFanSettings.MemoryEcc.Get(settingType).has_value())
			{
				combobox_Memory_Ecc().SelectedIndex(tuningFanSettings.MemoryEcc.Get(settingType).value());
			}

			//Memory Frequency
			if (tuningFanSettings.MemoryMax.Get(settingType).has_value())
			{
				slider_Memory_Max().Value(tuningFanSettings.MemoryMax.Get(settingType).value());
			}

			//Power Limit
			if (tuningFanSettings.PowerLimit.Get(settingType).has_value())
			{
				slider_Power_Limit().Value(tuningFanSettings.PowerLimit.Get(settingType).value());
			}

			//Power Voltage
			if (tuningFanSettings.PowerVoltage.Get(settingType).has_value())
			{
				slider_Power_Voltage().Value(tuningFanSettings.PowerVoltage.Get(settingType).value());
			}

			//Power TDC
			if (tuningFanSettings.PowerTDC.Get(settingType).has_value())
			{
				slider_Power_TDC().Value(tuningFanSettings.PowerTDC.Get(settingType).value());
			}

			//Fan Zero RPM
			if (tuningFanSettings.FanZeroRpm.Get(settingType).has_value())
			{
				//Get setting
				bool valueBool = tuningFanSettings.FanZeroRpm.Get(settingType).value();

				//Set setting value
				toggleswitch_Fan_Zero_Rpm().IsOn(valueBool);

				//Show or hide Zero RPM line
				grid_Fan_Zero_Rpm_Line_Profile().Visibility(valueBool ? Visibility::Visible : Visibility::Collapsed);
				border_Fan_Zero_Rpm_Range().Visibility(valueBool ? Visibility::Visible : Visibility::Collapsed);
			}

			//Fan Speed 0
			if (tuningFanSettings.FanSpeed0.Get(settingType).has_value())
			{
				//Set setting value
				slider_Fan_Speed_0().Value(tuningFanSettings.FanSpeed0.Get(settingType).value());
			}

			//Fan Temperature 0
			if (tuningFanSettings.FanTemp0.Get(settingType).has_value())
			{
				//Set setting value
				slider_Fan_Temp_0().Value(tuningFanSettings.FanTemp0.Get(settingType).value());
			}

			//Fan Speed 1
			if (tuningFanSettings.FanSpeed1.Get(settingType).has_value())
			{
				//Set setting value
				slider_Fan_Speed_1().Value(tuningFanSettings.FanSpeed1.Get(settingType).value());
			}

			//Fan Temperature 1
			if (tuningFanSettings.FanTemp1.Get(settingType).has_value())
			{
				//Set setting value
				slider_Fan_Temp_1().Value(tuningFanSettings.FanTemp1.Get(settingType).value());
			}

			//Fan Speed 2
			if (tuningFanSettings.FanSpeed2.Get(settingType).has_value())
			{
				//Set setting value
				slider_Fan_Speed_2().Value(tuningFanSettings.FanSpeed2.Get(settingType).value());
			}

			//Fan Temperature 2
			if (tuningFanSettings.FanTemp2.Get(settingType).has_value())
			{
				//Set setting value
				slider_Fan_Temp_2().Value(tuningFanSettings.FanTemp2.Get(settingType).value());
			}

			//Fan Speed 3
			if (tuningFanSettings.FanSpeed3.Get(settingType).has_value())
			{
				//Set setting value
				slider_Fan_Speed_3().Value(tuningFanSettings.FanSpeed3.Get(settingType).value());
			}

			//Fan Temperature 3
			if (tuningFanSettings.FanTemp3.Get(settingType).has_value())
			{
				//Set setting value
				slider_Fan_Temp_3().Value(tuningFanSettings.FanTemp3.Get(settingType).value());
			}

			//Fan Speed 4
			if (tuningFanSettings.FanSpeed4.Get(settingType).has_value())
			{
				//Set setting value
				slider_Fan_Speed_4().Value(tuningFanSettings.FanSpeed4.Get(settingType).value());
			}

			//Fan Temperature 4
			if (tuningFanSettings.FanTemp4.Get(settingType).has_value())
			{
				//Set setting value
				slider_Fan_Temp_4().Value(tuningFanSettings.FanTemp4.Get(settingType).value());
			}

			//Fan Speed Minimum
			if (tuningFanSettings.FanSpeedMin.Get(settingType).has_value())
			{
				//Set setting value
				slider_Fan_Speed_Min().Value(tuningFanSettings.FanSpeedMin.Get(settingType).value());
			}

			//Fan Speed Maximum
			if (tuningFanSettings.FanSpeedMax.Get(settingType).has_value())
			{
				//Set setting value
				slider_Fan_Speed_Max().Value(tuningFanSettings.FanSpeedMax.Get(settingType).value());
			}

			//Update fan graph
			UpdateFanGraphProfile();

			//Update fan control mode interface
			UpdateFanControlModeInterface(tuningFanSettings);

			//Set result
			AVDebugWriteLine(L"Tuning and fans settings applied to interface (Profile)");
			return true;
		}
		catch (...)
		{
			//Set result
			AVDebugWriteLine(L"Failed applying tuning and fans settings to interface (Profile)");
			return false;
		}
	}
}