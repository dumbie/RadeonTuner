#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::AdlTuningApply(int gpuAdapterIndex, TuningFanSettings tuningFanSettings)
	{
		try
		{
			//Set save settings list
			std::vector<std::tuple<ADLOD8SettingId, int, bool>> saveSettings;

			//Tuning Preset
			saveSettings.push_back({ ADLOD8SettingId::OD8_OPTIMZED_POWER_MODE, OD8_OPTIMZED_POWER_MODES::Custom, false });

			//Core Frequency Minimum
			if (tuningFanSettings.CoreMin.Current.has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_GFXCLK_FMIN, tuningFanSettings.CoreMin.Current.value(), false });
			}

			//Core Frequency Maximum
			if (tuningFanSettings.CoreMax.Current.has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_GFXCLK_FMAX, tuningFanSettings.CoreMax.Current.value(), false });
			}

			//Memory Frequency
			if (tuningFanSettings.MemoryMax.Current.has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_UCLK_FMAX, tuningFanSettings.MemoryMax.Current.value(), false });
			}

			//Memory Timing
			if (tuningFanSettings.MemoryTiming.Current.has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_AC_TIMING, tuningFanSettings.MemoryTiming.Current.value(), false });
			}

			//Power Limit
			if (tuningFanSettings.PowerBoostUse)
			{
				if (tuningFanSettings.PowerLimitPB.Current.has_value())
				{
					saveSettings.push_back({ ADLOD8SettingId::OD8_POWER_PERCENTAGE, tuningFanSettings.PowerLimitPB.Current.value(), false });
				}
			}
			else
			{
				if (tuningFanSettings.PowerLimit.Current.has_value())
				{
					saveSettings.push_back({ ADLOD8SettingId::OD8_POWER_PERCENTAGE, tuningFanSettings.PowerLimit.Current.value(), false });
				}
			}

			//Power Voltage
			if (tuningFanSettings.PowerBoostUse)
			{
				if (tuningFanSettings.PowerVoltagePB.Current.has_value())
				{
					saveSettings.push_back({ ADLOD8SettingId::OD8_OD_VOLTAGE, tuningFanSettings.PowerVoltagePB.Current.value(), false });
				}
			}
			else
			{
				if (tuningFanSettings.PowerVoltage.Current.has_value())
				{
					saveSettings.push_back({ ADLOD8SettingId::OD8_OD_VOLTAGE, tuningFanSettings.PowerVoltage.Current.value(), false });
				}
			}

			//Power TDC
			if (tuningFanSettings.PowerBoostUse)
			{
				if (tuningFanSettings.PowerTDCPB.Current.has_value())
				{
					saveSettings.push_back({ ADLOD8SettingId::OD8_TDC_PERCENTAGE, tuningFanSettings.PowerTDCPB.Current.value(), false });
				}
			}
			else
			{
				if (tuningFanSettings.PowerTDC.Current.has_value())
				{
					saveSettings.push_back({ ADLOD8SettingId::OD8_TDC_PERCENTAGE, tuningFanSettings.PowerTDC.Current.value(), false });
				}
			}

			//Fan Control
			bool fanControl = false;
			if (tuningFanSettings.FanControl.Current.has_value())
			{
				fanControl = tuningFanSettings.FanControl.Current.value();
			}

			//Fan Zero RPM
			if (tuningFanSettings.FanZeroRpm.Current.has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_ZERORPM_CONTROL, tuningFanSettings.FanZeroRpm.Current.value(), !fanControl });
			}

			//Fan Speed 0
			if (tuningFanSettings.FanSpeed0.Current.has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_SPEED_1, tuningFanSettings.FanSpeed0.Current.value(), !fanControl });
			}

			//Fan Temperature 0
			if (tuningFanSettings.FanTemp0.Current.has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_1, tuningFanSettings.FanTemp0.Current.value(), !fanControl });
			}

			//Fan Speed 1
			if (tuningFanSettings.FanSpeed1.Current.has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_SPEED_2, tuningFanSettings.FanSpeed1.Current.value(), !fanControl });
			}

			//Fan Temperature 1
			if (tuningFanSettings.FanTemp1.Current.has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_2, tuningFanSettings.FanTemp1.Current.value(), !fanControl });
			}

			//Fan Speed 2
			if (tuningFanSettings.FanSpeed2.Current.has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_SPEED_3, tuningFanSettings.FanSpeed2.Current.value(), !fanControl });
			}

			//Fan Temperature 2
			if (tuningFanSettings.FanTemp2.Current.has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_3, tuningFanSettings.FanTemp2.Current.value(), !fanControl });
			}

			//Fan Speed 3
			if (tuningFanSettings.FanSpeed3.Current.has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_SPEED_4, tuningFanSettings.FanSpeed3.Current.value(), !fanControl });
			}

			//Fan Temperature 3
			if (tuningFanSettings.FanTemp3.Current.has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_4, tuningFanSettings.FanTemp3.Current.value(), !fanControl });
			}

			//Fan Speed 4
			if (tuningFanSettings.FanSpeed4.Current.has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_SPEED_5, tuningFanSettings.FanSpeed4.Current.value(), !fanControl });
			}

			//Fan Temperature 4
			if (tuningFanSettings.FanTemp4.Current.has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_5, tuningFanSettings.FanTemp4.Current.value(), !fanControl });
			}

			//Apply gpu tuning and fan values
			bool setResult = Adl_Overdrive8_Set_Values(gpuAdapterIndex, saveSettings);

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