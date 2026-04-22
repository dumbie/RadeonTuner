#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	bool MainPage::AdlTuningApply(int adapterIndex, TuningFanSettings tuningFanSettings)
	{
		try
		{
			//Set save settings list
			std::vector<std::tuple<ADLOD8SettingId, int, bool>> saveSettings;

			//Tuning Preset
			saveSettings.push_back({ ADLOD8SettingId::OD8_OPTIMZED_POWER_MODE, OD8_OPTIMZED_POWER_MODES::Custom, false });

			//Core Frequency Minimum
			if (tuningFanSettings.CoreMin.has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_GFXCLK_FMIN, tuningFanSettings.CoreMin.value(), false });
			}

			//Core Frequency Maximum
			if (tuningFanSettings.CoreMax.has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_GFXCLK_FMAX, tuningFanSettings.CoreMax.value(), false });
			}

			//Memory Frequency
			if (tuningFanSettings.MemoryMax.has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_UCLK_FMAX, tuningFanSettings.MemoryMax.value(), false });
			}

			//Memory Timing
			if (tuningFanSettings.MemoryTiming.has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_AC_TIMING, tuningFanSettings.MemoryTiming.value(), false });
			}

			//Power Limit
			if (tuningFanSettings.PowerBoostUse.has_value() && tuningFanSettings.PowerBoostUse.value())
			{
				if (tuningFanSettings.PowerLimitPB.has_value())
				{
					saveSettings.push_back({ ADLOD8SettingId::OD8_POWER_PERCENTAGE, tuningFanSettings.PowerLimitPB.value(), false });
				}
			}
			else
			{
				if (tuningFanSettings.PowerLimit.has_value())
				{
					saveSettings.push_back({ ADLOD8SettingId::OD8_POWER_PERCENTAGE, tuningFanSettings.PowerLimit.value(), false });
				}
			}

			//Power Voltage
			if (tuningFanSettings.PowerBoostUse.has_value() && tuningFanSettings.PowerBoostUse.value())
			{
				if (tuningFanSettings.PowerVoltagePB.has_value())
				{
					saveSettings.push_back({ ADLOD8SettingId::OD8_OD_VOLTAGE, tuningFanSettings.PowerVoltagePB.value(), false });
				}
			}
			else
			{
				if (tuningFanSettings.PowerVoltage.has_value())
				{
					saveSettings.push_back({ ADLOD8SettingId::OD8_OD_VOLTAGE, tuningFanSettings.PowerVoltage.value(), false });
				}
			}

			//Power TDC
			if (tuningFanSettings.PowerBoostUse.has_value() && tuningFanSettings.PowerBoostUse.value())
			{
				if (tuningFanSettings.PowerTDCPB.has_value())
				{
					saveSettings.push_back({ ADLOD8SettingId::OD8_TDC_PERCENTAGE, tuningFanSettings.PowerTDCPB.value(), false });
				}
			}
			else
			{
				if (tuningFanSettings.PowerTDC.has_value())
				{
					saveSettings.push_back({ ADLOD8SettingId::OD8_TDC_PERCENTAGE, tuningFanSettings.PowerTDC.value(), false });
				}
			}

			//Fan Control
			bool fanControl = false;
			if (tuningFanSettings.FanControl.has_value())
			{
				fanControl = tuningFanSettings.FanControl.value();
			}

			//Fan Zero RPM
			if (tuningFanSettings.FanZeroRpm.has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_ZERORPM_CONTROL, tuningFanSettings.FanZeroRpm.value(), !fanControl });
			}

			//Fan Speed 0
			if (tuningFanSettings.FanSpeed0.has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_SPEED_1, tuningFanSettings.FanSpeed0.value(), !fanControl });
			}

			//Fan Temperature 0
			if (tuningFanSettings.FanTemp0.has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_1, tuningFanSettings.FanTemp0.value(), !fanControl });
			}

			//Fan Speed 1
			if (tuningFanSettings.FanSpeed1.has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_SPEED_2, tuningFanSettings.FanSpeed1.value(), !fanControl });
			}

			//Fan Temperature 1
			if (tuningFanSettings.FanTemp1.has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_2, tuningFanSettings.FanTemp1.value(), !fanControl });
			}

			//Fan Speed 2
			if (tuningFanSettings.FanSpeed2.has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_SPEED_3, tuningFanSettings.FanSpeed2.value(), !fanControl });
			}

			//Fan Temperature 2
			if (tuningFanSettings.FanTemp2.has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_3, tuningFanSettings.FanTemp2.value(), !fanControl });
			}

			//Fan Speed 3
			if (tuningFanSettings.FanSpeed3.has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_SPEED_4, tuningFanSettings.FanSpeed3.value(), !fanControl });
			}

			//Fan Temperature 3
			if (tuningFanSettings.FanTemp3.has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_4, tuningFanSettings.FanTemp3.value(), !fanControl });
			}

			//Fan Speed 4
			if (tuningFanSettings.FanSpeed4.has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_SPEED_5, tuningFanSettings.FanSpeed4.value(), !fanControl });
			}

			//Fan Temperature 4
			if (tuningFanSettings.FanTemp4.has_value())
			{
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_5, tuningFanSettings.FanTemp4.value(), !fanControl });
			}

			//Save settings
			Adl_Overdrive_Set(adapterIndex, saveSettings);

			//Set result
			ShowNotification(L"Tuning and fans settings applied");
			AVDebugWriteLine(L"Tuning and fans settings applied to gpu.");
			return true;
		}
		catch (...)
		{
			//Set result
			ShowNotification(L"Failed applying tuning and fans settings");
			AVDebugWriteLine(L"Failed applying tuning and fans settings to gpu.");
			return false;
		}
	}
}