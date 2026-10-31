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

			//Get Fan Control Mode
			int fanControlMode = 0;
			if (targetSettings.FanControlMode.Get(settingGet).has_value())
			{
				fanControlMode = targetSettings.FanControlMode.Get(settingGet).value();
			}

			//Check Fan Control Mode
			if (fanControlMode == (int)FanControlModes::NoFanControl)
			{
				//Fan Zero RPM
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_ZERORPM_CONTROL, 0, true });

				//Fan Speed 0
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_SPEED_1, 0, true });

				//Fan Temperature 0
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_1, 0, true });

				//Fan Speed 1
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_SPEED_2, 0, true });

				//Fan Temperature 1
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_2, 0, true });

				//Fan Speed 2
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_SPEED_3, 0, true });

				//Fan Temperature 2
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_3, 0, true });

				//Fan Speed 3
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_SPEED_4, 0, true });

				//Fan Temperature 3
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_4, 0, true });

				//Fan Speed 4
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_SPEED_5, 0, true });

				//Fan Temperature 4
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_5, 0, true });

				AVDebugWriteLine("Applied fan mode: No Fan Control");
			}
			else if (fanControlMode == (int)FanControlModes::RangedFanSpeed)
			{
				//Fan Zero RPM
				if (targetSettings.FanZeroRpm.Get(settingGet).has_value())
				{
					saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_ZERORPM_CONTROL, targetSettings.FanZeroRpm.Get(settingGet).value(), false });
				}

				//Fan Speed Minimum and Maximum
				if (targetSettings.FanSpeedMin.Get(settingGet).has_value() && targetSettings.FanSpeedMax.Get(settingGet).has_value())
				{
					//Get minimum and maximum fan speed
					int curveStart = targetSettings.FanSpeedMin.Get(settingGet).value();
					int curveEnd = targetSettings.FanSpeedMax.Get(settingGet).value();

					//Calculate fan curve based on minimum and maximum
					int curveValues[5];
					//float curveWeights[] = { 0.00F, 0.20F, 0.40F, 0.60F, 1.00F }; //AMD Default
					for (int i = 0; i < 5; i++)
					{
						curveValues[i] = std::round(std::lerp(curveStart, curveEnd, i / 4.0F)); //Linear
						//curveValues[i] = std::round(curveStart + (curveEnd - curveStart) * curveWeights[i]); //Weights
					}

					//Fan Speed 0
					saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_SPEED_1, curveValues[0], false });

					//Fan Temperature 0
					saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_1, 0, true });

					//Fan Speed 1
					saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_SPEED_2, curveValues[1], false });

					//Fan Temperature 1
					saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_2, 0, true });

					//Fan Speed 2
					saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_SPEED_3, curveValues[2], false });

					//Fan Temperature 2
					saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_3, 0, true });

					//Fan Speed 3
					saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_SPEED_4, curveValues[3], false });

					//Fan Temperature 3
					saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_4, 0, true });

					//Fan Speed 4
					saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_SPEED_5, curveValues[4], false });

					//Fan Temperature 4
					saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_5, 0, true });
				}

				AVDebugWriteLine("Applied fan mode: Ranged Fan Speed");
			}
			else if (fanControlMode == (int)FanControlModes::CustomFanCurve)
			{
				//Fan Zero RPM
				if (targetSettings.FanZeroRpm.Get(settingGet).has_value())
				{
					saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_ZERORPM_CONTROL, targetSettings.FanZeroRpm.Get(settingGet).value(), false });
				}

				//Fan Speed 0
				if (targetSettings.FanSpeed0.Get(settingGet).has_value())
				{
					saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_SPEED_1, targetSettings.FanSpeed0.Get(settingGet).value(), false });
				}

				//Fan Temperature 0
				if (targetSettings.FanTemp0.Get(settingGet).has_value())
				{
					saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_1, targetSettings.FanTemp0.Get(settingGet).value(), false });
				}

				//Fan Speed 1
				if (targetSettings.FanSpeed1.Get(settingGet).has_value())
				{
					saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_SPEED_2, targetSettings.FanSpeed1.Get(settingGet).value(), false });
				}

				//Fan Temperature 1
				if (targetSettings.FanTemp1.Get(settingGet).has_value())
				{
					saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_2, targetSettings.FanTemp1.Get(settingGet).value(), false });
				}

				//Fan Speed 2
				if (targetSettings.FanSpeed2.Get(settingGet).has_value())
				{
					saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_SPEED_3, targetSettings.FanSpeed2.Get(settingGet).value(), false });
				}

				//Fan Temperature 2
				if (targetSettings.FanTemp2.Get(settingGet).has_value())
				{
					saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_3, targetSettings.FanTemp2.Get(settingGet).value(), false });
				}

				//Fan Speed 3
				if (targetSettings.FanSpeed3.Get(settingGet).has_value())
				{
					saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_SPEED_4, targetSettings.FanSpeed3.Get(settingGet).value(), false });
				}

				//Fan Temperature 3
				if (targetSettings.FanTemp3.Get(settingGet).has_value())
				{
					saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_4, targetSettings.FanTemp3.Get(settingGet).value(), false });
				}

				//Fan Speed 4
				if (targetSettings.FanSpeed4.Get(settingGet).has_value())
				{
					saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_SPEED_5, targetSettings.FanSpeed4.Get(settingGet).value(), false });
				}

				//Fan Temperature 4
				if (targetSettings.FanTemp4.Get(settingGet).has_value())
				{
					saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_5, targetSettings.FanTemp4.Get(settingGet).value(), false });
				}

				AVDebugWriteLine("Applied fan mode: Custom Fan Curve");
			}
			else if (fanControlMode == (int)FanControlModes::FanZeroRpmOnly)
			{
				//Note: Annoying limitation in api also resets fan speeds to default when Fan Zero RPM is enabled even when not requested.

				//Fan Zero RPM
				if (targetSettings.FanZeroRpm.Get(settingGet).has_value())
				{
					saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_ZERORPM_CONTROL, targetSettings.FanZeroRpm.Get(settingGet).value(), false });
				}

				//Fan Speed 0
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_SPEED_1, 0, true });

				//Fan Temperature 0
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_1, 0, true });

				//Fan Speed 1
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_SPEED_2, 0, true });

				//Fan Temperature 1
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_2, 0, true });

				//Fan Speed 2
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_SPEED_3, 0, true });

				//Fan Temperature 2
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_3, 0, true });

				//Fan Speed 3
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_SPEED_4, 0, true });

				//Fan Temperature 3
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_4, 0, true });

				//Fan Speed 4
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_SPEED_5, 0, true });

				//Fan Temperature 4
				saveSettings.push_back({ ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_5, 0, true });

				AVDebugWriteLine("Applied fan mode: Fan Zero RPM Only");
			}

			//Memory ECC / EDC
			try
			{
				if (targetSettings.MemoryEcc.Get(settingGet).has_value())
				{
					//Get value
					auto newValue = targetSettings.MemoryEcc.Get(settingGet).value();

					//Enumeration index correction
					int setValue = 0;
					if (newValue == 0)
					{
						//Disabled
						setValue = ECC_MODE_OFF;
					}
					else if (newValue == 1)
					{
						//Enabled
						setValue = ECC_MODE_ON;
					}
					else if (newValue == 2)
					{
						//HBM
						setValue = ECC_MODE_HBM;
					}

					adl_Res0 = _ADL2_Workstation_ECC_Set(adl_Context, gpuAdapterIndex, setValue);
				}
			}
			catch (...) {}

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