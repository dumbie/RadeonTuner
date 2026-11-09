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
			std::vector<ADLOD8SaveSetting> saveSettings;

			//Tuning Preset
			saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_OPTIMZED_POWER_MODE, .TargetValue = (int)OD8_OPTIMZED_POWER_MODES::Custom });

			//Core Frequency Minimum
			if (targetSettings.CoreMin.Get(settingGet).has_value())
			{
				saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_GFXCLK_FMIN, .TargetValue = targetSettings.CoreMin.Get(settingGet).value() });
			}

			//Core Frequency Maximum
			if (targetSettings.CoreMax.Get(settingGet).has_value())
			{
				saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_GFXCLK_FMAX, .TargetValue = targetSettings.CoreMax.Get(settingGet).value() });
			}

			//Memory Frequency
			if (targetSettings.MemoryMax.Get(settingGet).has_value())
			{
				saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_UCLK_FMAX, .TargetValue = targetSettings.MemoryMax.Get(settingGet).value() });
			}

			//Memory Timing
			if (targetSettings.MemoryTiming.Get(settingGet).has_value())
			{
				saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_AC_TIMING, .TargetValue = targetSettings.MemoryTiming.Get(settingGet).value() });
			}

			//Power Limit
			if (targetSettings.PowerLimit.Get(settingGet).has_value())
			{
				saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_POWER_PERCENTAGE, .TargetValue = targetSettings.PowerLimit.Get(settingGet).value() });
			}

			//Power Voltage
			if (targetSettings.PowerVoltage.Get(settingGet).has_value())
			{
				saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_OD_VOLTAGE, .TargetValue = targetSettings.PowerVoltage.Get(settingGet).value() });
			}

			//Power TDC
			if (targetSettings.PowerTDC.Get(settingGet).has_value())
			{
				saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_TDC_PERCENTAGE, .TargetValue = targetSettings.PowerTDC.Get(settingGet).value() });
			}

			//Get Fan Control Mode
			int fanControlMode = (int)FanControlModes::NoFanControl;
			if (targetSettings.FanControlMode.Get(settingGet).has_value())
			{
				fanControlMode = targetSettings.FanControlMode.Get(settingGet).value();
			}

			//Check Fan Control Mode
			if (fanControlMode == (int)FanControlModes::NoFanControl)
			{
				//Fan Zero RPM
				saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_ZERORPM_CONTROL, .ResetValue = true });

				//Fan Speed 0
				saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_SPEED_1, .ResetValue = true });

				//Fan Temperature 0
				saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_1, .ResetValue = true });

				//Fan Speed 1
				saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_SPEED_2, .ResetValue = true });

				//Fan Temperature 1
				saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_2, .ResetValue = true });

				//Fan Speed 2
				saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_SPEED_3, .ResetValue = true });

				//Fan Temperature 2
				saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_3, .ResetValue = true });

				//Fan Speed 3
				saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_SPEED_4, .ResetValue = true });

				//Fan Temperature 3
				saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_4, .ResetValue = true });

				//Fan Speed 4
				saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_SPEED_5, .ResetValue = true });

				//Fan Temperature 4
				saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_5, .ResetValue = true });

				AVDebugWriteLine("Applied fan mode: No Fan Control");
			}
			else if (fanControlMode == (int)FanControlModes::FanZeroRpmOnly)
			{
				//Note: Annoying limitation in api also resets fan speeds to default when Fan Zero RPM is changed even when fan speeds are not requested.

				//Fan Zero RPM
				if (targetSettings.FanZeroRpm.Get(settingGet).has_value())
				{
					saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_ZERORPM_CONTROL, .TargetValue = targetSettings.FanZeroRpm.Get(settingGet).value() });
				}

				//Fan Speed 0
				saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_SPEED_1, .ResetValue = true });

				//Fan Temperature 0
				saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_1, .ResetValue = true });

				//Fan Speed 1
				saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_SPEED_2, .ResetValue = true });

				//Fan Temperature 1
				saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_2, .ResetValue = true });

				//Fan Speed 2
				saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_SPEED_3, .ResetValue = true });

				//Fan Temperature 2
				saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_3, .ResetValue = true });

				//Fan Speed 3
				saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_SPEED_4, .ResetValue = true });

				//Fan Temperature 3
				saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_4, .ResetValue = true });

				//Fan Speed 4
				saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_SPEED_5, .ResetValue = true });

				//Fan Temperature 4
				saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_5, .ResetValue = true });

				AVDebugWriteLine("Applied fan mode: Fan Zero RPM Only");
			}
			else if (fanControlMode == (int)FanControlModes::RangedFanSpeed)
			{
				//Fan Zero RPM
				if (targetSettings.FanZeroRpm.Get(settingGet).has_value())
				{
					saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_ZERORPM_CONTROL, .TargetValue = targetSettings.FanZeroRpm.Get(settingGet).value() });
				}

				//Fan Speed Minimum and Maximum
				if (targetSettings.FanSpeedMin.Get(settingGet).has_value() && targetSettings.FanSpeedMax.Get(settingGet).has_value())
				{
					//Get Fan Ranged Curve
					int fanRangedCurve = (int)FanRangedCurves::Linear;
					if (targetSettings.FanRangedCurve.Get(settingGet).has_value())
					{
						fanRangedCurve = targetSettings.FanRangedCurve.Get(settingGet).value();
					}

					//Get minimum and maximum fan speed
					int curveStart = targetSettings.FanSpeedMin.Get(settingGet).value();
					int curveEnd = targetSettings.FanSpeedMax.Get(settingGet).value();

					//Calculate fan curve based on minimum and maximum
					int curveValues[5];
					float curveWeightsLinear[] = { 0.00F, 0.25F, 0.50F, 0.75F, 1.00F }; //Linear
					float curveWeightsQuiet[] = { 0.00F, 0.20F, 0.40F, 0.60F, 1.00F }; //Quiet (AMD Default)
					for (UINT i = 0; i < 5; i++)
					{
						if (fanRangedCurve == (int)FanRangedCurves::Linear)
						{
							curveValues[i] = std::round(curveStart + (curveEnd - curveStart) * curveWeightsLinear[i]);
						}
						else if (fanRangedCurve == (int)FanRangedCurves::Quiet)
						{
							curveValues[i] = std::round(curveStart + (curveEnd - curveStart) * curveWeightsQuiet[i]);
						}
					}

					//Fan Speed 0
					saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_SPEED_1, .TargetValue = curveValues[0] });

					//Fan Temperature 0
					saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_1, .UseDefaultValue = true }); //30c

					//Fan Speed 1
					saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_SPEED_2, .TargetValue = curveValues[1] });

					//Fan Temperature 1
					saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_2, .UseDefaultValue = true }); //50c

					//Fan Speed 2
					saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_SPEED_3, .TargetValue = curveValues[2] });

					//Fan Temperature 2
					saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_3, .UseDefaultValue = true }); //66c

					//Fan Speed 3
					saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_SPEED_4, .TargetValue = curveValues[3] });

					//Fan Temperature 3
					saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_4, .UseDefaultValue = true }); //82c

					//Fan Speed 4
					saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_SPEED_5, .TargetValue = curveValues[4] });

					//Fan Temperature 4
					saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_5, .UseDefaultValue = true }); //92c
				}

				AVDebugWriteLine("Applied fan mode: Ranged Fan Speed");
			}
			else if (fanControlMode == (int)FanControlModes::CustomFanCurve)
			{
				//Fan Zero RPM
				if (targetSettings.FanZeroRpm.Get(settingGet).has_value())
				{
					saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_ZERORPM_CONTROL, .TargetValue = targetSettings.FanZeroRpm.Get(settingGet).value() });
				}

				//Fan Speed 0
				if (targetSettings.FanSpeed0.Get(settingGet).has_value())
				{
					saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_SPEED_1, .TargetValue = targetSettings.FanSpeed0.Get(settingGet).value() });
				}

				//Fan Temperature 0
				if (targetSettings.FanTemp0.Get(settingGet).has_value())
				{
					saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_1, .TargetValue = targetSettings.FanTemp0.Get(settingGet).value() });
				}

				//Fan Speed 1
				if (targetSettings.FanSpeed1.Get(settingGet).has_value())
				{
					saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_SPEED_2, .TargetValue = targetSettings.FanSpeed1.Get(settingGet).value() });
				}

				//Fan Temperature 1
				if (targetSettings.FanTemp1.Get(settingGet).has_value())
				{
					saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_2, .TargetValue = targetSettings.FanTemp1.Get(settingGet).value() });
				}

				//Fan Speed 2
				if (targetSettings.FanSpeed2.Get(settingGet).has_value())
				{
					saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_SPEED_3, .TargetValue = targetSettings.FanSpeed2.Get(settingGet).value() });
				}

				//Fan Temperature 2
				if (targetSettings.FanTemp2.Get(settingGet).has_value())
				{
					saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_3, .TargetValue = targetSettings.FanTemp2.Get(settingGet).value() });
				}

				//Fan Speed 3
				if (targetSettings.FanSpeed3.Get(settingGet).has_value())
				{
					saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_SPEED_4, .TargetValue = targetSettings.FanSpeed3.Get(settingGet).value() });
				}

				//Fan Temperature 3
				if (targetSettings.FanTemp3.Get(settingGet).has_value())
				{
					saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_4, .TargetValue = targetSettings.FanTemp3.Get(settingGet).value() });
				}

				//Fan Speed 4
				if (targetSettings.FanSpeed4.Get(settingGet).has_value())
				{
					saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_SPEED_5,.TargetValue = targetSettings.FanSpeed4.Get(settingGet).value() });
				}

				//Fan Temperature 4
				if (targetSettings.FanTemp4.Get(settingGet).has_value())
				{
					saveSettings.push_back(ADLOD8SaveSetting{ .Identifier = ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_5, .TargetValue = targetSettings.FanTemp4.Get(settingGet).value() });
				}

				AVDebugWriteLine("Applied fan mode: Custom Fan Curve");
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