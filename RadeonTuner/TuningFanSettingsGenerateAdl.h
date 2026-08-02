#pragma once
#include "pch.h"
#include "MainPage.h"
#include "MainVariables.h"

namespace winrt::RadeonTuner::implementation
{
	std::optional<TuningFanSettings> MainPage::TuningFanSettings_Generate_FromADL(int gpuAdapterIndex, std::wstring application, bool loadDefault)
	{
		try
		{
			TuningFanSettings tuningFanSettings{};

			//Device identifier
			tuningFanSettings.DeviceId = AdlxGetGpuIdentifier(gpuAdapterIndex);

			//Device application
			tuningFanSettings.Application = application;

			//Get overdrive capabilities
			int iSupported = -1;
			int iEnabled = -1;
			int iVersion = -1;
			adl_Res0 = _ADL2_Overdrive_Caps(adl_Context, gpuAdapterIndex, &iSupported, &iEnabled, &iVersion);

			//Check overdrive support
			if (iSupported != 1 && iVersion != 8)
			{
				AVDebugWriteLine("Overdrive not supported: " << iSupported << " / enabled: " << iEnabled << " / version: " << iVersion);
				tuningFanSettings.FanSupport = false;
				tuningFanSettings.TuningSupport = false;
				return tuningFanSettings;
			}
			else
			{
				AVDebugWriteLine("Overdrive supported: " << iSupported << " / enabled: " << iEnabled << " / version: " << iVersion);
			}

			//Check tuning and fan support
			tuningFanSettings.FanSupport = Adl_Overdrive8_Feature_Supported(gpuAdapterIndex, ADLOD8FeatureControl::ADL_OD8_FAN_CURVE);
			tuningFanSettings.TuningSupport = Adl_Overdrive8_Feature_Supported(gpuAdapterIndex, ADLOD8FeatureControl::ADL_OD8_GFXCLK_LIMITS);

			//Gpu Core Minimum
			try
			{
				auto defaultValue = Adl_Overdrive8_Load_Default(gpuAdapterIndex, ADLOD8SettingId::OD8_GFXCLK_FMIN);
				auto settingValue = Adl_Overdrive8_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_GFXCLK_FMIN);
				if (defaultValue.has_value() && settingValue.has_value())
				{
					if (defaultValue.value().IsSupported())
					{
						if (!loadDefault)
						{
							tuningFanSettings.CoreMin.Current = settingValue.value();
						}
						else
						{
							tuningFanSettings.CoreMin.Current = defaultValue.value().defaultValue;
						}
						tuningFanSettings.CoreMin.Minimum = defaultValue.value().minValue;
						tuningFanSettings.CoreMin.Maximum = defaultValue.value().maxValue;
						tuningFanSettings.CoreMin.Step = 1;
						tuningFanSettings.CoreMin.Support = true;
					}
				}
			}
			catch (...) {}

			//Gpu Core Maximum
			try
			{
				auto defaultValue = Adl_Overdrive8_Load_Default(gpuAdapterIndex, ADLOD8SettingId::OD8_GFXCLK_FMAX);
				auto settingValue = Adl_Overdrive8_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_GFXCLK_FMAX);
				if (defaultValue.has_value() && settingValue.has_value())
				{
					if (defaultValue.value().IsSupported())
					{
						if (!loadDefault)
						{
							tuningFanSettings.CoreMax.Current = settingValue.value();
						}
						else
						{
							tuningFanSettings.CoreMax.Current = defaultValue.value().defaultValue;
						}
						tuningFanSettings.CoreMax.Minimum = defaultValue.value().minValue;
						tuningFanSettings.CoreMax.Maximum = defaultValue.value().maxValue;
						tuningFanSettings.CoreMax.Step = 1;
						tuningFanSettings.CoreMax.Support = true;
					}
				}
			}
			catch (...) {}

