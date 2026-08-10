#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::AdlTuningFanSettingsApply(int gpuAdapterIndex, TuningFanSettings targetSettings, AdlSettingGet settingGet)
	{
		try
		{
			//Set save settings list
			std::vector<std::tuple<ADLOD8SettingId, int, bool>> saveSettings;

			//Tuning Preset
			saveSettings.push_back({ ADLOD8SettingId::OD8_OPTIMZED_POWER_MODE, (int)OD8_OPTIMZED_POWER_MODES::Custom, false });

			//Core Frequency Minimum
			if (targetSettings.CoreMin.Get(settingGet).has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_GFXCLK_FMIN, targetSettings.CoreMin.Get(settingGet).value(), false });
			}

			//Core Frequency Maximum
			if (targetSettings.CoreMax.Get(settingGet).has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_GFXCLK_FMAX, targetSettings.CoreMax.Get(settingGet).value(), false });
			}

			//Memory Frequency
			if (targetSettings.MemoryMax.Get(settingGet).has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_UCLK_FMAX, targetSettings.MemoryMax.Get(settingGet).value(), false });
			}

			//Memory Timing
			if (targetSettings.MemoryTiming.Get(settingGet).has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_AC_TIMING, targetSettings.MemoryTiming.Get(settingGet).value(), false });
			}

			//Power Limit
			if (targetSettings.PowerLimit.Get(settingGet).has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_POWER_PERCENTAGE, targetSettings.PowerLimit.Get(settingGet).value(), false });
			}

			//Power Voltage
			if (targetSettings.PowerVoltage.Get(settingGet).has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_OD_VOLTAGE, targetSettings.PowerVoltage.Get(settingGet).value(), false });
			}

			//Power TDC
			if (targetSettings.PowerTDC.Get(settingGet).has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_TDC_PERCENTAGE, targetSettings.PowerTDC.Get(settingGet).value(), false });
			}

			//Fan Control
			bool fanControl = false;
			if (targetSettings.FanControl.Get(settingGet).has_value())
			{
				fanControl = targetSettings.FanControl.Get(settingGet).value();
			}

			//Fan Zero RPM
			if (targetSettings.FanZeroRpm.Get(settingGet).has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_ZERORPM_CONTROL, targetSettings.FanZeroRpm.Get(settingGet).value(), !fanControl });
			}

			//Fan Speed 0
			if (targetSettings.FanSpeed0.Get(settingGet).has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_SPEED_1, targetSettings.FanSpeed0.Get(settingGet).value(), !fanControl });
			}

			//Fan Temperature 0
			if (targetSettings.FanTemp0.Get(settingGet).has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_1, targetSettings.FanTemp0.Get(settingGet).value(), !fanControl });
			}

			//Fan Speed 1
			if (targetSettings.FanSpeed1.Get(settingGet).has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_SPEED_2, targetSettings.FanSpeed1.Get(settingGet).value(), !fanControl });
			}

			//Fan Temperature 1
			if (targetSettings.FanTemp1.Get(settingGet).has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_2, targetSettings.FanTemp1.Get(settingGet).value(), !fanControl });
			}

			//Fan Speed 2
			if (targetSettings.FanSpeed2.Get(settingGet).has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_SPEED_3, targetSettings.FanSpeed2.Get(settingGet).value(), !fanControl });
			}

			//Fan Temperature 2
			if (targetSettings.FanTemp2.Get(settingGet).has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_3, targetSettings.FanTemp2.Get(settingGet).value(), !fanControl });
			}

			//Fan Speed 3
			if (targetSettings.FanSpeed3.Get(settingGet).has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_SPEED_4, targetSettings.FanSpeed3.Get(settingGet).value(), !fanControl });
			}

			//Fan Temperature 3
			if (targetSettings.FanTemp3.Get(settingGet).has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_4, targetSettings.FanTemp3.Get(settingGet).value(), !fanControl });
			}

			//Fan Speed 4
			if (targetSettings.FanSpeed4.Get(settingGet).has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_SPEED_5, targetSettings.FanSpeed4.Get(settingGet).value(), !fanControl });
			}

			//Fan Temperature 4
			if (targetSettings.FanTemp4.Get(settingGet).has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_5, targetSettings.FanTemp4.Get(settingGet).value(), !fanControl });
			}

			//Apply gpu tuning and fan values
			bool setResult = Adl_Overdrive8_Values_Set(gpuAdapterIndex, saveSettings);

			//Return result
			return setResult;
		}
		catch (...)
		{
			//Return result
			return false;
		}
	}
}