			//Memory Timing
			try
			{
				auto defaultValue = Adl_Overdrive8_Load_Default(gpuAdapterIndex, ADLOD8SettingId::OD8_AC_TIMING);
				auto settingValue = Adl_Overdrive8_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_AC_TIMING);
				if (defaultValue.has_value() && settingValue.has_value())
				{
					if (defaultValue.value().IsSupported())
					{
						if (!loadDefault)
						{
							tuningFanSettings.MemoryTiming.Current = settingValue.value();
						}
						else
						{
							tuningFanSettings.MemoryTiming.Current = defaultValue.value().defaultValue;
						}
						tuningFanSettings.MemoryTiming.Support = true;
					}
				}
			}
			catch (...) {}

			//Memory Frequency
			try
			{
				auto defaultValue = Adl_Overdrive8_Load_Default(gpuAdapterIndex, ADLOD8SettingId::OD8_UCLK_FMAX);
				auto settingValue = Adl_Overdrive8_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_UCLK_FMAX);
				if (defaultValue.has_value() && settingValue.has_value())
				{
					if (defaultValue.value().IsSupported())
					{
						if (!loadDefault)
						{
							tuningFanSettings.MemoryMax.Current = settingValue.value();
						}
						else
						{
							tuningFanSettings.MemoryMax.Current = defaultValue.value().defaultValue;
						}
						tuningFanSettings.MemoryMax.Minimum = defaultValue.value().minValue;
						tuningFanSettings.MemoryMax.Maximum = defaultValue.value().maxValue;
						tuningFanSettings.MemoryMax.Step = 2;
						tuningFanSettings.MemoryMax.Support = true;
					}
				}
			}
			catch (...) {}

			//Power Limit
			try
			{
				auto defaultValue = Adl_Overdrive8_Load_Default(gpuAdapterIndex, ADLOD8SettingId::OD8_POWER_PERCENTAGE);
				auto settingValue = Adl_Overdrive8_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_POWER_PERCENTAGE);
				if (defaultValue.has_value() && settingValue.has_value())
				{
					if (defaultValue.value().IsSupported())
					{
						if (!loadDefault)
						{
							tuningFanSettings.PowerLimit.Current = settingValue.value();
						}
						else
						{
							tuningFanSettings.PowerLimit.Current = defaultValue.value().defaultValue;
						}
						tuningFanSettings.PowerLimit.Minimum = defaultValue.value().minValue;
						tuningFanSettings.PowerLimit.Maximum = defaultValue.value().maxValue;
						tuningFanSettings.PowerLimit.Step = 1;
						tuningFanSettings.PowerLimit.Support = true;
					}
				}
			}
			catch (...) {}

			//Power Voltage
			try
			{
				auto defaultValue = Adl_Overdrive8_Load_Default(gpuAdapterIndex, ADLOD8SettingId::OD8_OD_VOLTAGE);
				auto settingValue = Adl_Overdrive8_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_OD_VOLTAGE);
				if (defaultValue.has_value() && settingValue.has_value())
				{
					if (defaultValue.value().IsSupported())
					{
						if (!loadDefault)
						{
							tuningFanSettings.PowerVoltage.Current = settingValue.value();
						}
						else
						{
							tuningFanSettings.PowerVoltage.Current = defaultValue.value().defaultValue;
						}
						tuningFanSettings.PowerVoltage.Minimum = defaultValue.value().minValue;
						tuningFanSettings.PowerVoltage.Maximum = defaultValue.value().maxValue;
						tuningFanSettings.PowerVoltage.Step = 1;
						tuningFanSettings.PowerVoltage.Support = true;
					}
				}
			}
			catch (...) {}

			//Power TDC
			try
			{
				auto defaultValue = Adl_Overdrive8_Load_Default(gpuAdapterIndex, ADLOD8SettingId::OD8_TDC_PERCENTAGE);
				auto settingValue = Adl_Overdrive8_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_TDC_PERCENTAGE);
				if (defaultValue.has_value() && settingValue.has_value())
				{
					if (defaultValue.value().IsSupported())
					{
						if (!loadDefault)
						{
							tuningFanSettings.PowerTDC.Current = settingValue.value();
						}
						else
						{
							tuningFanSettings.PowerTDC.Current = defaultValue.value().defaultValue;
						}
						tuningFanSettings.PowerTDC.Minimum = defaultValue.value().minValue;
						tuningFanSettings.PowerTDC.Maximum = defaultValue.value().maxValue;
						tuningFanSettings.PowerTDC.Step = 1;
						tuningFanSettings.PowerTDC.Support = true;
					}
				}
			}
			catch (...) {}

			//Fan Zero RPM
			try
			{
				auto defaultValue = Adl_Overdrive8_Load_Default(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_ZERORPM_CONTROL);
				auto settingValue = Adl_Overdrive8_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_ZERORPM_CONTROL);
				if (defaultValue.has_value() && settingValue.has_value())
				{
					if (defaultValue.value().IsSupported())
					{
						if (!loadDefault)
						{
							tuningFanSettings.FanZeroRpm.Current = settingValue.value();
						}
						else
						{
							tuningFanSettings.FanZeroRpm.Current = defaultValue.value().defaultValue;
						}
						tuningFanSettings.FanZeroRpm.Support = true;
					}
				}
			}
			catch (...) {}

			//Fan Zero Temperature
			try
			{
				auto settingValue = Adl_Overdrive8_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_ZERO_RPM_STOP_TEMPERATURE);
				if (settingValue.has_value())
				{
					//Note: Fan zero temp sometimes returns as 0, using 50 as default when that happens.
					if (settingValue.value() <= 0)
					{
						tuningFanSettings.FanZeroTemp = 50;
					}
					else
					{
						tuningFanSettings.FanZeroTemp = settingValue.value();
					}
				}
			}
			catch (...) {}

			//Fan Speed 0
			try
			{
				auto defaultValue = Adl_Overdrive8_Load_Default(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_SPEED_1);
				auto settingValue = Adl_Overdrive8_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_SPEED_1);
				if (defaultValue.has_value() && settingValue.has_value())
				{
					if (defaultValue.value().IsSupported())
					{
						if (!loadDefault)
						{
							tuningFanSettings.FanSpeed0.Current = settingValue.value();
						}
						else
						{
							tuningFanSettings.FanSpeed0.Current = defaultValue.value().defaultValue;
						}
						tuningFanSettings.FanSpeed0.Minimum = defaultValue.value().minValue;
						tuningFanSettings.FanSpeed0.Maximum = defaultValue.value().maxValue;
						tuningFanSettings.FanSpeed0.Step = 1;
						tuningFanSettings.FanSpeed0.Support = true;
					}
				}
			}
			catch (...) {}

			//Fan Temperature 0
			try
			{
				auto defaultValue = Adl_Overdrive8_Load_Default(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_1);
				auto settingValue = Adl_Overdrive8_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_1);
				if (defaultValue.has_value() && settingValue.has_value())
				{
					if (defaultValue.value().IsSupported())
					{
						if (!loadDefault)
						{
							tuningFanSettings.FanTemp0.Current = settingValue.value();
						}
						else
						{
							tuningFanSettings.FanTemp0.Current = defaultValue.value().defaultValue;
						}
						tuningFanSettings.FanTemp0.Minimum = defaultValue.value().minValue;
						tuningFanSettings.FanTemp0.Maximum = defaultValue.value().maxValue;
						tuningFanSettings.FanTemp0.Step = 1;
						tuningFanSettings.FanTemp0.Support = true;
					}
				}
			}
			catch (...) {}

			//Fan Speed 1
			try
			{
				auto defaultValue = Adl_Overdrive8_Load_Default(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_SPEED_2);
				auto settingValue = Adl_Overdrive8_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_SPEED_2);
				if (defaultValue.has_value() && settingValue.has_value())
				{
					if (defaultValue.value().IsSupported())
					{
						if (!loadDefault)
						{
							tuningFanSettings.FanSpeed1.Current = settingValue.value();
						}
						else
						{
							tuningFanSettings.FanSpeed1.Current = defaultValue.value().defaultValue;
						}
						tuningFanSettings.FanSpeed1.Minimum = defaultValue.value().minValue;
						tuningFanSettings.FanSpeed1.Maximum = defaultValue.value().maxValue;
						tuningFanSettings.FanSpeed1.Step = 1;
						tuningFanSettings.FanSpeed1.Support = true;
					}
				}
			}
			catch (...) {}

			//Fan Temperature 1
			try
			{
				auto defaultValue = Adl_Overdrive8_Load_Default(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_2);
				auto settingValue = Adl_Overdrive8_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_2);
				if (defaultValue.has_value() && settingValue.has_value())
				{
					if (defaultValue.value().IsSupported())
					{
						if (!loadDefault)
						{
							tuningFanSettings.FanTemp1.Current = settingValue.value();
						}
						else
						{
							tuningFanSettings.FanTemp1.Current = defaultValue.value().defaultValue;
						}
						tuningFanSettings.FanTemp1.Minimum = defaultValue.value().minValue;
						tuningFanSettings.FanTemp1.Maximum = defaultValue.value().maxValue;
						tuningFanSettings.FanTemp1.Step = 1;
						tuningFanSettings.FanTemp1.Support = true;
					}
				}
			}
			catch (...) {}

			//Fan Speed 2
			try
			{
				auto defaultValue = Adl_Overdrive8_Load_Default(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_SPEED_3);
				auto settingValue = Adl_Overdrive8_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_SPEED_3);
				if (defaultValue.has_value() && settingValue.has_value())
				{
					if (defaultValue.value().IsSupported())
					{
						if (!loadDefault)
						{
							tuningFanSettings.FanSpeed2.Current = settingValue.value();
						}
						else
						{
							tuningFanSettings.FanSpeed2.Current = defaultValue.value().defaultValue;
						}
						tuningFanSettings.FanSpeed2.Minimum = defaultValue.value().minValue;
						tuningFanSettings.FanSpeed2.Maximum = defaultValue.value().maxValue;
						tuningFanSettings.FanSpeed2.Step = 1;
						tuningFanSettings.FanSpeed2.Support = true;
					}
				}
			}
			catch (...) {}

			//Fan Temperature 2
			try
			{
				auto defaultValue = Adl_Overdrive8_Load_Default(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_3);
				auto settingValue = Adl_Overdrive8_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_3);
				if (defaultValue.has_value() && settingValue.has_value())
				{
					if (defaultValue.value().IsSupported())
					{
						if (!loadDefault)
						{
							tuningFanSettings.FanTemp2.Current = settingValue.value();
						}
						else
						{
							tuningFanSettings.FanTemp2.Current = defaultValue.value().defaultValue;
						}
						tuningFanSettings.FanTemp2.Minimum = defaultValue.value().minValue;
						tuningFanSettings.FanTemp2.Maximum = defaultValue.value().maxValue;
						tuningFanSettings.FanTemp2.Step = 1;
						tuningFanSettings.FanTemp2.Support = true;
					}
				}
			}
			catch (...) {}

			//Fan Speed 3
			try
			{
				auto defaultValue = Adl_Overdrive8_Load_Default(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_SPEED_4);
				auto settingValue = Adl_Overdrive8_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_SPEED_4);
				if (defaultValue.has_value() && settingValue.has_value())
				{
					if (defaultValue.value().IsSupported())
					{
						if (!loadDefault)
						{
							tuningFanSettings.FanSpeed3.Current = settingValue.value();
						}
						else
						{
							tuningFanSettings.FanSpeed3.Current = defaultValue.value().defaultValue;
						}
						tuningFanSettings.FanSpeed3.Minimum = defaultValue.value().minValue;
						tuningFanSettings.FanSpeed3.Maximum = defaultValue.value().maxValue;
						tuningFanSettings.FanSpeed3.Step = 1;
						tuningFanSettings.FanSpeed3.Support = true;
					}
				}
			}
			catch (...) {}

			//Fan Temperature 3
			try
			{
				auto defaultValue = Adl_Overdrive8_Load_Default(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_4);
				auto settingValue = Adl_Overdrive8_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_4);
				if (defaultValue.has_value() && settingValue.has_value())
				{
					if (defaultValue.value().IsSupported())
					{
						if (!loadDefault)
						{
							tuningFanSettings.FanTemp3.Current = settingValue.value();
						}
						else
						{
							tuningFanSettings.FanTemp3.Current = defaultValue.value().defaultValue;
						}
						tuningFanSettings.FanTemp3.Minimum = defaultValue.value().minValue;
						tuningFanSettings.FanTemp3.Maximum = defaultValue.value().maxValue;
						tuningFanSettings.FanTemp3.Step = 1;
						tuningFanSettings.FanTemp3.Support = true;
					}
				}
			}
			catch (...) {}

			//Fan Speed 4
			try
			{
				auto defaultValue = Adl_Overdrive8_Load_Default(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_SPEED_5);
				auto settingValue = Adl_Overdrive8_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_SPEED_5);
				if (defaultValue.has_value() && settingValue.has_value())
				{
					if (defaultValue.value().IsSupported())
					{
						if (!loadDefault)
						{
							tuningFanSettings.FanSpeed4.Current = settingValue.value();
						}
						else
						{
							tuningFanSettings.FanSpeed4.Current = defaultValue.value().defaultValue;
						}
						tuningFanSettings.FanSpeed4.Minimum = defaultValue.value().minValue;
						tuningFanSettings.FanSpeed4.Maximum = defaultValue.value().maxValue;
						tuningFanSettings.FanSpeed4.Step = 1;
						tuningFanSettings.FanSpeed4.Support = true;
					}
				}
			}
			catch (...) {}

			//Fan Temperature 4
			try
			{
				auto defaultValue = Adl_Overdrive8_Load_Default(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_5);
				auto settingValue = Adl_Overdrive8_Load_Value(gpuAdapterIndex, ADLOD8SettingId::OD8_FAN_CURVE_TEMPERATURE_5);
				if (defaultValue.has_value() && settingValue.has_value())
				{
					if (defaultValue.value().IsSupported())
					{
						if (!loadDefault)
						{
							tuningFanSettings.FanTemp4.Current = settingValue.value();
						}
						else
						{
							tuningFanSettings.FanTemp4.Current = defaultValue.value().defaultValue;
						}
						tuningFanSettings.FanTemp4.Minimum = defaultValue.value().minValue;
						tuningFanSettings.FanTemp4.Maximum = defaultValue.value().maxValue;
						tuningFanSettings.FanTemp4.Step = 1;
						tuningFanSettings.FanTemp4.Support = true;
					}
				}
			}
			catch (...) {}

			//Return result
			//AVDebugWriteLine("Generated tuning and fan settings from ADL.");
			return tuningFanSettings;
		}
		catch (...)
		{
			//Return result
			AVDebugWriteLine("Failed to generate tuning and fan settings from ADL.");
			return std::nullopt;
		}
	}
}